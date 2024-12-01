#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = optional(concat(single_char('h'), single_char('i')));

const std::map<std::string, bool> cases = {
    {"", true},
    {"hi", true},
    {"h", false},
    {"i", false},
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check(regex, cases) << std::endl;
    return 0;
}
