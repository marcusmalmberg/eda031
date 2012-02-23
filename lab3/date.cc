/*
 * Class Date, implementation.
 * 
 */

#include <ctime>    // for C-routines: time and localtime
#include <sstream>
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
    
    Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

	Date::Date(std::string date) {
		using namespace std;
		stringstream ss(date);
		char c;
		ss >> year >> c;
		if (c == '-') {
			ss >> month >> c;
			if (c == '-') {
				ss >> day;
			} else {
				ss.setstate(ios_base::failbit);
			}
		} else {
			ss.setstate(ios_base::failbit);
		}
		if (year < 0 || month < 0 || month > 12 || day < 0 || day > daysPerMonth[month-1]) {
			year = 1970;
			month = 1;
			day = 1;
		}
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
    	++day;
		if(day > daysPerMonth[month-1]) {
			day = 1;
			++month;
		}
		if(month > 12) {
			month = 1;
			++year;
		}
	}

	std::ostream& operator<<(std::ostream& out, const Date& d) {
		out << d.getYear() << "-";
		if (d.getMonth() < 10)
			out << "0";
		out << d.getMonth() << "-";
		if(d.getDay() < 10)
			out << "0";
		out << d.getDay();
		return out;
	}

	std::istream& operator>>(std::istream& in, Date& d) {
		std::string s;
		in >> s;
		d = Date(s);
		return in;
	}

}
