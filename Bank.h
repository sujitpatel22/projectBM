#pragma once
#include <iostream>
#include <cstring>
#include <string>
// #include <ctype>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "validations.h"
// #include <ncurses.h>
#include "User.h"
#include "Account.h"
#include "Transection.h"
using namespace std;

class Bank
{
private:
     vector<Account> accounts;
     vector<User> users;
     int setUserId = 0;
     int setAccId = 0;
     int setTransId = 0;
     unsigned long long setAccNo = 5500202310000ULL;
     ofstream accounts_csv;
     ofstream users_csv;
     ofstream transection_csv;

public:
     void menu();
     bool home(int);
     int _register();
     int login();
     bool logout(int);
     bool authenticate(int, string);
     bool createAccount(int);
     bool addAccount(Account &newAcc, User &user);
     bool send(int);
     bool deposit(int);
     bool withdraw(int);
     bool accInfo(int);
     bool listAccTransections(int);
     bool closeAccount(int);

     vector<Account> getAccounts()
     {
          return accounts;
     }
     vector<User> getUsers()
     {
          return users;
     }

     // Opening the data file for synchronus data update
     bool openCSV()
     {
          accounts_csv = ofstream("data_csv/accounsts_data.csv", ios::app);
          if (!accounts_csv)
          {
               cout << "Error loading the accounts_data_csv file!";
               return false;
          }
          users_csv = ofstream("data_csv/users_data.csv", ios::app);
          if (!users_csv)
          {
               cout << "Error loading the users_data_csv file!";
               return false;
          }
          transection_csv = ofstream("data_csv/transections_data.csv", ios::app);
          if (!transection_csv)
          {
               cout << "Error loading the transections_data_csv file!";
               return false;
          }
          return true;
     }
};

// Main Menu, User needs to login or regisgter to access more operations
void Bank::menu()
{
     do
     {
          int option;
          do
          {
               system("cls");
               cout << "Select Operation: " << endl
                    << endl;
               cout << "[1]\tRegister" << endl;
               cout << "[2]\tLogin" << endl;
               cout << "[0]\tExit" << endl;

               option = input_int();
          } while (option < 0 || option > 2);
          if (option == 1)
          {
               int newUserId = Bank::_register();
               Bank::home(newUserId);
          }
          else if (option == 2)
          {
               int UserLoginId = Bank::login();
               if (UserLoginId >= 0)
               {
                    Bank::home(UserLoginId);
               }
          }
          else
               exit(0);
     } while (true);
}

bool Bank::home(int _userId)
{
     int option;
     while (true)
     {
          system("cls");
          cout << "[1]\tCreate Account" << endl;
          cout << "[2]\tSend Money" << endl;
          cout << "[3]\tDeposit" << endl;
          cout << "[4]\twithdraw" << endl;
          cout << "[5]\tView Account info" << endl;
          cout << "[6]\tView Account transections" << endl;
          cout << "[7]\tClose account" << endl;
          cout << "[8]\tLogout" << endl;

          cout << endl
               << "Select Operation:\t";
          option = input_int();

          if (option == 1)
               createAccount(_userId);
          else if (option == 2)
               send(_userId);
          else if (option == 3)
               deposit(_userId);
          else if (option == 4)
               withdraw(_userId);
          else if (option == 5)
               accInfo(_userId);
          else if (option == 6)
               listAccTransections(_userId);
          else if (option == 7)
               closeAccount(_userId);
          else if (option == 8)
          {
               if (logout(_userId))
               {
                    return true;
               }
          }
          else
          {
               continue;
          }
     }
}

// Register & login the User
// New Uer will be created based on the automatic userId generating mechanism through the bank itself.
// Thereafter, new User will be added the 'users' vector and will re directed the User home page.
int Bank::_register()
{
     User newUser(setUserId++, users);
     users.push_back(newUser);
     return newUser.getUserId();
     // newUser.save_csv_data(users_csv);
}

int Bank::login()
{
     system("cls");
     string username;
     string password;
     cout
         << "Username: ";
     username = input_string();
     cout << endl
          << "Password: " << endl;
     SetConsoleEcho(false);
     password = input_string();
     SetConsoleEcho(true);
     for (auto user : users)
     {
          if (user.getUsername() == username)
               if (user.authenticate(username, password))
               {
                    return user.getUserId();
               }
               else
               {
                    cout << endl
                         << "Invalid UserId or Password!" << endl;
               }
     }
     cout << endl
          << "User not found!" << endl;
     pauseConsole();
     return -1;
}

// To logout the current logedin user by setting its "sessionSet = false"
// After logout, the user is redirected into the application main menu
bool Bank::logout(int userId)
{
     users[userId].logout();
     return true;
}

// To insert new 'Account' object and new 'User' object in accounts<vector> & users<vector> respectively.
// Function will allocate the nearest available space, from beginning of the respective vector,
// without disturbing the index of other elements.
bool Bank::addAccount(Account &newAcc, User &user)
{
     user.accIds.push_back(newAcc.accId);
     user.accNumbers.push_back(newAcc.accNumber);
     for (int i = 0; i < accounts.size(); i++)
          if (accounts[i].accId == -1)
          {
               accounts[i] = newAcc;
               return true;
          }
     accounts.push_back(newAcc);
     return true;
}

// Create new Account and new account Id & new Account Number based on the automatic
// accountId(accId) generating mechanism through the bank itself.
// If one User created multiple accounts, then each account have same account-userId,
// different accountId(accId) and different account Number(accNumber).
// Newly created account will bew added in the 'accounts' vector and
// accountId(accId) will be added in the user's account-Ids (accIds) vector.
bool Bank::createAccount(int _userId)
{
     if (accounts.size() >= 3)
     {
          cout << "You have reached the limit of number of accounts you can open!" << endl;
          pauseConsole();
          return false;
     }
     int option;
     User *user = &users[_userId];
     Account newAcc = Account(_userId, setAccId++, ++setAccNo, user->getPhoneNo());
     if (addAccount(newAcc, *user))
     {
          // newAcc.save_csv_data(accounts_csv);
          return true;
     }
     else
          return false;
}

// Send money, from one account to another
// 2 options to send, through UPI or through direct account number
// User will be displayed the list of their accounts to choose payment with. following the prompt to enter transection PIN.
bool Bank::send(int _userId)
{
     int option;
     string str_mode;
     string UPIid;
     unsigned long long acc_number;
     int reciever_acc;
     float amount;
     int pin;
     do
     {
          system("cls");
          cout << "Choose Payment mode" << endl;
          cout << "[1]\tUPI id" << endl;
          cout << "[2]\tAccount number" << endl;
          option = input_int();
     } while (option < 1 || option > 2);

     Account *sender;
     do
     {
          cout << endl
               << "Enter amount" << endl;
          amount = input_float();
     } while (amount <= 0);
     system("cls");
     if (users[_userId].accIds.size() == 0)
          return false;
     else if (users[_userId].accIds.size() == 1)
          sender = &accounts[users[_userId].accIds[0]];
     else
     {
          do
          {
               cout << endl
                    << "Select Account to pay from" << endl;
               for (int i = 0; i < users[_userId].accIds.size(); i++)
                    cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
               option = input_int();
          } while (option < 0 || option >= users[_userId].accIds.size());
          int sender_acc = users[_userId].accIds[option];
          sender = &accounts[sender_acc];
     }

     system("cls");
     if (option == 1)
     {
          str_mode = "UPI";
          cout << endl
               << "Enter UPI id" << endl;
          UPIid = input_string();
          if (UPIid.compare(sender->getUpi()))
          {

               cout << endl
                    << "Sender and Reciever acount cannot be same!" << endl;
               pauseConsole();
               return false;
          }
          for (auto acc : accounts)
          {
               if (acc.getUpi().compare(UPIid) == 0)
               {
                    reciever_acc = acc.getAccId();
                    goto verify;
               }
          }
          cout << endl
               << "Account not found!" << endl;
          pauseConsole();
          return false;
     }
     else
     {
          str_mode = "Account Number";
          cout << endl
               << "Enter Account number" << endl;
          acc_number = input_ullong();
          if (acc_number == sender->getAccNumber())
          {
               cout << endl
                    << "Sender and Reciever acount cannot be same!" << endl;
               pauseConsole();
               return false;
          }
          for (auto acc : accounts)
          {
               if (acc_number == acc.getAccNumber())
               {
                    reciever_acc = acc.getAccId();
                    goto verify;
               }
          }
          cout << endl
               << "Account not found!" << endl;
          pauseConsole();
          return false;
     }
verify:
     Account *reciever = &accounts[reciever_acc];
     system("cls");
     if (amount > sender->getBalance())
     {
          cout
              << endl
              << "Low Account Balance!" << endl
              << "Cannot proceed transection!" << endl;
          return false;
     }
     else
     {
          system("cls");
          cout << endl
               << "Enter transection pin" << endl;
          SetConsoleEcho(false);
          pin = input_int();
          SetConsoleEcho(true);
          if (pin == sender->getPin())
          {
               sender->setBalance(sender->getBalance() - amount);
               reciever->setBalance(reciever->getBalance() + amount);
               cout << endl
                    << "Payment Successful!" << endl;
               cout << "Debited " << amount << " from account " << sender->getAccNumber() << endl;
               cout << "Credited " << amount << " in account " << reciever->getAccNumber() << endl;

               // To add transection entry in the user's account in vector<Transection> transections
               Transection sendTrans(sender->getAccId(), setTransId, "send", amount, sender->getAccHolder(), reciever->getAccHolder(), str_mode);
               sender->transections.push_back(sendTrans);
               // sendTrans.save_csv_data(transection_csv);
               Transection recieveTrans(reciever->getAccId(), setTransId, "recieved", amount, sender->getAccHolder(), reciever->getAccHolder(), str_mode);
               reciever->transections.push_back(recieveTrans);
               // recieveTrans.save_csv_data(transection_csv);
               ++setTransId;
               pauseConsole();
               return true;
          }
          cout << endl
               << "Wrong Pin!" << endl;
          pauseConsole();
     }
     return false;
}

// To deposite money in any account.
// It is expected that the process is done by the admin in the backend.....
bool Bank::deposit(int _userId)
{
     system("cls");
     int option;
     float amount;
     int sender_acc;
     Account *deposite_acc;
     if (users[_userId].accIds.size() == 0)
          return false;
     else if (users[_userId].accIds.size() == 1)
          deposite_acc = &accounts[users[_userId].accIds[0]];
     else
     {
          do
          {
               cout << "Select Account to deposit in" << endl;
               for (int i = 0; i < users[_userId].accIds.size(); i++)
                    cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
               option = input_int();
          } while (option < 0 || option >= users[_userId].accIds.size());
          sender_acc = users[_userId].accIds[option];
          deposite_acc = &accounts[sender_acc];
     }
     do
     {
          system("cls");
          cout << endl
               << "Enter amount to pay: " << endl;
          amount = input_float();
     } while (amount <= 0);
     deposite_acc->setBalance(deposite_acc->getBalance() + amount);
     cout << endl
          << "Deposited " << amount << " in account " << deposite_acc->getAccNumber() << endl;

     // Updating the data_csv file upon account update.
     // Need to update the balance only.
     // {
     //      string line;
     //      string tempId;
     //      while(getline(accounts_csv, line, "\n"))
     //      {
     //           while(getline(line, tempId, ","))
     //           {
     //                if(stoi(tempId) == _userId)
     //                {

     //                }
     //           }
     //      }
     // }

     pauseConsole();
     return true;
}

// To withdraw money from any account
bool Bank::withdraw(int _userId)
{
     system("cls");
     int option;
     float amount;
     int accId;
     Account *withdraw_acc;
     if (users[_userId].accIds.size() == 0)
          return false;
     else if (users[_userId].accIds.size() == 1)
          withdraw_acc = &accounts[users[_userId].accIds[0]];
     else
     {
          do
          {
               cout << "Select Account to withdraw from" << endl;
               for (int i = 0; i < users[_userId].accIds.size(); i++)
                    cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
               option = input_int();
          } while (option < 0 || option >= users[_userId].accIds.size());
          accId = users[_userId].accIds[option];
          withdraw_acc = &accounts[accId];
     }
     do
     {
          cout << endl
               << "Enter amount to withdraw: " << endl;
          amount = input_float();
     } while (amount <= 0);
     cout << endl
          << "Enter transection pin" << endl;
     SetConsoleEcho(false);
     int pin = input_int();
     SetConsoleEcho(true);
     if (pin == withdraw_acc->getPin())
     {
          withdraw_acc->setBalance(withdraw_acc->getBalance() - amount);
          cout << endl
               << "Withdrawn " << amount << " from account " << withdraw_acc->getAccNumber() << endl;
          // To add transection entry in the user's account in vector<Transection> transections
          Transection sendTrans(withdraw_acc->getAccId(), setTransId, "withdraw", amount, to_string(withdraw_acc->getAccNumber()), "Cash", "ATM");
          withdraw_acc->transections.push_back(sendTrans);
          // sendTrans.save_csv_data(transection_csv);
          ++setTransId;
          pauseConsole();
          return true;
     }
     cout << endl
          << "Wrong Pin!" << endl;
     pauseConsole();
     return false;
}

// To view details of current user's accounts
bool Bank::accInfo(int _userId)
{
     system("cls");
     int option;
     int pin;
     Account *acc;
     if (users[_userId].accIds.size() == 0)
          return false;
     else if (users[_userId].accIds.size() == 1)
          acc = &accounts[users[_userId].accIds[0]];
     else
     {
          do
          {
               cout << "Select Account to show details" << endl;
               for (int i = 0; i < users[_userId].accIds.size(); i++)
                    cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
               option = input_int();
          } while (option < 0 || option >= users[_userId].accIds.size());
          int accId = users[_userId].accIds[option];
          acc = &accounts[accId];
     }

     cout << endl
          << "Enter PIN to verify:\t";
     pin = input_int();
     if (acc->getPin() != pin)
     {
          cout << endl
               << "Wrong Pin! " << endl;
          pauseConsole();
          return false;
     }
     else
     {
          system("cls");
          cout << "Account type: " << acc->accType << endl
               << endl;
          cout << "Account holder: " << acc->getAccHolder() << endl
               << endl;
          cout << "Account Number: " << acc->getAccNumber() << endl
               << endl;
          cout << "UPI id: " << acc->getUpi() << endl
               << endl;
          cout << "Available balance : Rs. " << acc->getBalance() << endl
               << endl;
          cout << "IFSC code" << acc->IFSCcode << endl
               << endl;

          pauseConsole();
          return true;
     }
}

// To list all the transections for the current user's accounts (any one)
bool Bank::listAccTransections(int _userId)
{
     system("cls");
     int option;
     Account *acc;
     if (users[_userId].accIds.size() == 0)
          return false;
     else if (users[_userId].accIds.size() == 1)
          acc = &accounts[users[_userId].accIds[0]];
     else
     {
          cout << "Select Account to show details" << endl;
          for (int i = 0; i < users[_userId].accIds.size(); i++)
               cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
          option = input_int();
          int accId = users[_userId].accIds[option];
          acc = &accounts[accId];
     }
     cout << endl
          << "Enter PIN to verify:\t";
     SetConsoleEcho(false);
     int pin = input_int();
     SetConsoleEcho(true);
     if (acc->getPin() != pin)
     {
          cout << endl
               << "Wrong Pin! " << endl;
          pauseConsole();
          return false;
     }
     acc->listTransections();
     cout << endl
          << "Press any key to continue!" << endl;
     cin.clear();
     cin.ignore();
     cin.get();
     return true;
}

bool Bank::closeAccount(int _userId)
{
     system("cls");
     int option;
     int close_acc;
     cout << "Select Account to close" << endl;
     int i = 0;
     for (; i < users[_userId].accIds.size(); i++)
          cout << "Account [" << i << "]\tAccount No: " << users[_userId].accNumbers[i] << endl;
     option = input_int();
     close_acc = users[_userId].accIds[option];
     char confirm = 'N';
     cout << "Enter Y to confirm | N to discard";
     cin >> confirm;
     if (confirm == 'Y' || confirm == 'y')
     {
          accounts[close_acc].updateAccId(-1);
          // users[_userId].removeAcc(i);
          return true;
     }
     return false;
}