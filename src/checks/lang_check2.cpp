#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = concat(zero_or_more(single_char('a')), zero_or_more(single_char('b')));

const std::set<std::string> expected = {
    "",
    "b",
    "bb",
    "bbb",
    "bbbb",
    "bbbbb",
    "bbbbbb",
    "bbbbbbb",
    "a",
    "ab",
    "abb",
    "abbb",
    "abbbb",
    "abbbbb",
    "abbbbbb",
    "aa",
    "aab",
    "aabb",
    "aabbb",
    "aabbbb",
    "aabbbbb",
    "aaa",
    "aaab",
    "aaabb",
    "aaabbb",
    "aaabbbb",
    "aaaa",
    "aaaab",
    "aaaabb",
    "aaaabbb",
    "aaaaa",
    "aaaaab",
    "aaaaabb",
    "aaaaaa",
    "aaaaaab",
    "aaaaaaa",
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check_language(regex, 7, expected) << std::endl;
    return 0;
}
