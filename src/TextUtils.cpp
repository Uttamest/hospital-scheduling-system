#include "TextUtils.h"
#include "HospitalException.h"
#include <cerrno>
#include <climits>
#include <cstdlib>
using namespace std;

namespace text {

string trim(const string &value) {
    const string whitespace = " \t\r\n";
    const string::size_type begin = value.find_first_not_of(whitespace);
    if (begin == string::npos) {
        return "";
    }

    const string::size_type end = value.find_last_not_of(whitespace);
    return value.substr(begin, end - begin + 1);
}

vector<string> split(const string &line, char delimiter) {
    vector<string> parts;
    string::size_type start = 0;

    while (true) {
        const string::size_type position = line.find(delimiter, start);
        if (position == string::npos) {
            parts.push_back(line.substr(start));
            break;
        }

        parts.push_back(line.substr(start, position - start));
        start = position + 1;
    }

    return parts;
}

int toInt(const string &value, const string &fieldName) {
    const string trimmed = trim(value);
    if (trimmed.empty()) {
        throw ValidationException(fieldName + " must be a number.");
    }

    char* end = nullptr;
    errno = 0;
    const long parsed = strtol(trimmed.c_str(), &end, 10);
    if (errno != 0 || end == trimmed.c_str() || *end != '\0') {
        throw ValidationException(fieldName + " must be a valid integer.");
    }
    if (parsed < INT_MIN || parsed > INT_MAX) {
        throw ValidationException(fieldName + " is outside the valid integer range.");
    }

    return static_cast<int>(parsed);
}

void requireNoDelimiter(const string &value, const string &fieldName, char delimiter) {
    if (value.find(delimiter) != string::npos) {
        // The delimiter is reserved for file storage, so user text cannot contain it.
        throw ValidationException(fieldName + " cannot contain the pipe character '|'.");
    }
}

void requireField(const string &value, const string &fieldName) {
    if (trim(value).empty()) {
        throw ValidationException(fieldName + " is required.");
    }
    requireNoDelimiter(value, fieldName);
}
}
