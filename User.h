#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "dependencies.h"
// #include <ctype>
#include <vector>
#include "Account.h"
using namespace std;

class User
{
private:
    int userId = 0;
    string username = "";
    string password = "";
    string DOB = "";
    long long phoneNo = 0;
    bool sessionSet = false;

public:
    vector<int> accIds;
    vector<unsigned long long> accNumbers;
    friend class Bank;

    // To create a new User
    User() { userId = 0, phoneNo = 0; }
    User(int setUserId, vector<User> &users)
    {
        userId = setUserId;
        bool proceed = true;
        clear();
        refresh();
        WINDOW *registerWin = newwin(LINES, COLS, 0, 0);
        wrefresh(registerWin);
        setBackgroundColor(registerWin);
        noecho();
        mvwprintw(registerWin, 0, (COLS - strlen(" Register User ")) / 2, " Register User ");
        mvwprintw(registerWin, LINES / 2, (COLS - strlen("Welcome to User registration")) / 2, "Welcome to User registration");
        wrefresh(registerWin);
        pauseConsole();

        try
        {
            while (proceed)
            {
                int i = 0;
                do
                {
                    werase(registerWin);
                    setBackgroundColor(registerWin);
                    mvwprintw(registerWin, LINES / 2, (COLS - strlen("Username: (Must be 8 to 25 characters long)")) / 2, "Username: (Must be 8 to 25 characters long)");
                    wrefresh(registerWin);
                    username = input_string(registerWin);
                    if (username == "-1")
                    {
                        throw runtime_error("go_back");
                    }
                } while ((username.length() < 8 || username.length() > 25));
                for (i = 0; i < users.size(); i++)
                {
                    if (users[i].getUsername().compare(username) == 0)
                    {
                        mvwprintw(registerWin, LINES - 2, (COLS - strlen("Username alredy taken!")) / 2, "Username alredy taken!");
                        wrefresh(registerWin);
                        break;
                    }
                }
                if (i == users.size())
                    break;
            }

            do
            {
                werase(registerWin);
                setBackgroundColor(registerWin);
                mvwprintw(registerWin, LINES / 2, (COLS - strlen("Password: (Must be 8 to 16 characters long)")) / 2, "Password: (Must be 8 to 16 characters long)");
                wrefresh(registerWin);
                password = input_string(registerWin);
                if (password == "-1")
                {
                    throw runtime_error("go_back");
                }
            } while ((password.length() < 8 || password.length() > 16));

            do
            {
                werase(registerWin);
                setBackgroundColor(registerWin);
                mvwprintw(registerWin, LINES / 2, (COLS - strlen("Date of Birth (format: DDMMYYYY) :")) / 2, "Date of Birth (format: DDMMYYYY) :");
                wrefresh(registerWin);
                DOB = input_string(registerWin);
                if (DOB == "-1")
                {
                    throw runtime_error("go_back");
                }
            } while (!is_date(DOB));
            int i = 0;
            bool valid = true;
            do
            {
                valid = true;
                werase(registerWin);
                setBackgroundColor(registerWin);
                mvwprintw(registerWin, LINES / 2, (COLS - strlen("Enter Phone number :")) / 2, "Enter Phone number :");
                wrefresh(registerWin);
                phoneNo = input_llong(registerWin);
                if (phoneNo == -1)
                {
                    throw runtime_error("go_back");
                }
                for (i = 0; i < users.size();)
                {
                    if (users[i].phoneNo == phoneNo)
                    {
                        mvwprintw(registerWin, LINES - 2, (COLS - strlen("Phone number alredy taken!")) / 2, "Phone number alredy taken!");
                        wrefresh(registerWin);
                        valid = false;
                    }
                    ++i;
                }
                if (i == users.size())
                {
                    break;
                }
            } while ((is_negative(phoneNo) || to_string(phoneNo).length() < 10) && !valid);

            {
                werase(registerWin);
                setBackgroundColor(registerWin);
                mvwprintw(registerWin, 2, (COLS - strlen("-----------------------------------")) / 2, "Success! User registered!");
                string label = "Username:    ";
                mvwprintw(registerWin, LINES / 2 - 4, (COLS - strlen("-----------------------------------")) / 2, (label.append(username)).c_str());
                label = "Password:    ";
                mvwprintw(registerWin, LINES / 2 - 2, (COLS - strlen("-----------------------------------")) / 2, (label.append(password)).c_str());
                label = "DOB:    ";
                mvwprintw(registerWin, LINES / 2, (COLS - strlen("-----------------------------------")) / 2, (label.append(DOB)).c_str());
                label = "Phone number:    ";
                mvwprintw(registerWin, LINES / 2 + 2, (COLS - strlen("-----------------------------------")) / 2, (label.append(to_string(phoneNo))).c_str());
                sessionSet = true;
                wrefresh(registerWin);
                pauseConsole();
            }
            delwin(registerWin);
            endwin();
            clear();
        }
        catch (exception e)
        {
            throw runtime_error("go_back");
        }
    }

    // Authenticate User
    bool authenticate(string _username, string _password)
    {
        if (username.compare(_username) == 0 && password.compare(_password) == 0)
        {
            sessionSet = true;
            return true;
        }
        return false;
    }

    bool logout()
    {
        sessionSet = false;
        return true;
    }

    // Remove left account Id & account Number from the vector<accIds> & vector<accNumbers> respectively.
    // void removeAcc(int _index)
    // {
    //     // error in erasin data....
    //     accIds.erase(accIds.begin() + _index, _index + 1);
    //     accNumbers.erase(accNumbers.begin() + _index, _index + 1);
    // }
    //  To get the user Id
    int getUserId() { return userId; }
    // to get Username
    string getUsername() { return username; }
    // To get password
    string getPassword() { return password; }
    // To get phone number
    unsigned long long getPhoneNo() { return phoneNo; }

    // ~User()
    // {
    //     cout << "Deleted User | username: " << username << " | "
    //          << "DOB " << DOB << endl;
    // }

    void save_csv_data(ofstream &users_csv)
    {
        users_csv << userId << "," << username << "," << password << "," << DOB << "," << phoneNo << ",";
        for (int accId : accIds)
        {
            users_csv << accId << "/";
        }
        users_csv << ",";
        for (unsigned long long accNo : accNumbers)
        {
            users_csv << static_cast<long long>(accNo) << "/";
        }
        users_csv << "," << endl;
    }

    bool load_csv_data(string lineBuffer)
    {
        istringstream iss(lineBuffer);
        string fieldBuffer;
        string charBuffer;
        // Loading private data;
        getline(iss, fieldBuffer, ',');
        userId = (stoi(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        username = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        password = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        DOB = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        phoneNo = stoll(fieldBuffer);
        // Loading public data...
        getline(iss, fieldBuffer, ',');
        istringstream isf(fieldBuffer);
        while (getline(isf, charBuffer, '/'))
        {
            accIds.push_back(stoi(charBuffer));
        }
        getline(iss, fieldBuffer, ',');
        istringstream isf2(fieldBuffer);
        while (getline(isf2, charBuffer, '/'))
        {
            accNumbers.push_back(stoull(charBuffer));
        }
        return true;
    }
};