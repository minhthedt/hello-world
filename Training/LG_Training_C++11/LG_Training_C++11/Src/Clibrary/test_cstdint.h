//http://www.cplusplus.com/reference/cstdint/
//This header defines a set of integral type aliases with specific width requirements, 
//along with macros specifying their limits and macro functions to create values of these types.

//signed type  | unsigned type
//intmax_t     | uintmax_t      | Integer type with the maximum width supported.

//int8_t       | uint8_t        | Integer type with a width of exactly 8, 16, 32, or 64 bits.
//int16_t      | uint16_t       | For signed types, negative values are represented using 2's complement.
//int32_t      | uint32_t       | No padding bits.
//int64_t      | uint64_t       | Optional: These typedefs are not defined if no types with such characteristics exist.*

//int_least8_t | uint_least8_t  | 
//int_least16_t| uint_least16_t | Integer type with a minimum of 8, 16, 32, or 64 bits.
//int_least32_t| uint_least32_t | No other integer type exists with lesser size and at least the specified width.
//int_least64_t| uint_least64_t | 

//int_fast8_t  | uint_fast8_t   | 
//int_fast16_t | uint_fast16_t  | Integer type with a minimum of 8, 16, 32, or 64 bits.
//int_fast32_t | uint_fast32_t  | At least as fast as any other integer type with at least the specified width.
//int_fast64_t | uint_fast64_t  | 

//                              | Integer type capable of holding a value converted from a void pointer and then be 
//intptr_t     | uintptr_t      | converted back to that type with a value that compares equal to the original pointer.
//                              | Optional: These typedefs may not be defined in some library implementations.*


void test_cstdint();

