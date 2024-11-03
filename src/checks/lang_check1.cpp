#include "regexfa.hpp"

#include <iostream>

using namespace regexfa;
using namespace regexfa::constructors;

graph regex = concat(
    single_char('a'),
    concat(
        optional(union_of(single_char('b'), single_char('c'))),
        optional(single_char('d'))));

const std::set<std::string> expected = {
    "a",
    "ad",
    "ab",
    "abd",
    "ac",
    "acd",
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check_language(regex, 3, expected) << std::endl;
    return 0;
}
