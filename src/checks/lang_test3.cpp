#include "regexfa.hpp"

#include <iostream>

using namespace regexfa;
using namespace regexfa::constructors;

graph regex = one_or_more(
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
    std::cout << regex.label << std::endl;
    std::cerr << regex.language(6).size() << std::endl;
    return 0;
}
