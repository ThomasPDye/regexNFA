#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = one_or_more(
    union_of(
        one_or_more(
            union_of(
                concat(
                    single_char('a'),
                    optional(single_char('b'))),
                concat(optional(single_char('c')), single_char('d')))),
        one_or_more(single_char('e'))));

int main()
{
    std::cout << target.label << std::endl;
    std::cerr << target.language(6).size() << std::endl;
    return 0;
}
