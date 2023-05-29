#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "validations.h"
// #include <ctype>
#include <vector>
#include "Account.h"
using namespace std;

class User
{
private:
    int userId;
    string username = "";
    string password = "";
    string DOB = "";
    long long phoneNo;
    bool sessionSet = false;

public:
    vector<int> accIds;
    vector<unsigned long long> accNumbers;
    friend class Bank;

    // To create a new User
    User() { userId = 0, phoneNo = 0; }
    User(int setUserId, vector<User> &users)
    {
        while (true)
        {
            system("cls");
            cout << "Welcome to User registration" << endl;
            cout << endl
                 << "Username: (Must be 8 to 25 characters long)" << endl;
            username = input_string();
            if (username.length() < 8 || username.length() > 25)
            {
                cout << endl
                     << "Username must be 8 to 25 characters long!" << endl;
                continue;
            }
            for (int i = 0; i < users.size(); i++)
            {
                if (users[i].getUsername().compare(username) == 0)
                {
                    cout << endl
                         << "Username alredy taken!" << endl;
                    break;
                }
            }
            goto password;
        }
    password:
        while (true)
        {
            system("cls");
            SetConsoleEcho(true);
            cout << endl
                 << "Password: (Must be 8 to 25 characters long)" << endl;
            SetConsoleEcho(false);
            password = input_string();
            if (password.length() >= 8 && password.length() <= 25)
            {
                break;
            }
        }
        SetConsoleEcho(true);
        do
        {
            system("cls");
            cout << endl
                 << "Date of Birth (format: DDMMYYYY) :" << endl;
            DOB = input_string();
        } while (!is_date(DOB));
        while (true)
        {
            system("cls");
            int i = 0;
            cout << endl
                 << "Phone Number :" << endl;
            phoneNo = input_llong();
            // Phone Number validation
            if (is_negative(phoneNo) || to_string(phoneNo).length() < 10)
            {
                continue;
            }
            for (i = 0; i < users.size(); i++)
            {
                if (users[i].phoneNo == phoneNo)
                {
                    cout << endl
                         << "Phone number already in use!" << endl;
                    break;
                }
            }
            if (i == users.size())
            {
                goto final;
            }
        }
    final:
        system("cls");
        cout << "Success! User registered! " << endl;
        userId = setUserId;
        cout << endl
             << "Your Username: " << username << endl;
        cout << endl
             << "password: " << password << endl;
        sessionSet = true;
        cout << endl
             << "DoB: " << DOB[0] + DOB[1] << "-" << DOB[2] + DOB[3] << "-" << DOB[4] + DOB[5] + DOB[6] + DOB[7] << endl;
        cout << endl
             << "Phone number: " << phoneNo << endl;

        pauseConsole();
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