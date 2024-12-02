#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(single_char('h'),
                     union_of(single_char('i'), single_char('a')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"ha", true},
    {"ho", false},
    {"hia", false},
};

int main()
{
    std::cout << target.to_graph() << std::endl;
    std::cerr << check(target, cases) << std::endl;
    return 0;
}
