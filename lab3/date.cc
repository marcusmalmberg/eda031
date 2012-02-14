/*
 * Class Date, implementation.
 * 
 */

#include <ctime>    // for C-routines: time and localtime
#include "date.h"

namespace cpp_lab3 {
    int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    Date::Date() {
        time_t timer = time(0);           // time in seconds since 1970-01-01
        tm* locTime = localtime(&timer);  // broken-down time
        year = 1900 + locTime->tm_year;
        month = 1 + locTime->tm_mon;
        day = locTime->tm_mday;
    }
    
    Date::Date(int y, int m, int d) {
        //
        // *** IMPLEMENT ***
        //
    }
    
    int Date::getYear() const {
        return year;
    }
    
    int Date::getMonth() const {
        return month;
    }
    
    int Date::getDay() const {
        return day;
    }
    
    void Date::next() {
        //
        // *** IMPLEMENT ***
        //
    }
}
