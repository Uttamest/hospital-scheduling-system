#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>

using namespace std;

namespace text {
    string trim(const string& value);
    vector<string> split(const string& line, char delimiter);
    int toInt(const string& value, const string& fieldName);
    void requireField(const string& value, const string& fieldName);
    void requireNoDelimiter(const string& value, const string& fieldName, char delimiter = '|');
}
#endif
