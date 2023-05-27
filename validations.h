#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <ios>
#include <limits>
#include <windows.h>
#include <algorithm>
using namespace std;

// To check if a number is negative
template <typename T>
T is_negative(T num)
{
    if (num < 0)
    {
        return true;
    }
    return false;
}

string input_string()
{
    string s;
    while (true)
    {
        try
        {
            cin >> ws;
            getline(cin, s);
            if (std::cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input.");
            }
        }
        catch (const std::exception &e)
        {
            continue;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return s;
    }
}

// To check if a string contains only alphabetical characters
string input_strictString()
{
    string s;
    int i = 0;
    while (true)
    {
        cin.clear();
        cin >> ws;
        getline(cin, s);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (i = 0; i < s.length(); i++)
        {
            if (!isalpha(s[i]) && s[i] != ' ')
            {
                cout << "invalid input! Enter again" << endl;
                break;
            }
        }
        if (i == s.length())
        {
            return s;
        }
    }
}

int input_int()
{
    int n;
    while (true)
    {
        try
        {
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (std::cin.fail())
            {
                cin.clear();
                throw std::runtime_error("Invalid input.");
            }
        }
        catch (const std::exception &e)
        {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return n;
    }
}

long long input_ullong()
{
    long long n;
    while (true)
    {
        try
        {
            cin >> n;
            if (std::cin.fail())
            {
                throw std::runtime_error("Invalid input.");
            }
            else if (is_negative(n))
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        catch (const std::exception &e)
        {
            cout << "Invalid input! Enter again: " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return n;
    }
}

long long input_llong()
{
    long long n;
    while (true)
    {
        try
        {
            cin >> n;
            if (std::cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input.");
            }
        }
        catch (const std::exception &e)
        {
            cout << "Invalid input! Enter again: " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return n;
    }
}

float input_float()
{
    float n;
    while (true)
    {
        try
        {
            cin >> n;
            if (std::cin.fail())
            {
                throw std::runtime_error("Invalid input.");
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (const std::exception &e)
        {
            cout << "invalid input! Enter again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return n;
    }
}

// To validate if a date entered is a valid date
bool is_date(const string &dob)
{
    if (dob.length() != 8)
    {
        return false;
    }
    int day = std::stoi(dob.substr(0, 2));
    int month = std::stoi(dob.substr(2, 2));
    int year = std::stoi(dob.substr(4, 4));
    if (month <= 0 || month > 12)
    {
        return false;
    }
    int maxDays = 31;
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            maxDays = 29;
        }
        else
        {
            maxDays = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDays = 30;
    }
    if (day <= 0 || day > maxDays)
    {
        return false;
    }
    if (year < 1900 || year > 2005)
    {
        return false;
    }
    return true;
}

// To turn on/off console echo
bool SetConsoleEcho(bool enableEcho)
{

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enableEcho)
    {
        mode &= ~ENABLE_ECHO_INPUT;
    }
    else
    {
        mode |= ENABLE_ECHO_INPUT;
    }

    SetConsoleMode(hStdin, mode);

    return true;
}

void pauseConsole()
{
    cout << endl
         << "Press any key to continue!" << endl;
    cin.clear();
    cin.get();
}

string removeNonNumericCharacters(const string &str)
{
    string result;
    copy_if(str.begin(), str.end(), back_inserter(result), [](char c)
            { return isdigit(c); });
    return result;
}