#include "test_chrono.h"
#include <chrono>
#include <ratio>
#include <iostream>
#include <ctime>
//std::chrono::duration
//A duration object expresses a time span by means of a count and a period.
//template <class Rep, class Period = ratio<1> > class duration;
//hours = ratio<3600,1> //typedef duration < /*see rep below*/, ratio<3600,1> > hours;
//nanoseconds = ratio<1,1000000000>
void test_duaration() //value = count * ratio
{
    typedef std::chrono::duration<int> seconds_type;//đơn vị là giây
    typedef std::chrono::duration<int, std::milli> milliseconds_type;//ratio đối với giây
    typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;//ratio đối với giờ

    hours_type h_oneday(24);                  // 24h
    seconds_type s_oneday(60 * 60 * 24);          // 86400s
    milliseconds_type ms_oneday(s_oneday);    // 86400000ms 
    //milliseconds_type ms_oneday = std::chrono::duration_cast<milliseconds_type>(s_oneday);
    hours_type aaa = std::chrono::duration_cast<hours_type>(s_oneday);

    std::cout << "h in 1 day = " << h_oneday.count() << std::endl;
    std::cout << "s in 1 day = " << s_oneday.count() << std::endl;
    std::cout << "ms in 1 day = " << ms_oneday.count() << std::endl;
    std::cout << "h in 1 day = " << aaa.count() << std::endl;
}


//std::chrono::system_clock,lấy về thời gian hiện tại của hệ thống
    //Clock classes provide access to the current time_point.
    //Specifically, system_clock is a system - wide realtime clock. (đồng hồ thời gian thực trên toàn hệ thống)
//system-wide: All processes running on the system shall retrieve the same time_point values by using this clock
void test_system_clock()
{
    //using std::chrono::system_clock;
    using namespace std::chrono;

    std::chrono::duration<int, std::ratio<60 * 60 * 24> > one_day(1);

    system_clock::time_point today = system_clock::now();//static time_point now() noexcept;
    system_clock::time_point tomorrow = today + one_day;

    std::time_t tt;

    tt = system_clock::to_time_t(today);//Convert to time_t
    std::cout << "today is: " << ctime(&tt);

    tt = system_clock::to_time_t(tomorrow);
    std::cout << "tomorrow will be: " << ctime(&tt);
    //
    using namespace std::chrono;
    // create tm with 1/1/2000:
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = 100;   // year: 2000
    timeinfo.tm_mon = 0;      // month: january
    timeinfo.tm_mday = 1;     // day: 1st
    timeinfo.tm_hour = 20;    // i don't know exactly how to round "day"
    //std::time_t tt = std::mktime(&timeinfo);
    tt = std::mktime(&timeinfo);

    system_clock::time_point tp = system_clock::from_time_t(tt);
    system_clock::duration d = system_clock::now() - tp;

    // convert to number of days:
    typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
    typedef duration<int, std::ratio<60 * 60>> hours_type;
    days_type ndays = duration_cast<days_type> (d);
    hours_type nhours = duration_cast<hours_type> (d);
    days_type zero = days_type::zero();
    std::cout << "zero.count() = " << zero.count() <<std::endl;

    // display result:
    std::cout << ndays.count() << " days have passed since 1/1/2000" << std::endl;
    std::cout << nhours.count() << " hours have passed since 1/1/2000" << std::endl;
    std::cout << std::endl;

    system_clock::time_point t1 = system_clock::now();
    std::cout << "printing out 1000 stars...\n";
    for (int i = 0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;
    system_clock::time_point t2 = system_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "system_clock : It took me " << time_span.count() << " seconds.";
}

//std::chrono::steady_clock
    //Clock classes provide access to the current time_point.
    //steady_clock is specifically designed to calculate time intervals. (thiết kế để tính toán khoảng thời gian)
//steady: Every tick the clock advances takes the same amount of time (in terms of physical time).
void test_steady_clock()
{
    using namespace std::chrono;

    steady_clock::time_point t1 = steady_clock::now();

    std::cout << "printing out 1000 stars...\n";
    for (int i = 0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;

    steady_clock::time_point t2 = steady_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "steady_clock: It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
}

//std::chrono::high_resolution_clock
    //The members of clock classes provide access to the current time_point.
    //high_resolution_clock is the clock with the shortest tick period.It may be a synonym for system_clock or steady_clock.
//highest precision: high_resolution_clock is the clock with the shortest tick period
void test_high_resolution_clock()
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    std::cout << "printing out 1000 stars...\n";
    for (int i = 0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "high_resolution_clock: It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
}

void test_duration_cast()
{
    std::chrono::seconds s(1);             // 1 second
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (s);

    ms += std::chrono::milliseconds(2500);  // 2500 millisecond

    s = std::chrono::duration_cast<std::chrono::seconds> (ms);   // truncated

    std::cout << "ms: " << ms.count() << std::endl;
    std::cout << "s: " << s.count() << std::endl;
}


//std::chrono::time_point
//A time_point object expresses a point in time relative to a clock's epoch.
//Internally, the object stores an object of a duration type, and uses the Clock type as a reference for its epoch.
void test_time_point()
{

}


void test_chrono()
{
    test_system_clock();
    test_duaration();
    test_steady_clock();
    test_high_resolution_clock();
    test_duration_cast();
}