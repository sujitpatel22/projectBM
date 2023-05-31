#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <ios>
#include <limits>
#include <string.h>
#include <algorithm>
#include <math.h>
#include "E:\msys64\mingw64\include\curses.h"
using namespace std;

// PDcurses elements for CGUI
int WinHeight() { return LINES; }
int WinWidth() { return LINES; }
int menuWinHeight() { return 20; }
int menuWinWidth() { return 30; }
int bodyWinHeight() { return 20; }
// int COLS { return 80; }
int CenterY() { return LINES / 2; }
int CenterX() { return COLS / 2; }
int menuCenterY() { return (LINES - menuWinHeight()) / 2; }
int menuCenterX() { return (COLS - menuWinWidth()) / 2; }
int bodyCenterY() { return (LINES - bodyWinHeight()) / 2; }
int bodyCenterX() { return (COLS - COLS) / 2; }

// To set up the background color
void setBackgroundColor(WINDOW *win)
{
    init_pair(1, COLOR_BLUE, COLOR_CYAN);
    init_pair(2, COLOR_CYAN, COLOR_WHITE);
    for (int y = 0; y < LINES; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            int color = (x * 2) / COLS + 1;
            wattron(win, COLOR_PAIR(color));
            mvwaddch(win, y, x, ' ');
            wattroff(win, COLOR_PAIR(color));
        }
    }
    wrefresh(win);
}

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

string input_string(WINDOW *win)
{
    char str[25];
    while (true)
    {
        try
        {
            cbreak();
            echo();
            mvwgetstr(win, LINES - 4, COLS / 2 - 4, str);
            mvwprintw(win, LINES - 4, (COLS - strlen("-----------------------------------------")) / 2, "                                      ");
        }
        catch (const std::exception &e)
        {
            continue;
        }
        return string(str);
    }
}
// To check if a string contains only alphabetical characters
string input_strictString(WINDOW *win)
{
    char str[25];
    string sstr = "";
    int i = 0;
    while (true)
    {
        try
        {
            nocbreak();
            echo();
            mvwgetstr(win, LINES - 4, COLS / 2 - 4, str);
            mvwprintw(win, LINES - 4, (COLS - strlen("-----------------------------------------")) / 2, "                                      ");
            sstr = string(str);
        }
        catch (const std::exception &e)
        {
            continue;
        }
        for (i = 0; i < sstr.length();)
        {
            if (!isalpha(sstr[i]) && sstr[i] != ' ')
            {
                break;
            }
            ++i;
        }
        if (i == sstr.length())
        {
            return sstr;
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

unsigned long long input_ullong(WINDOW *win)
{
    char str[16];
    long long n;
    do
    {
        try
        {
            nocbreak();
            echo();
            mvwgetstr(win, LINES - 4, COLS / 2 - 4, str);
            mvwprintw(win, LINES - 4, (COLS - strlen("-----------------------------------------")) / 2, "                                      ");
        }
        catch (const std::exception &e)
        {
            continue;
        }
    } while (is_negative(n));
    return n;
}

long long input_llong(WINDOW *win)
{
    char str[16];
    long long n;
    while (true)
    {
        try
        {
            nocbreak();
            echo();
            mvwgetstr(win, LINES - 4, COLS / 2 - 4, str);
            mvwprintw(win, LINES - 4, (COLS - strlen("-----------------------------------------")) / 2, "                                      ");
        }
        catch (const std::exception &e)
        {
            continue;
        }
        return stoll(string(str));
    }
}

float input_float(WINDOW *win)
{
    float n;
    while (true)
    {
        try
        {
            nocbreak();
            echo();
            mvwscanw(win, bodyWinHeight() - 2, COLS / 2 - 4, "%f", &n);
        }
        catch (const std::exception &e)
        {
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

    // HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    // DWORD mode;
    // GetConsoleMode(hStdin, &mode);

    // if (!enableEcho)
    // {
    //     mode &= ~ENABLE_ECHO_INPUT;
    // }
    // else
    // {
    //     mode |= ENABLE_ECHO_INPUT;
    // }

    // SetConsoleMode(hStdin, mode);

    return true;
}

void pauseConsole()
{
    move(LINES - 3, (COLS - strlen("Press enter to continue!")) / 2);
    printw("Press enter to continue!");
    wgetch(stdscr);
    // refresh();
}

bool returnBack(WINDOW *win)
{
    delwin(win);
    endwin();
    clear();
    return true;
}

string removeNonNumericCharacters(const string &str)
{
    string result;
    copy_if(str.begin(), str.end(), back_inserter(result), [](char c)
            { return isdigit(c); });
    return result;
}

float roundToDecimal(float value)
{
    return round(value * 100) / 100;
}