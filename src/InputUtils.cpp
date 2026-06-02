#include "InputUtils.h"

#include "DateTime.h"
#include "HospitalException.h"
#include "TextUtils.h"

#include <iostream>

using namespace std;

namespace input
{

    string readLine(const string &prompt)
    {
        cout << prompt;
        string value;
        if (!getline(cin, value))
        {
            throw HospitalException("Input stream closed.");
        }
        return text::trim(value);
    }

    string readRequiredLine(const string &prompt)
    {
        while (true)
        {
            const string value = readLine(prompt);
            try
            {
                text::requireField(value, "Value");
                return value;
            }
            catch (const ValidationException &error)
            {
                cout << "Invalid input: " << error.what() << '\n';
            }
        }
    }

    int readInt(const string &prompt, int minValue, int maxValue)
    {
        while (true)
        {
            const string value = readLine(prompt);
            try
            {
                const int parsed = text::toInt(value, "Input");
                if (parsed < minValue || parsed > maxValue)
                {
                    cout << "Please enter a number from " << minValue << " to " << maxValue << ".\n";
                    continue;
                }
                return parsed;
            }
            catch (const ValidationException &error)
            {
                cout << "Invalid input: " << error.what() << '\n';
            }
        }
    }

    string readDate(const string &prompt)
    {
        while (true)
        {
            const string value = readLine(prompt);
            if (DateTime::isValidDate(value))
            {
                return value;
            }
            cout << "Please use a real date in YYYY-MM-DD format.\n";
        }
    }

    string readTime(const string &prompt)
    {
        while (true)
        {
            const string value = readLine(prompt);
            if (DateTime::isValidTime(value))
            {
                return value;
            }
            cout << "Please use 24-hour time in HH:MM format.\n";
        }
    }

    void pause()
    {
        cout << "\nPress Enter to continue...";
        string ignored;
        getline(cin, ignored);
        cout << '\n';
    }

}
