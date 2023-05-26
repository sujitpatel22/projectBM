#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <ios>
#include <limits>
#include <windows.h>
using namespace std;

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
            cout << "invalid input! Enter again" << endl;
            continue;
        }
        return n;
    }
}

long input_long()
{
    long n;
    // while (true)
    // {
    //     try
    //     {
    cin >> n;
    //     if (std::cin.fail())
    //     {
    //         cin.clear();
    //         throw std::runtime_error("Invalid input.");
    //     }
    //     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // }
    // catch (const std::exception &e)
    // {
    //     cout << "Invalid input! Enter again: " << endl;
    //     cin.clear();
    //     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     continue;
    // }
    return n;
    // }
}

unsigned long long input_long_long()
{
    unsigned long long n;
    while (true)
    {
        try
        {
            cin >> n;
            if (std::cin.fail())
            {
                cin.clear();
                throw std::runtime_error("Invalid input.");
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

template <typename T>
T is_negative(T num)
{
    if (num < 0)
    {
        return true;
    }
    return false;
}

bool is_date(string dob)
{
    // int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // if (dob.length() != 8)
    // {
    //     return false;
    // }
    // int m = stoi((to_string(dob[2] + dob[3])));
    // cout << m <<endl;
    // if (m <= 0 || m > 12)
    // {
    //     return false;
    // }
    // int d = stoi((to_string(dob[0] + dob[1])));
    // cout << d <<endl;
    // if (d <= 0 || d > days[m])
    // {
    //     return false;
    // }
    // int y = stoi((to_string(dob[4] + dob[5] + dob[6] + dob[7])));
    // cout << y <<endl;
    // if (y < 1900 || y > 2005)
    // {
    //     return false;
    // }
    return true;
}

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