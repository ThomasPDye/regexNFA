#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(
    zero_or_more(
        concat(
            single_char('l'),
            single_char('o'))),
    zero_or_more(single_char('l')));

const std::map<std::string, bool> cases = {
    {"", true},
    {"lo", true},
    {"lol", true},
    {"lolll", true},
    {"lolol", true},
    {"looool", false},
    {"olll", false},
    {"lolololll", true},
};

int main()
{
    std::cout << target.to_graph() << std::endl;
    std::cerr << check(target, cases) << std::endl;
    return 0;
}
