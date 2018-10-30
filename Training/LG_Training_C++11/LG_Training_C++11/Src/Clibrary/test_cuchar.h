//http://www.cplusplus.com/reference/cuchar/
//This header provides support for 16 - bit and 32 - bit characters, suitable to be encoded using UTF - 16 and UTF - 32.

//If defined, values of type char16_t have UTF-16 encoding.
//Otherwise, the encoding of char16_t is unspecified.
//(In C11, the macro expands to 1 when defined)
//__STD_UTF_16__    

//If defined, values of type char32_t have UTF - 32 encoding.
//Otherwise, the encoding of char32_t is unspecified.
//(In C11, the macro expands to 1 when defined)
//__STD_UTF_32__

//c16rtomb //Convert 16-bit character to multibyte sequence (function )
//c32rtomb //Convert 32-bit character to multibyte sequence (function )
//mbrtoc16 //Convert multibyte sequence to 16-bit character (function )
//mbrtoc32 //Convert multibyte sequence to 32-bit character (function )


void test_cuchar();