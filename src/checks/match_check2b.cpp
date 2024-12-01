#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = one_or_more(concat(
    single_char('h'),
    single_char('i')));

const std::map<std::string, bool> cases = {
    {"hi", true},
    {"hihi", true},
    {"hii", false},
    {"", false},
};

int main()
{
    std::cout << regex.to_graph() << std::endl;
    std::cerr << check(regex, cases) << std::endl;
    return 0;
}
