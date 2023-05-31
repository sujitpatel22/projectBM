#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bank.h"

using namespace std;

bool loadUsers(vector<User> &);
bool loadAccounts(vector<Account> &);
bool loadTransections(vector<Account> &);
bool loadStaticData(int *, int *, int *, unsigned long long *, unsigned long long *);
// void welcome();

int main(void)
{
    // Initialise the screen
    initscr();
    start_color();

    // Create loading window
    static WINDOW *loadingWin = newwin(LINES, COLS, 0,0);
    refresh();                   
    setBackgroundColor(loadingWin);                         
    mvwprintw(loadingWin, LINES/2, COLS/2, "Loading data");
    // Start the Bank.
    // Hereafter all the functions will be oprated through Bank CUI;s
    Bank bank;
    vector<Account> *accounts = bank.getAccounts();
    vector<User> *users = bank.getUsers();
    int *getStaticUserId = bank.getStaticUserId();
    int *getStaticAccountId = bank.getStaticAccountId();
    int *getStaticTransId = bank.getStaticTransId();
    unsigned long long *getStaticAccno = bank.getStaticAccno();
    unsigned long long *getStaticDebitNo = bank.getStaticDebitNo();

    wclear(loadingWin);
    setBackgroundColor(loadingWin);
    mvwprintw(loadingWin, (LINES/2)-2, (COLS - strlen("Loading User data...")) / 2, "Loading User data...");
    wrefresh(loadingWin);
    loadUsers(*users);
    mvwprintw(loadingWin, (LINES/2)-1, (COLS - strlen("Loading Account data...")) / 2, "Loading Account data...");
    wrefresh(loadingWin);
    loadAccounts(*accounts);
    mvwprintw(loadingWin, LINES/2, (COLS - strlen("Loading static data...")) / 2, "Loading static data...");
    wrefresh(loadingWin);
    loadStaticData(getStaticUserId, getStaticAccountId, getStaticTransId, getStaticAccno, getStaticDebitNo);
    mvwprintw(loadingWin, (LINES/2)+1, (COLS - strlen("Loading Transections data...")) / 2, "Loading Transections data...");
    wrefresh(loadingWin);
    loadTransections(*accounts);

    if (!bank.openCSV())
    {
        mvwprintw(loadingWin, LINES/2, (COLS - strlen("Unable to open CSV files to write data")) / 2, "Unable to open CSV files to write data");

        exit(1);
    }
    wclear(loadingWin);
    setBackgroundColor(loadingWin);
    mvwprintw(loadingWin, LINES/2, (COLS - strlen("Welcome to the Bank Management System")) / 2, "Welcome to the Bank Management System");
    mvwprintw(loadingWin, LINES-5, (COLS - strlen("1.0 Built - Sujit Patel & Preet Anand")) / 2, "1.0 Built - Sujit Patel & Preet Anand");
    wrefresh(loadingWin);
    pauseConsole();
    // Delete the loading window
    delwin(loadingWin);
    // End loadingWin
    endwin();
    clear();
    // Start the bank Application
    bank.menu();
    return true;
}

bool loadAccounts(vector<Account> &accounts)
{
    ifstream infile("data_csv/accounts_data.csv", ios::in);
    if (!infile)
        return false;
    string lineBuffer;
    string fieldBuffer;
    int accId = 0;
    while (getline(infile, lineBuffer, '\n'))
    {
        Account acc;
        istringstream iss(lineBuffer);
        getline(iss, fieldBuffer, ',');
        accId = stoi(fieldBuffer);
        if (acc.load_csv_data(lineBuffer))
        {
            if (accId >= accounts.size())
                accounts.resize(accId + 1);
            accounts[accId] = acc;
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
            if (userId >= users.size())
                users.resize(userId + 1);
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
    string lineBuffer = "";
    string accId;
    while (getline(infile, lineBuffer, '\n'))
    {
        if (lineBuffer == "")
            continue;
        istringstream iss(lineBuffer);
        getline(iss, accId, ',');
        Transection trans;
        trans.load_csv_data(lineBuffer);
        accounts[stoi(accId)].transections.push_back(trans);
    }
    infile.close();
    return true;
}

bool loadStaticData(int *getStaticUserId, int *getStaticAccountId, int *getStaticTransId, unsigned long long *getStaticAccno, unsigned long long *getStaticDebitNo)
{
    ifstream infile("data_csv/staticData.csv", ios::in);
    if (!infile)
        return false;
    string lineBuffer = "";
    string accId = "";

    if (getline(infile, lineBuffer))
        *getStaticUserId = stoi(lineBuffer);
    else
        return false;
    if (getline(infile, lineBuffer))
        *getStaticAccountId = stoi(lineBuffer);
    else
        return false;
    if (getline(infile, lineBuffer))
        *getStaticTransId = stoi(lineBuffer);
    else
        return false;
    if (getline(infile, lineBuffer))
        *getStaticAccno = stoull(lineBuffer);
    else
        return false;
    if (getline(infile, lineBuffer))
        *getStaticDebitNo = stoull(lineBuffer);
    else
        return false;
    return true;
}
