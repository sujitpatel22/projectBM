#pragma once
#include <iostream>
#include <fstream>
#include "Bank.h"
#include "User.h"
#include "Transection.h"
#include <string>
#include <vector>
#include "dependencies.h"
using namespace std;

class Account
{
private:
    int accId;
    int accUserId;
    unsigned long long accNumber;
    unsigned long long debitNumber;
    string accHolder = "";
    float balance;
    string UPI = "";
    string accPin;

public:
    // Making class 'Bank' as friend; so that bank can access all the data of accounts.
    friend class Bank;
    string accType;
    string IFSCcode = "AMT0474005";
    // Vector of transection objects to store transection entries
    vector<Transection> transections;

    Account()
    {
        accId = 0, accUserId = 0, accNumber = 0;
        balance = 0, accPin = "";
    }
    Account(int _userId, int setAccId, unsigned long long _accNo, unsigned long long _debitNo, long _phoneNo)
    {
        accId = setAccId;
        accNumber = _accNo;
        accUserId = _userId;
        debitNumber = _debitNo;

        refresh();
        WINDOW *newAccountWin = newwin(LINES, COLS, 0, 0);
        wrefresh(newAccountWin);
        setBackgroundColor(newAccountWin);
        keypad(newAccountWin, true);
        noecho();
        mvwprintw(newAccountWin, 0, (COLS - strlen(" Create Account ")) / 2, " Create Account ");
        mvwprintw(newAccountWin, LINES / 2, (COLS - strlen("Welcome to Account creation")) / 2, "Welcome to Account creation");
        wrefresh(newAccountWin);
        pauseConsole();

        int option = 0;
        int selected = 0;
        bool proceed = true;
        werase(newAccountWin);
        setBackgroundColor(newAccountWin);
        mvwprintw(newAccountWin, 2, (COLS - strlen("Choose Payment mode")) / 2, "Choose Payment mode");
        string options[2] = {"Savings", "Current"};
        try
        {
            while (proceed)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (i == selected)
                        wattron(newAccountWin, A_REVERSE);
                    mvwprintw(newAccountWin, (LINES / 2) - 1 + i, (COLS - strlen(options[i].c_str())) / 2, options[i].c_str());
                    wattroff(newAccountWin, A_REVERSE);
                }
                if (selected == 2)
                {
                    wattron(newAccountWin, A_REVERSE);
                    mvwprintw(newAccountWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
                }
                else
                {
                    wattroff(newAccountWin, A_REVERSE);
                    mvwprintw(newAccountWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
                }
                wrefresh(newAccountWin);
                cbreak();
                option = wgetch(newAccountWin);
                if (option == KEY_UP)
                {
                    if (selected != 0)
                        selected--;
                }
                else if (option == KEY_DOWN)
                {
                    if (selected != 1)
                        selected++;
                }
                else if (option == 10)
                {
                    accType = options[selected];
                    break;
                }
                else
                    continue;
            }
            if (selected == 2)
            {
                throw runtime_error("go_back");
            }
            if (proceed)
                do
                {
                    werase(newAccountWin);
                    setBackgroundColor(newAccountWin);
                    mvwprintw(newAccountWin, LINES / 2, (COLS - strlen("Enter account Holders name:")) / 2, "Enter account Holders name:");
                    wrefresh(newAccountWin);
                    accHolder = input_strictString(newAccountWin);
                    if (accHolder == "-1")
                    {
                        throw runtime_error("go_back");
                    }
                } while ((accHolder.length() < 4 || accHolder.length() > 25) && proceed);
            if (proceed)
                do
                {
                    werase(newAccountWin);
                    setBackgroundColor(newAccountWin);
                    mvwprintw(newAccountWin, LINES / 2, (COLS - strlen("Set transection pin (4 digit):")) / 2, "Set transection pin (4 digit):");
                    wrefresh(newAccountWin);
                    accPin = input_string(newAccountWin);
                    if (accPin == "-1")
                    {
                        throw runtime_error("go_back");
                    }
                } while ((accPin.length() != 4) && proceed);
            if (proceed)
                do
                {
                    werase(newAccountWin);
                    setBackgroundColor(newAccountWin);
                    mvwprintw(newAccountWin, LINES / 2, (COLS - strlen("Enter Opening balance (min 1):")) / 2, "Enter Opening balance (min 1):");
                    wrefresh(newAccountWin);
                    balance = roundToDecimal(input_float(newAccountWin));
                    if (balance == -1)
                    {
                        throw runtime_error("go_back");
                    }
                } while ((balance <= 0 || balance > 999999) && proceed);
            if (proceed)
            {
                UPI = to_string(_userId) + to_string(_phoneNo % 1000) + to_string(_accNo % 1000) + "@AmiBnk";
                werase(newAccountWin);
                setBackgroundColor(newAccountWin);
                mvwprintw(newAccountWin, 2, (COLS - strlen("Success! Account created!")) / 2, "Success! Account created!");
                string label = "Account holder's name:    ";
                mvwprintw(newAccountWin, LINES / 2 - 4, (COLS - strlen("-------------------------")) / 2, (label.append(accHolder)).c_str());
                label = "Account number:    ";
                mvwprintw(newAccountWin, LINES / 2 - 2, (COLS - strlen("-------------------------")) / 2, (label.append(to_string(accNumber))).c_str());
                label = "Debit card number:    ";
                mvwprintw(newAccountWin, LINES / 2, (COLS - strlen("-------------------------")) / 2, (label.append(to_string(debitNumber))).c_str());
                label = "Balance:    ";
                mvwprintw(newAccountWin, LINES / 2 + 2, (COLS - strlen("-------------------------")) / 2, (label.append(to_string(balance))).c_str());
                label = "UPI id:    ";
                mvwprintw(newAccountWin, LINES / 2 + 4, (COLS - strlen("-------------------------")) / 2, (label.append(UPI)).c_str());
                wrefresh(newAccountWin);
                pauseConsole();
            }
            delwin(newAccountWin);
            endwin();
            clear();
        }
        catch (exception e)
        {
            throw runtime_error("go_back");
        }
    }

    // To update the account
    void accUpdateName(string _accHolder) { accHolder = _accHolder; }
    // To get account Id
    const int getAccId() { return accId; }
    // To get the Account Number
    void updateAccId(int newAccId) { accId = newAccId; }
    // To get the Account Number
    const unsigned long long getAccNumber() { return accNumber; }
    // To get the Debit card number
    const unsigned long long getDebitNumber() { return debitNumber; }
    // To get the acount holder's name

    string getAccHolder() { return accHolder; }
    // To get the transection pin.
    const string getPin() { return accPin; }
    // to set the balance
    void setBalance(const float _balance) { balance = roundToDecimal(_balance); }
    // To get the balance
    const float getBalance() { return (roundToDecimal(balance)); }
    // To ge UPI
    string getUpi() { return UPI; }
    // To close the account

    // To revel the Debit Card
    void revelDebitCard()
    {
        clear();
        refresh();
        WINDOW *debitWin = newwin(LINES, COLS, 0, 0);
        wrefresh(debitWin);
        setBackgroundColor(debitWin);
        noecho();
        mvwprintw(debitWin, 1, (COLS - strlen(" Debit Card ")) / 2, " Debit Card ");
        wrefresh(debitWin);

        int cardHeight = 12;
        int cardWidth = 35;
        WINDOW *card = newwin(cardHeight, cardWidth, (LINES - cardHeight) / 2, (COLS - cardWidth) / 2);
        box(card, 0, 0);
        wrefresh(card);
        curs_set(0);
        wbkgdset(card, COLOR_PAIR(0) | ' ');
        mvwprintw(card, 1, 2, "Rupay");
        mvwprintw(card, 1, cardWidth-9, "AmiBank");
        mvwprintw(card, cardHeight - 4, 2, accHolder.c_str());
        mvwprintw(card, cardHeight - 2, 2, to_string(debitNumber).c_str());
        mvwprintw(card, cardHeight - 4, cardWidth-5, "512");
        mvwprintw(card, cardHeight - 2, cardWidth-7, "05/28");
        wrefresh(card);
        pauseConsole();
        delwin(card);
        delwin(debitWin);
        endwin();
        clear();
    }

    // to list all transections for *this account
    bool listTransections()
    {
        refresh();
        // clear();
        static WINDOW *TransectionWin = newwin(LINES, COLS, 0, 0);
        wrefresh(TransectionWin);
        setBackgroundColor(TransectionWin);
        noecho();
        scrollok(TransectionWin, true);
        mvwprintw(TransectionWin, 0, (COLS - strlen(" Account Transections ")) / 2, " Account Transections ");
        string label;
        if (transections.size() == 0)
        {
            mvwprintw(TransectionWin, (LINES / 2), (COLS - strlen("-----------------------------")) / 2, "Empty! No transections made yet");
        }
        else
        {
            for (int i = 0; i < transections.size(); i++)
            {
                label = transections[i].transId.append("    ").append(transections[i].type).append("    ").append(transections[i].amount).append("    ").append(transections[i].from).append("    ").append(transections[i].to_acc).append(transections[i].transTime);
                mvwprintw(TransectionWin, LINES / 2 - (transections.size() / 2), (COLS - label.length()) / 2, label.c_str());
            }
        }
        wrefresh(TransectionWin);
        pauseConsole();
        delwin(TransectionWin);
        endwin();
        clear();
        return true;
    }

    // ~Account()
    // {
    //     cout << "Account closed | Closing balanace: " << balance << endl;
    // }

    void save_csv_data(ofstream &accounts_csv)
    {
        // Save the created object in account_csv file.
        accounts_csv << accId << "," << accUserId << "," << static_cast<long long>(accNumber) << "," << static_cast<long long>(debitNumber) << "," << accHolder << "," << balance << "," << UPI << "," << accPin << "," << accType << endl;
    }

    bool load_csv_data(string lineBuffer)
    {
        istringstream iss(lineBuffer);
        string fieldBuffer;
        getline(iss, fieldBuffer, ',');
        accId = stoi(fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accUserId = stoi(fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accNumber = (stoull(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        debitNumber = (stoull(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        accHolder = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        balance = (stof(fieldBuffer));
        getline(iss, fieldBuffer, ',');
        UPI = (fieldBuffer);
        getline(iss, fieldBuffer, ',');
        accPin = fieldBuffer;
        getline(iss, fieldBuffer, ',');
        accType = (fieldBuffer);

        return true;
    }
};