#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
using namespace std;

class Transection
{
private:
    int accId;
    string transId = "";
    string type = "";
    string amount = "";
    string from = "";
    string to_acc = "";
    string mode = "";
    string transTime = "";
    friend class Account;

public:
    // To create a new Transection (read-only)
    Transection() { accId = 0; }
    Transection(int _accId, long _id, string _type, string _amount, string _from, string _toUPI, string _mode)
    {
        accId = _accId;
        transId = to_string(_id);
        type = _type;
        amount = _amount;
        from = _from;
        to_acc = _toUPI;
        mode = _mode;
        transTime = getTime();
    }

    // extra library functions for transection class (Abstracted):
    // fetching current Time from the system
    string getTime()
    {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
        struct std::tm *timeinfo = std::localtime(&time);
        int day = timeinfo->tm_mday;
        int month = timeinfo->tm_mon + 1;   
        int year = timeinfo->tm_year + 1900;
        string strTime = "";
        strTime.append(to_string(day)).append("-").append(to_string(month)).append("-").append(to_string(year));
        return strTime;
    }
    void save_csv_data(ofstream &transections_csv)
    {
        transections_csv << accId << "," << transId << "," << type << "," << amount << "," << from << "," << to_acc << "," << mode << "," << transTime << endl;
    }

    bool load_csv_data(string lineBuffer)
    {
        string fieldBuffer;
        istringstream iss(lineBuffer);

        getline(iss, fieldBuffer, ',');
        accId = stoi(fieldBuffer);
        getline(iss, fieldBuffer, ',');
        transId = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        type = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        amount = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        from = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        to_acc = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        mode = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        transTime = fieldBuffer;

        return true;
    }
};