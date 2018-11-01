#include "test_codecvt.h"
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <fstream>
//Unicode conversion facets
//Standard facets to convert between UTF character encodings.
//
//Notice that the codecvt facet is not declared in this header, but in <locale>.

void test_codecvt()
{
#if (!_DLL) && (_MSC_VER >= 1900 /* VS 2015*/) && (_MSC_VER <= 1911 /* VS 2017 */)
    std::u32string str(U"\U00004f60\U0000597d");  // ni hao (你好)

    std::locale loc(std::locale(), new std::codecvt_utf8<char32_t>);
    std::basic_ofstream<char32_t> ofs("test.txt");
    ofs.imbue(loc);

    std::cout << "Writing to file (UTF-8)... ";
    ofs << str;
    std::cout << "done!\n";
#endif
}