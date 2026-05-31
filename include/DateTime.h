#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <string>

using namespace std;

class DateTime {
public:
    static bool isValidDate(const string &date);
    static bool isValidTime(const string &time);
    static void requireValidDate(const string &date);
    static void requireValidTime(const string &time);
    static string key(const string &date, const string &time);

private:
    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);
};
#endif