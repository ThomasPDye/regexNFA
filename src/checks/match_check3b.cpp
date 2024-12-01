#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = concat(single_char('h'),
                     union_of(single_char('i'), single_char('a')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"ha", true},
    {"ho", false},
    {"hia", false},
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check(regex, cases) << std::endl;
    return 0;
}
