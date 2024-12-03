#include "regex.hpp"

#include <iostream>

using namespace regex::engine;
using namespace regex::engine::constructors;

graph target = concat(
    one_or_more(
        concat(
            single_char('l'),
            single_char('o'))),
    one_or_more(single_char('l')));

int main()
{
    std::cout << target.label << std::endl;
    std::cerr << target.language(571).size() << std::endl;
    return 0;
}
