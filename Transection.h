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
    Transection(int _accId, long _id, string _type, double _ammount, string _from, string _toUPI, string _mode)
    {
        accId = _accId;
        transId = to_string(_id);
        type = _type;
        amount = to_string(_ammount);
        from = _from;
        to_acc = _toUPI;
        mode = _mode;
        transTime = getTime();
    }

    // extra library functions for transection class (Abstracted):
    // fetching current Time from the system
    string getTime()
    {
        stringstream ss;
        auto time = chrono::system_clock::now();
        time_t now_time = std::chrono::system_clock::to_time_t(time);
        string currTime = ctime(&now_time);
        return currTime;
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