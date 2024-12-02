#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph target = optional(concat(single_char('h'), single_char('i')));

const std::map<std::string, bool> cases = {
    {"", true},
    {"hi", true},
    {"h", false},
    {"i", false},
};

int main()
{
    std::cout << target.to_graph() << std::endl;
    std::cerr << check(target, cases) << std::endl;
    return 0;
}
