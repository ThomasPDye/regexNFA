#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(
    concat(
        concat(
            single_char('h'), single_char('a')),
        one_or_more(single_char('h'))),
    zero_or_more(single_char('a')));

int main()
{
    std::cout << target.label << std::endl;
    std::cerr << target.language(272).size() << std::endl;
    return 0;
}
