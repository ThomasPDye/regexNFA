#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = concat(single_char('h'), optional(single_char('i')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"h", true},
    {"ho", false},
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check(regex, cases) << std::endl;
    return 0;
}
