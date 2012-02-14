/*
 * class Date, describes dates with year, month, and day.
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>

namespace cpp_lab3 {
    class Date {
	public:
        Date();                      // today's date
        Date(int y, int m, int d);   // yyyy-mm-dd
        int getYear() const;	     // get the year
        int getMonth() const;        // get the month
        int getDay() const;          // get the day
        void next();                 // advance to next day
	private:
        int year;                    // the year (four digits)
        int month;                   // the month (1-12)
        int day;                     // the day (1-..)
        static int daysPerMonth[12]; // number of days in each month
    };
}

#endif
