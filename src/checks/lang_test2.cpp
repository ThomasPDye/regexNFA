#include "regex.hpp"

#include <iostream>

using namespace regex;
using namespace regex::constructors;

graph regex = concat(
    concat(
        concat(
            single_char('h'), single_char('a')),
        one_or_more(single_char('h'))),
    zero_or_more(single_char('a')));

int main()
{
    std::cout << regex.label << std::endl;
    std::cerr << regex.language(272).size() << std::endl;
    return 0;
}
