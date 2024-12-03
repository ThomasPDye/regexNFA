#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = union_of(concat(single_char('h'), single_char('i')),
                       concat(single_char('l'), single_char('o')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"lo", true},
    {"hilo", false},
};

int main()
{
    std::cout << target.to_graph() << std::endl;
    std::cerr << check(target, cases) << std::endl;
    return 0;
}
