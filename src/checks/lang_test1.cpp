#include "regexfa.hpp"

#include <iostream>

using namespace regexfa;
using namespace regexfa::constructors;

graph regex = concat(
    one_or_more(
        concat(
            single_char('l'),
            single_char('o'))),
    one_or_more(single_char('l')));

int main()
{
    std::cout << regex.label << std::endl;
    std::cerr << regex.language(571).size() << std::endl;
    return 0;
}
