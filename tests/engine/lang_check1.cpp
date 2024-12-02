#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(
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
    std::cout << target.to_graph() << std::endl;
    std::cerr << check_language(target, 3, expected) << std::endl;
    return 0;
}
