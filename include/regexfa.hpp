#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <limits>

namespace regexfa
{
    typedef unsigned long index_t;

    class charset : public std::set<char>
    {
    public:
        inline charset() {}

        inline charset(const char c)
        {
            insert(c);
        }

        inline charset(const char min, const char max)
        {
            for (int c = min; c <= max; c++)
                insert(c);
        }

        inline charset operator+=(charset other)
        {
            for (auto c : other)
                insert(c);
            return *this;
        }
    };

    const charset non_null(1, 127);

    class state
    {
        inline static index_t _count = 0;

    public:
        inline state() : number(_count++) {}

        inline state(const state &other) : number(other.number) {}

        inline operator std::string()
        {
            return "S" + std::to_string(number);
        }

    public:
        const index_t number;
    };

    inline bool operator<(const state a, const state b)
    {
        return a.number < b.number;
    }

    inline bool operator==(const state a, const state b)
    {
        return a.number == b.number;
    }

    class named_matcher
    {
    public:
        using match_function = std::function<bool(char)>;

    public:
        inline named_matcher(match_function func, std::string name, const charset domain, bool epsilon = false) : is_epsilon(epsilon), _func(func), _name(name), _domain(domain) {}

        inline bool operator()(char c)
        {
            return _func(c);
        }

        inline operator std::string()
        {
            return _name;
        }

        const bool is_epsilon;

        inline charset domain(const charset super = non_null)
        {
            if (is_epsilon)
                _domain = {};
            else if (_domain.size() == 0)
                find_domain(super);
            return _domain;
        }

    private:
        inline void find_domain(const charset super = non_null)
        {
            if (!is_epsilon)
                for (auto c : super)
                    if (c != 0 && _func(c))
                        _domain.insert(c);
        }

    private:
        const match_function _func;
        const std::string _name;
        charset _domain;
    };

    namespace matchers
    {
        inline const named_matcher EPSILON(
            [](char) -> bool
            { return false; }, "E", charset(), true);

        inline named_matcher match_eq(const char c)
        {
            return named_matcher(
                [c](char x) -> bool
                { return c == x; }, (std::string) "EQ " + std::string(1, c), charset(c));
        }

        inline const named_matcher ANY(
            [](char) -> bool
            { return true; }, "ANY", non_null);

    }

    class rule
    {
    public:
        inline rule(state start_, named_matcher matcher_, state end_) : start(start_), end(end_), matcher(matcher_) {}

        inline bool match(char c)
        {
            return matcher(c);
        }

        inline bool is_epsilon()
        {
            return matcher.is_epsilon;
        }

        inline charset domain()
        {
            return matcher.domain();
        }

        inline operator std::string()
        {
            return (std::string)start + " -" + (std::string)matcher + "-> " + (std::string)end;
        }

    public:
        state start, end;
        named_matcher matcher;
    };

    class graph
    {
    public:
        std::string label;
        state start, end;
        std::vector<rule> rules;

        inline graph(std::string label_, state start_, state end_, std::vector<rule> rules_) : label(label_), start(start_), end(end_), rules(rules_) {}

        // implement logical copy as pertaining to same functionality on a new set of states
        inline graph(const graph &other)
        {
            label = other.label;
            std::map<state, state> state_map;
            state_map.emplace(other.start, start);
            state_map.emplace(other.end, end);
            for (auto r : other.rules)
            {
                for (auto s : {r.start, r.end})
                {
                    if (state_map.count(s) == 0)
                        state_map.emplace(s, state());
                }
                rules.emplace_back(state_map[r.start], r.matcher, state_map[r.end]);
            }
        }

        inline std::string to_graph()
        {
            std::string result = "digraph \"" + label + "\" {\n";
            for (auto r : rules)
                result += "  " + (std::string)r.start + " -> " + (std::string)r.end + " [label=\"" + (std::string)r.matcher + "\"];\n";
            result += (std::string)start + " [shape=square];\n";
            result += (std::string)end + " [shape=doublecircle];\n";
            result += "}\n";
            return result;
        }

        inline bool match(std::string str)
        {
            std::set<state> states = follow_epsilons(start);
            for (auto c : str)
            {
                std::set<state> next_states;
                for (auto r : matching_rules(states, c))
                {
                    for (auto s : follow_epsilons(r.end))
                        next_states.insert(s);
                }
                states = next_states;
            }
            return states.count(end) != 0;
        }

        inline std::set<std::string> language(const size_t max_length)
        {
            std::set<std::string> result;
            std::set<state> states = follow_epsilons(start);
            std::map<state, std::set<std::string>> state_candidates;
            for (auto s : states)
                state_candidates[s].insert("");
            for (size_t i = 0; i <= max_length; i++)
            {
                for (auto candidate : state_candidates[end])
                    result.insert(candidate);
                std::set<state> next_states;
                std::map<state, std::set<std::string>> next_state_candidates;
                // for each rule
                for (auto r : rules)
                {
                    // if rule is not epsilon and follows an active state
                    if (!r.is_epsilon() && states.count(r.start) != 0)
                    {
                        for (auto s : follow_epsilons(r.end))
                        {
                            for (auto c : r.domain())
                            {
                                for(auto candidate : state_candidates[r.start])
                                    next_state_candidates[s].insert(candidate + c);
                            }
                            next_states.insert(s);
                        }
                    }
                }
                states = next_states;
                state_candidates = next_state_candidates;
            }
            return result;
        }

        inline std::set<state> follow_epsilons(state initial)
        {
            std::set<state> result;
            result.insert(initial);
            for (auto r : rules)
                if (r.is_epsilon() && r.start == initial)
                    for (auto s : follow_epsilons(r.end))
                        result.insert(s);
            return result;
        }

        inline std::vector<rule> matching_rules(std::set<state> states, char c)
        {
            std::vector<rule> result;
            for (auto r : rules)
            {
                if (states.count(r.start) != 0 && r.match(c))
                    result.push_back(r);
            }
            return result;
        }

        inline std::map<state, charset> domains(std::set<state> states)
        {
            std::map<state, charset> result;
            for (auto r : rules)
            {
                if (states.count(r.start) != 0)
                {
                    result[r.start] += r.domain();
                }
            }
            return result;
        }

        inline std::set<std::string> shortest_first_language(const size_t max_length)
        {
            std::set<std::string> result;
            std::set<std::string> candidates = {""}, previous_candidates;
            find_domain();
            for (size_t length = 0; length <= max_length; length++)
            {
                // construct the next set of candidates
                for (auto cs : previous_candidates)
                    for (auto c : _domain)
                        candidates.insert(cs + c);
                // check the latest set of candidates and place matches in result
                for (auto cs : candidates)
                    if (match(cs))
                        result.insert(cs);
                previous_candidates = candidates;
                candidates = {};
            }
            return result;
        }

        inline std::set<std::string> depth_first_language(const size_t max_length, const std::string pre = "")
        {
            std::set<std::string> result;
            if (match(pre))
                result.insert(pre);
            if (pre.size() < max_length)
            {
                find_domain();
                for (auto c : _domain)
                {
                    for (auto sublang_str : depth_first_language(max_length, pre + c))
                        result.insert(sublang_str);
                }
            }
            return result;
        }

        inline void find_domain()
        {
            if (_domain.size() == 0)
                for (auto r : rules)
                    if (!r.is_epsilon())
                        for (auto c : r.domain())
                            _domain.insert(c);
        }

    private:
        charset _domain;
    };

    namespace constructors
    {
        inline graph single_char(char c)
        {
            state start, end;
            return graph(std::string(1, c), start, end, {rule(start, matchers::match_eq(c), end)});
        }

        inline graph any_char()
        {
            state start, end;
            return graph(".", start, end, {rule(start, matchers::ANY, end)});
        }

        inline graph zero_or_more(graph sub)
        {
            state start, end;
            std::vector<rule> rules = sub.rules;
            rules.emplace_back(start, matchers::EPSILON, end);
            rules.emplace_back(start, matchers::EPSILON, sub.start);
            rules.emplace_back(sub.end, matchers::EPSILON, end);
            rules.emplace_back(sub.end, matchers::EPSILON, sub.start);
            return graph("(" + sub.label + ")*", start, end, rules);
        }

        inline graph concat(graph left, graph right)
        {
            std::vector<rule> rules = left.rules;
            for (auto rrule : right.rules)
                rules.push_back(rrule);
            rules.emplace_back(left.end, matchers::EPSILON, right.start);
            return graph(left.label + right.label, left.start, right.end, rules);
        }

        inline graph one_or_more(graph sub)
        {
            // concat subgraph with zero or more of a logical copy of subgraph
            graph result = concat(sub, zero_or_more(graph(sub)));
            result.label = "(" + sub.label + ")+";
            return result;
        }

        inline graph union_of(graph left, graph right)
        {
            state start, end;
            std::vector<rule> rules = left.rules;
            for (auto rrule : right.rules)
                rules.push_back(rrule);
            rules.emplace_back(start, matchers::EPSILON, left.start);
            rules.emplace_back(start, matchers::EPSILON, right.start);
            rules.emplace_back(left.end, matchers::EPSILON, end);
            rules.emplace_back(right.end, matchers::EPSILON, end);
            return graph("(" + left.label + "|" + right.label + ")", start, end, rules);
        }

        inline graph set_of(std::vector<graph> subs)
        {
            state start, end;
            std::vector<rule> rules;
            std::string label = "[";
            label += "]";
            for (auto sub : subs)
            {
                label += "(" + sub.label + ")";
                for (auto srule : sub.rules)
                    rules.push_back(srule);
                rules.emplace_back(start, matchers::EPSILON, sub.start);
                rules.emplace_back(sub.end, matchers::EPSILON, end);
            }
            return graph(label, start, end, rules);
        }

        inline graph optional(graph sub)
        {
            state start, end;
            std::vector<rule> rules = sub.rules;
            rules.emplace_back(start, matchers::EPSILON, sub.start);
            rules.emplace_back(sub.end, matchers::EPSILON, end);
            rules.emplace_back(start, matchers::EPSILON, end);
            return graph("(" + sub.label + ")?", start, end, rules);
        }
    }

    inline std::string check(graph machine, std::map<std::string, bool> cases)
    {
        std::string log;
        for (auto c : cases)
        {
            if (c.second == machine.match(c.first))
                log += "PASS: " + c.first + " -> " + (c.second ? "true" : "false") + "\n";
            else
                log += "FAIL: " + c.first + " -> " + (c.second ? "false (expected true)" : "true (expected false)") + "\n";
        }
        return log;
    }

    inline std::string check_language(graph machine, size_t max_length, std::set<std::string> expected)
    {
        std::string log;
        std::set<std::string> lang = machine.language(max_length);
        for (auto e : expected)
        {
            if (lang.count(e))
                log += "PASS: language contains \"" + e + "\"\n";
            else
                log += "FAIL: language does not contain \"" + e + "\"\n";
        }
        for (auto l : lang)
        {
            if (expected.count(l) == 0)
                log += "FAIL: language contains \"" + l + "\"\n";
        }
        return log;
    }
}
