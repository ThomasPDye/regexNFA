#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = union_of(concat(single_char('h'), single_char('i')),
                       concat(single_char('l'), single_char('o')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"lo", true},
    {"hilo", false},
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check(regex, cases) << std::endl;
    return 0;
}
