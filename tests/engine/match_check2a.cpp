#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(
    single_char('h'),
    one_or_more(single_char('i')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"hii", true},
    {"h", false},
};

int main()
{
    std::cout << target.to_graph() << std::endl;
    std::cerr << check(target, cases) << std::endl;
    return 0;
}
