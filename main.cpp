#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bank.h"
// #include <ncurses.h>

using namespace std;

bool loadUsers(vector<User> &);
bool loadAccounts(vector<Account> &);
bool loadTransections(vector<Account> &);

int main(void)
{
    // initscr();
    // keypad(stdscr, TRUE);
    // noecho();
    // Start the Bank.

    // Hereafter all the functions will be oprated through Bank CUI;
    Bank bank;
    vector<Account> *accounts = bank.getAccounts();
    vector<User> *users = bank.getUsers();
    system("cls");
    cout << "Starting App..." << endl;

    cout << "Hang on! Loading User data..." << endl;
    loadUsers(*users);
    cout
        << "Done! Loading Account data..." << endl;
    loadAccounts(*accounts);
    cout
        << "Done! Loading Transections data..." << endl;
    loadTransections(*accounts);

    if (!bank.openCSV())
    {
        cout << "Unable to open CSV files to write data" << endl;
        exit(1);
    }
    bank.welcome();
    bank.menu();
}

bool loadAccounts(vector<Account> &accounts)
{
    ifstream infile("data_csv/accounts_data.csv", ios::in);
    if (!infile)
        return false;
    string lineBuffer;
    string fieldBuffer;
    int size = 1;
    int accId = 0;
    while (getline(infile, lineBuffer, '\n'))
    {
        Account acc;
        istringstream iss(lineBuffer);
        getline(iss, fieldBuffer, ',');
        accId = stoi(fieldBuffer);
        if (acc.load_csv_data(lineBuffer))
        {
            // cout << accId << ", ";
            accounts.resize(size);
            accounts[accId] = acc;
            ++size;
        }
    }
    infile.close();
    return true;
}

bool loadUsers(vector<User> &users)
{
    ifstream infile("data_csv/users_data.csv", ios::in);
    if (!infile)
        return false;
    string lineBuffer = "";
    string fieldBuffer = "";
    int size = 1;
    int userId = 0;
    while (getline(infile, lineBuffer, '\n'))
    {
        User user;
        istringstream iss(lineBuffer);
        getline(iss, fieldBuffer, ',');
        userId = stoi(fieldBuffer);
        if (user.load_csv_data(lineBuffer))
        {
            // cout << userId << ", ";
            users.resize(size);
            users[userId] = user;
            ++size;
        }
    }
    infile.close();
    return true;
}

bool loadTransections(vector<Account> &accounts)
{
    ifstream infile("data_csv/transections_data.csv", ios::in);
    if (!infile)
        return false;
    string lineBuffer;
    string accId;
    while (getline(infile, lineBuffer, '\n'))
    {
        istringstream iss(lineBuffer);
        getline(iss, accId, ',');
        Transection trans;
        trans.load_csv_data(lineBuffer);
        accounts[stoi(accId)].transections.push_back(trans);
    }
    infile.close();
    return true;
}