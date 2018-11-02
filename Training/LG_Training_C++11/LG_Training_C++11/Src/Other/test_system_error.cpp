#include "test_system_error.h"
// error_code::assign
#include <string>
#include <iostream>       // std::cout
#include <cerrno>         // errno
#include <system_error>   // std::error_code, std::generic_category
#include <cmath>          // std::pow
//This header defines a series of standardized elements to report error conditions originating from 
//the operating system or other low - level operations.
using namespace std;

struct expnumber {
    double value;
    std::error_code error;
    expnumber(double base, double exponent) {
        value = std::pow(base, exponent);
        if (errno) error.assign(errno, std::generic_category());
    }
};

void test_error_code()
{
    errno = 0;
    std::sqrt(-1.0);        // errno set to EDOM
    std::error_code ec(errno, std::generic_category());

    std::error_condition ok;
    if (ec != ok) std::cout << "Error: " << ec.message() << '\n';
};

//custom error conditions enum type :
enum class custom_errc
{
success = 0,
client_error,
server_error,
other
};

namespace std
{
    template<> struct is_error_condition_enum<custom_errc> : public true_type {};
}

namespace test_error_category
{
    // custom category:
    class custom_category_t : public std::error_category 
    {
    public:
        virtual const char* name() const _NOEXCEPT  { return "custom"; }
        virtual std::error_condition default_error_condition(int ev) const  _NOEXCEPT override
        {
            if ((ev >= 200) && (ev<300)) return std::error_condition((int)custom_errc::success, *this);
            else if ((ev >= 400) && (ev<500)) return std::error_condition((int)custom_errc::client_error, *this);
            else if ((ev >= 500) && (ev<600)) return std::error_condition((int)custom_errc::server_error, *this);
            else return std::error_condition((int)custom_errc::other, *this);
        }
        virtual bool equivalent(const std::error_code& code, int condition) const  _NOEXCEPT  override
        {
            return *this == code.category() &&
                static_cast<int>(default_error_condition(code.value()).value()) == condition;
        }
        virtual _NODISCARD std::string message(int ev) const override
        {
            switch (ev) {
            case 200: return "OK";
            case 403: return "403 Forbidden";
            case 404: return "404 Not Found";
            case 500: return "500 Internal Server Error";
            case 503: return "503 Service Unavailable";
            default: return "Unknown error";
            }
        }
    } ;
    custom_category_t custom_category;
    // make_error_code overload to generate custom conditions:
    std::error_condition make_error_condition(custom_errc e) {
        
        return std::error_condition(static_cast<int>(e), custom_category);
    }

    int main()
    {
        // let's generate a 404:
        std::error_code e(404, custom_category);

        int val = e.value();
        if (e.default_error_condition().value() == (int)custom_errc::success) std::cout << "Success: " << e.message();
        else if (e.default_error_condition().value() == (int)custom_errc::client_error) std::cout << "Client Error: " << e.message();
        else if (e.default_error_condition().value() == (int)custom_errc::server_error) std::cout << "Server Error: " << e.message();//e.default_error_condition().message()
        else std::cout << "Unknown";
        std::cout << std::endl;

        return 0;
    }
};

void test_error_condition()
{
    std::cout << "The default error condition: ";
    std::cout << std::error_condition().message() << '\n';

    std::cout << "A condition constructed from errc: ";
    std::cout << std::error_condition(std::errc::permission_denied).message() << '\n';

    std::cout << "Some generic error conditions, by value:\n";
    for (int i = 0; i<10; ++i) {
        std::error_condition c(i, std::generic_category());
        std::cout << "\t#" << i << ": " << c.message() << '\n';
    }

    //The default error condition : No error
    //A condition constructed from errc : Permission denied
    //Some generic error conditions, by value :
        //#0: No error
        //#1: Operation not permitted
        //#2: No such file or directory
        //#3: No such process
        //#4: Interrupted function call
        //#5: Input / output error
        //#6: No such device or address
        //#7: Arg list too long
        //#8: Exec format error
        //#9: Bad file descriptor
}

void test_system_error()
{
   // test_error_code();
    //test_error_category::main();
    test_error_condition();

}