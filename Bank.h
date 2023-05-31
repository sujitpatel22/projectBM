#pragma once
#include <iostream>
#include <cstring>
#include <string>
// #include <ctype>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "dependencies.h"
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
     unsigned long long setDebitNo = 4481980023086427ULL;
     ofstream accounts_csv;
     ofstream users_csv;
     ofstream transection_csv;
     ofstream staticData;

public:
     void menu();
     bool home(int);
     int _register();
     int login();
     bool logout(int);
     bool createAccount(int);
     bool addAccount(Account &newAcc, User &user);
     bool send(int);
     bool deposit(int);
     bool withdraw(int);
     bool showDebitCard(int);
     bool accInfo(int);
     bool listAccTransections(int);
     bool closeAccount(int);
     int getSelectedAccId(int);

     vector<Account> *getAccounts()
     {
          return &accounts;
     }
     vector<User> *getUsers()
     {
          return &users;
     }
     int *getStaticUserId() { return &setUserId; }
     int *getStaticAccountId() { return &setAccId; }
     int *getStaticTransId() { return &setTransId; }
     unsigned long long *getStaticAccno() { return &setAccNo; }
     unsigned long long *getStaticDebitNo() { return &setDebitNo; }

     // Opening the data file for synchronus data update
     bool openCSV()
     {
          accounts_csv = ofstream("data_csv/accounts_data.csv", ios::app);
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
     bool loadStaticData()
     {
          staticData = ofstream("data_csv/staticData.csv", ios::trunc);
          if (!staticData)
          {
               cout << "Error loading the staticData_csv file!";
               return false;
          }
          return true;
     }

     // To close the application
     void saveStaticData()
     {
          loadStaticData();
          staticData << setUserId << endl;
          staticData << setAccId << endl;
          staticData << setTransId << endl;
          staticData << setAccNo << endl;
          staticData << setDebitNo << endl;
          staticData.close();
     }
};

// Main Menu, User needs to login or regisgter to access more operations
void Bank::menu()
{
     WINDOW *menu;
     int option = 0;
     int selected = 0;
     while (true)
     {
          clear();
          refresh();
          menu = newwin(LINES, COLS, 0, 0);
          refresh();
          setBackgroundColor(menu);
          keypad(menu, true);
          noecho();
          mvwprintw(menu, 1, (COLS - strlen(" Main menu ")) / 2, " Main menu ");
          // system("cls");

          option = 0;
          selected = 0;
          string options[3] = {"Register", "Login", "Exit"};
          while (true)
          {
               for (int i = 0; i < 3; i++)
               {
                    if (i == selected)
                         wattron(menu, A_REVERSE);
                    mvwprintw(menu, (LINES / 2) - 3 + (i * 2), (COLS - strlen(options[i].c_str())) / 2, options[i].c_str());
                    wattroff(menu, A_REVERSE);
               }
               wrefresh(menu);
               option = wgetch(menu);
               if (option == KEY_UP)
               {
                    if (selected != 0)
                         selected--;
               }
               else if (option == KEY_DOWN)
               {
                    if (selected != 2)
                         selected++;
               }
               else if (option == 10)
                    break;
               else
                    continue;
          }

          delwin(menu);
          endwin();
          clear();
          if (selected == 0)
          {
               try
               {
                    int newUserId = Bank::_register();
                    Bank::home(newUserId);
               }
               catch (exception e)
               {
                    ;
               }
          }
          else if (selected == 1)
          {
               int UserLoginId = Bank::login();
               if (UserLoginId >= 0)
               {
                    Bank::home(UserLoginId);
               }
          }
          else
               exit(0);
     }
}

bool Bank::home(int _userId)
{
     clear();
     refresh();
     WINDOW *home;
     int option = 0;
     int selected = 0;
     while (true)
     {
          clear();
          refresh();
          saveStaticData();
          home = newwin(LINES, COLS, 0, 0);
          wrefresh(home);
          setBackgroundColor(home);
          keypad(home, true);
          noecho();
          mvwprintw(home, 1, (COLS - strlen(" Welcome ")) / 2, " Welcome ");
          option = 0;
          selected = 0;
          string options[9] = {"Create Account", "Send Money", "Deposit", "withdraw", "Show Debit Card", "View Account info", "View Account transections", "Close account", "Logout"};
          while (true)
          {
               for (int i = 0; i < 9; i++)
               {
                    if (i == selected)
                         wattron(home, A_REVERSE);
                    mvwprintw(home, (LINES / 2) - 9 + (i * 2), (COLS - strlen(options[i].c_str())) / 2, options[i].c_str());
                    wattroff(home, A_REVERSE);
               }
               wrefresh(home);
               cbreak();
               option = wgetch(home);
               if (option == KEY_UP)
               {
                    if (selected != 0)
                         selected--;
               }
               else if (option == KEY_DOWN)
               {
                    if (selected != 8)
                         selected++;
               }
               else if (option == 10)
                    break;
               else
                    continue;
          }

          delwin(home);
          endwin();
          clear();
          if (selected == 0)
          {
               try
               {
                    createAccount(_userId);
               }
               catch (exception e)
               {
                    ;
               }
          }
          else if (selected == 1)
          {
               send(_userId);
          }
          else if (selected == 2)
          {
               deposit(_userId);
          }
          else if (selected == 3)
          {
               withdraw(_userId);
          }
          else if (selected == 4)
          {
               showDebitCard(_userId);
          }
          else if (selected == 5)
          {
               accInfo(_userId);
          }
          else if (selected == 6)
          {
               listAccTransections(_userId);
          }
          else if (selected == 7)
          {
               closeAccount(_userId);
          }
          else if (selected == 8)
          {
               if (logout(_userId))
               {
                    return true;
               }
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
     createAccount(newUser.getUserId());
     // newUser.save_csv_data(users_csv);
     return newUser.getUserId();
}

int Bank::login()
{
     clear();
     refresh();
     string username;
     string password;
     WINDOW *loginWin = newwin(LINES, COLS, 0, 0);
     wrefresh(loginWin);
     setBackgroundColor(loginWin);
     noecho();
     mvwprintw(loginWin, 1, (COLS - strlen(" Login ")) / 2, " Login ");
     mvwprintw(loginWin, LINES / 2, (COLS - strlen("Enter Username")) / 2, "Enter Username");
     wrefresh(loginWin);
     username = input_string(loginWin);
     wclear(loginWin);
     setBackgroundColor(loginWin);
     mvwprintw(loginWin, LINES / 2, (COLS - strlen("Enter Password")) / 2, "Enter password");
     wrefresh(loginWin);
     password = input_string(loginWin);
     for (auto user : users)
     {
          if (user.getUsername() == username)
               if (user.authenticate(username, password))
               {
                    delwin(loginWin);
                    endwin();
                    clear();
                    return user.getUserId();
               }
     }
     mvwprintw(loginWin, LINES / 2, (COLS - strlen("User not found!")) / 2, "User not found!");
     wrefresh(loginWin);
     pauseConsole();
     delwin(loginWin);
     endwin();
     clear();
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
          WINDOW *notif = newwin(LINES, COLS, 0, 0);
          wrefresh(notif);
          setBackgroundColor(notif);
          mvwprintw(notif, 1, (COLS - strlen(" Cannot create account ")) / 2, " Cannot create account ");
          mvwprintw(notif, LINES / 2, (COLS - strlen("--------------------------------")) / 2, "Maximum account limit is 3!");
          wrefresh(notif);
          pauseConsole();
          return false;
     }
     int option;
     User *user = &users[_userId];
     Account newAcc = Account(_userId, setAccId++, ++setAccNo, ++setDebitNo, user->getPhoneNo());
     if (addAccount(newAcc, *user))
     {
          newAcc.save_csv_data(accounts_csv);
          user->save_csv_data(users_csv);
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
     clear();
     refresh();
     WINDOW *sendWin = newwin(LINES, COLS, 0, 0);
     wrefresh(sendWin);
     setBackgroundColor(sendWin);
     keypad(sendWin, true);
     noecho();
     mvwprintw(sendWin, 0, (COLS - strlen(" Send Payment ")) / 2, " Send Payment ");

     int option = 0;
     int selected = 0;
     string str_mode;
     string UPIid;
     int reciever_acc = 0;
     Account *reciever;
     float amount;
     string pin;

     mvwprintw(sendWin, 2, (COLS - strlen("Choose Payment mode")) / 2, "Choose Payment mode");
     string options[3] = {
         "UPI id",
         "Account number",
         "Debit Card"
     };
     int i = 0;
     while (true)
     {
          for (i = 0; i < 3; i++)
          {
               if (i == selected)
                    wattron(sendWin, A_REVERSE);
               mvwprintw(sendWin, (LINES / 2) - 2 + (i * 2), (COLS - strlen(options[i].c_str())) / 2, options[i].c_str());
               wattroff(sendWin, A_REVERSE);
          }
          if (selected == 3)
          {
               wattron(sendWin, A_REVERSE);
               mvwprintw(sendWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
          }
          else
          {
               wattroff(sendWin, A_REVERSE);
               mvwprintw(sendWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
          }

          wrefresh(sendWin);
          option = wgetch(sendWin);
          if (option == KEY_UP)
          {
               if (selected != 0)
                    selected--;
          }
          else if (option == KEY_DOWN)
          {
               if (selected != 2)
                    selected++;
          }
          else if (option == 10)
               break;
          else
               continue;
     }
     if (selected == 3)
     {
          returnBack(sendWin);
          return false;
     }
     int sender_acc = getSelectedAccId(_userId);
     Account *sender = &accounts[sender_acc];
     do
     {
          werase(sendWin);
          setBackgroundColor(sendWin);
          mvwprintw(sendWin, LINES / 2, (COLS - strlen("Enter amount")) / 2, "Enter amount");
          wrefresh(sendWin);
          amount = roundToDecimal(input_float(sendWin));
          if (amount > sender->getBalance())
          {
               mvwprintw(sendWin, LINES - 2, (COLS - strlen("Low Account Balance!")) / 2, "Low Account Balance!");
               wrefresh(sendWin);
          }
          else if (amount == -1)
          {
               returnBack(sendWin);
               return false;
          }
     } while (amount <= 0 || amount > sender->getBalance());

     werase(sendWin);
     setBackgroundColor(sendWin);
     if (selected == 0)
     {
          str_mode = "UPI";
          do
          {
               bool upi_found = false;
               werase(sendWin);
               setBackgroundColor(sendWin);
               mvwprintw(sendWin, LINES / 2, (COLS - strlen("Enter UPI id")) / 2, "Enter UPi id");
               wrefresh(sendWin);
               UPIid = input_string(sendWin);
               if (UPIid == (sender->getUpi()))
               {
                    mvwprintw(sendWin, LINES - 2, (COLS - strlen("Sender and Reciever acount (UPI) cannot be same!")) / 2, "Sender and Reciever acount (UPI) cannot be same!");
                    wrefresh(sendWin);
                    continue;
               }
               for (auto acc : accounts)
               {
                    if (acc.getUpi().compare(UPIid) == 0)
                    {
                         reciever_acc = acc.getAccId();
                         upi_found = true;
                         break;
                    }
               }
               if (!upi_found)
               {
                    mvwprintw(sendWin, LINES - 2, (COLS - strlen("UPI id not found!")) / 2, "UPI id not found!");
                    wrefresh(sendWin);
                    continue;
               }
               else if (UPIid == "-1")
               {
                    returnBack(sendWin);
                    return false;
               }
               break;
          } while (UPIid.length() < 4 || UPIid == (sender->getUpi()));
     }
     else if (selected == 1)
     {
          str_mode = "Account number";
          unsigned long long acc_number;
          do
          {
               bool acc_found = false;
               werase(sendWin);
               setBackgroundColor(sendWin);
               mvwprintw(sendWin, LINES / 2, (COLS - strlen("Enter Account number")) / 2, "Enter Account number");
               wrefresh(sendWin);
               acc_number = input_ullong(sendWin);
               if (acc_number == sender->getAccNumber())
               {
                    mvwprintw(sendWin, LINES - 2, (COLS - strlen("Sender and Reciever acount (number) cannot be same!")) / 2, "Sender and Reciever acount (number) cannot be same!");
                    wrefresh(sendWin);
                    continue;
               }
               for (auto acc : accounts)
               {
                    if (acc.getAccNumber() == acc_number)
                    {
                         reciever_acc = acc.getAccId();
                         acc_found = true;
                         break;
                    }
               }
               if (!acc_found)
               {
                    mvwprintw(sendWin, LINES - 2, (COLS - strlen("Account not found!")) / 2, "Account not found!");
                    wrefresh(sendWin);
                    continue;
               }
               else if (acc_number == 0)
               {
                    returnBack(sendWin);
                    return false;
               }
               break;
          } while (to_string(acc_number).length() < 13 || acc_number == sender->getAccNumber());
     }
     reciever = &accounts[reciever_acc];
     do
     {
          werase(sendWin);
          setBackgroundColor(sendWin);
          mvwprintw(sendWin, LINES / 2, (COLS - strlen("Enter transection pin")) / 2, "Enter transectuion pin");
          wrefresh(sendWin);
          pin = input_string(sendWin);
          if (pin == "-1")
          {
               returnBack(sendWin);
               return false;
          }

     } while (pin != sender->getPin());

     sender->setBalance(sender->getBalance() - amount);
     sender->save_csv_data(accounts_csv);
     reciever->setBalance(reciever->getBalance() + amount);
     reciever->save_csv_data(accounts_csv);

     // To add transection entry in the user's account in vector<Transection> transections
     Transection sendTrans(sender->getAccId(), setTransId, "send", to_string(roundToDecimal(amount)), sender->getAccHolder(), reciever->getAccHolder(), str_mode);
     sender->transections.push_back(sendTrans);
     sendTrans.save_csv_data(transection_csv);
     Transection recieveTrans(reciever->getAccId(), setTransId, "recieved", to_string(roundToDecimal(amount)), sender->getAccHolder(), reciever->getAccHolder(), str_mode);
     reciever->transections.push_back(recieveTrans);
     recieveTrans.save_csv_data(transection_csv);
     ++setTransId;

     werase(sendWin);
     setBackgroundColor(sendWin);
     mvwprintw(sendWin, 2, (COLS - strlen("Payment Successful!")) / 2, "Payment Successful!");
     string label = "Debited ";
     string notif = label.append(to_string(amount)).append(" from account ").append(to_string(sender->getAccNumber()));
     mvwprintw(sendWin, LINES / 2 - 1, (COLS - notif.length()) / 2, notif.c_str());
     label = "Creadited ";
     notif = label.append(to_string(amount)).append(" in account ").append(to_string(reciever->getAccNumber()));
     mvwprintw(sendWin, LINES / 2 + 1, (COLS - notif.length()) / 2, notif.c_str());
     wrefresh(sendWin);

     pauseConsole();
     delwin(sendWin);
     endwin();
     clear();
     return true;
}

// To deposite money in any account.
// It is expected that the process is done by the admin in the backend.....
bool Bank::deposit(int _userId)
{
     clear();
     refresh();
     WINDOW *depositeWin = newwin(LINES, COLS, 0, 0);
     wrefresh(depositeWin);
     setBackgroundColor(depositeWin);
     noecho();
     mvwprintw(depositeWin, 1, (COLS - strlen(" Diposit ")) / 2, " Diposit ");

     Account *deposit_acc;
     float amount;
     char pin[4];
     int accId = getSelectedAccId(_userId);
     if (accId == -1)
     {
          returnBack(depositeWin);
          return false;
     }
     deposit_acc = &accounts[accId];
     // To input amount
     do
     {
          werase(depositeWin);
          setBackgroundColor(depositeWin);
          mvwprintw(depositeWin, (LINES / 2), (COLS - strlen("Enter Amount:")) / 2, "Enter Amount:");
          wrefresh(depositeWin);
          amount = roundToDecimal(input_float(depositeWin));
          if (amount == -1)
          {
               returnBack(depositeWin);
               return false;
          }
     } while (amount <= 0 || amount > 99999);

     deposit_acc->setBalance(deposit_acc->getBalance() + amount);
     deposit_acc->save_csv_data(accounts_csv);
     // To add transection entry in the user's account in vector<Transection> transections
     Transection sendTrans(deposit_acc->getAccId(), setTransId, "diposit", to_string(roundToDecimal(amount)), to_string(deposit_acc->getAccNumber()), "Cash", "Online");
     deposit_acc->transections.push_back(sendTrans);
     sendTrans.save_csv_data(transection_csv);
     ++setTransId;

     string label = "Diposited ";
     string notif = "";

     notif = label.append(to_string(amount)).append(" in account ").append(to_string(deposit_acc->getAccNumber()));
     mvwprintw(depositeWin, LINES - 4, (COLS - notif.length()) / 2, notif.c_str());
     wrefresh(depositeWin);
     pauseConsole();
     delwin(depositeWin);
     endwin();
     clear();
     return true;
}

// To withdraw money from any account
bool Bank::withdraw(int _userId)
{
     clear();
     refresh();
     WINDOW *withdrawWin = newwin(LINES, COLS, 0, 0);
     wrefresh(withdrawWin);
     setBackgroundColor(withdrawWin);
     noecho();
     mvwprintw(withdrawWin, 1, (COLS - strlen(" Withdraw ")) / 2, " Withdraw ");

     Account *withdraw_acc;
     float amount;
     string pin;
     int accId = getSelectedAccId(_userId);
     if (accId == -1)
     {
          returnBack(withdrawWin);
          return false;
     }
     withdraw_acc = &accounts[accId];
     do
     {
          werase(withdrawWin);
          setBackgroundColor(withdrawWin);
          mvwprintw(withdrawWin, LINES / 2, (COLS - strlen("Enter amount")) / 2, "Enter amount");
          wrefresh(withdrawWin);
          amount = roundToDecimal(input_float(withdrawWin));
          if (amount > withdraw_acc->getBalance())
          {
               mvwprintw(withdrawWin, LINES - 4, (COLS - strlen("Low Account Balance!")) / 2, "Low Account Balance!");
               wrefresh(withdrawWin);
          }
          else if (amount == -1)
          {
               returnBack(withdrawWin);
               return false;
          }
     } while (amount <= 0 || amount > withdraw_acc->getBalance());
     // to verify PIN
     do
     {
          werase(withdrawWin);
          setBackgroundColor(withdrawWin);
          mvwprintw(withdrawWin, LINES / 4, (COLS - strlen("Enter transection pin")) / 2, "Enter transection pin");
          wrefresh(withdrawWin);
          pin = input_string(withdrawWin);
          if (pin == "-1")
          {
               returnBack(withdrawWin);
               return false;
          }
     } while (pin != withdraw_acc->getPin());

     withdraw_acc->setBalance(withdraw_acc->getBalance() - amount);
     withdraw_acc->save_csv_data(accounts_csv);
     // To add transection entry in the user's account in vector<Transection> transections
     Transection sendTrans(withdraw_acc->getAccId(), setTransId, "withdraw", to_string(roundToDecimal(amount)), to_string(withdraw_acc->getAccNumber()), "Cash", "ATM");
     withdraw_acc->transections.push_back(sendTrans);
     sendTrans.save_csv_data(transection_csv);
     ++setTransId;

     string notif = "Withdrawn ";
     notif = notif.append(to_string(amount));
     notif = notif.append(" from account ");
     notif = notif.append(to_string(withdraw_acc->getAccNumber()));
     mvwprintw(withdrawWin, LINES - 2, (COLS - notif.length()) / 2, notif.c_str());
     wrefresh(withdrawWin);
     pauseConsole();
     delwin(withdrawWin);
     endwin();
     clear();
     return true;
}

// To revel Debit Card
bool Bank::showDebitCard(int _userId)
{
     clear();
     refresh();
     WINDOW *debitWin = newwin(LINES, COLS, 0, 0);
     wrefresh(debitWin);
     setBackgroundColor(debitWin);
     noecho();
     mvwprintw(debitWin, 1, (COLS - strlen(" Debit Card ")) / 2, " Debit Card ");

     Account *debitAcc;
     string pin;
     int accId = getSelectedAccId(_userId);
     if (accId == -1)
     {
          returnBack(debitWin);
          return false;
     }
     debitAcc = &accounts[accId];
     do
     {
          werase(debitWin);
          setBackgroundColor(debitWin);
          mvwprintw(debitWin, LINES / 2, (COLS - strlen("Enter transection pin")) / 2, "Enter transection pin");
          wrefresh(debitWin);
          pin = input_string(debitWin);
          if (pin == "-1")
          {
               returnBack(debitWin);
               return false;
          }
     } while (pin != debitAcc->getPin());
     debitAcc->revelDebitCard();

     delwin(debitWin);
     endwin();
     clear();
     return true;
}

// To view details of current user's accounts
bool Bank::accInfo(int _userId)
{
     Account *acc;
     int accId = getSelectedAccId(_userId);
     string pin;

     clear();
     refresh();
     WINDOW *infoWin = newwin(LINES, COLS, 0, 0);
     wrefresh(infoWin);
     setBackgroundColor(infoWin);
     noecho();
     box(infoWin, 0, 0);
     mvwprintw(infoWin, 1, (COLS - strlen(" Account Info ")) / 2, " Account Info ");

     if (accId == -1)
     {
          returnBack(infoWin);
          return false;
     }
     acc = &accounts[accId];

     werase(infoWin);
     setBackgroundColor(infoWin);
     mvwprintw(infoWin, (LINES / 2), (COLS - strlen("Enter PIN to verify:")) / 2, "Enter PIN to verify:");
     wrefresh(infoWin);
     pin = input_string(infoWin);
     if (acc->getPin() != pin)
     {
          mvwprintw(infoWin, LINES - 2, (COLS - strlen("Wrong Pin!")) / 2, "Wrong Pin!");
          wrefresh(infoWin);
          pauseConsole();
          delwin(infoWin);
          endwin();
          clear();
          return false;
     }
     else
     {
          werase(infoWin);
          setBackgroundColor(infoWin);
          string label = "Account type ";
          mvwprintw(infoWin, (LINES / 2) - 6, (COLS - strlen("---------------------------")) / 2, (label.append(acc->accType)).c_str());
          label = "Account holder ";
          mvwprintw(infoWin, (LINES / 2) - 4, (COLS - strlen("---------------------------")) / 2, (label.append(acc->getAccHolder())).c_str());
          label = "Account Number: ";
          mvwprintw(infoWin, (LINES / 2) - 2, (COLS - strlen("---------------------------")) / 2, (label.append(to_string(acc->getAccNumber()))).c_str());
          label = "Debit card Number: ";
          mvwprintw(infoWin, (LINES / 2), (COLS - strlen("---------------------------")) / 2, (label.append(to_string(acc->getDebitNumber()))).c_str());
          label = "UPI id: ";
          mvwprintw(infoWin, (LINES / 2) + 2, (COLS - strlen("---------------------------")) / 2, (label.append(acc->getUpi())).c_str());
          label = "Available balance : Rs. ";
          mvwprintw(infoWin, (LINES / 2) + 4, (COLS - strlen("---------------------------")) / 2, (label.append(to_string(acc->getBalance()))).c_str());
          label = "IFSC Code: ";
          mvwprintw(infoWin, (LINES / 2) + 6, (COLS - strlen("---------------------------")) / 2, (label.append(acc->IFSCcode)).c_str());
     }
     wrefresh(infoWin);
     pauseConsole();
     delwin(infoWin);
     endwin();
     clear();
     return true;
}

// To list all the transections for the current user's accounts (any one)
bool Bank::listAccTransections(int _userId)
{
     Account *acc;
     int accId = getSelectedAccId(_userId);
     string pin;

     clear();
     refresh();
     WINDOW *transectionWin = newwin(LINES, COLS, 0, 0);
     wrefresh(transectionWin);
     setBackgroundColor(transectionWin);
     noecho();
     mvwprintw(transectionWin, 0, (COLS - strlen(" Account transections ")) / 2, " Account transections ");

     if (accId == -1)
     {
          returnBack(transectionWin);
          return false;
     }
     acc = &accounts[accId];

     werase(transectionWin);
     setBackgroundColor(transectionWin);
     mvwprintw(transectionWin, (LINES / 2), (COLS - strlen("Enter PIN to verify:")) / 2, "Enter PIN to verify:");
     wrefresh(transectionWin);
     pin = input_string(transectionWin);
     if (acc->getPin() != pin)
     {
          mvwprintw(transectionWin, LINES - 2, (COLS - strlen("Wrong Pin!")) / 2, "Wrong Pin!");
          wrefresh(transectionWin);
          pauseConsole();
          delwin(transectionWin);
          endwin();
          clear();
          return false;
     }
     acc->listTransections();
     delwin(transectionWin);
     endwin();
     clear();
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

int Bank::getSelectedAccId(int _userId)
{
     WINDOW *selectAccWin;
     clear();
     refresh();
     selectAccWin = newwin(LINES, COLS, 0, 0);
     wrefresh(selectAccWin);
     setBackgroundColor(selectAccWin);
     keypad(selectAccWin, true);
     noecho();
     mvwprintw(selectAccWin, 2, (COLS - strlen(" Select Account ")) / 2, " Select Account ");

     int option;
     int selected = 0;
     Account *acc;
     if (users[_userId].accIds.size() == 0)
          return -1;
     else if (users[_userId].accIds.size() == 1)
          return users[_userId].accIds[0];
     else
     {
          mvwprintw(selectAccWin, 2, (COLS - strlen("Select Account")) / 2, "Select Account");
          while (true)
          {
               for (int i = 0; i < users[_userId].accIds.size(); i++)
               {
                    if (i == selected)
                         wattron(selectAccWin, A_REVERSE);
                    mvwprintw(selectAccWin, (LINES / 2) - 2 + (i * 2), (COLS - strlen("--------------")) / 2, to_string(users[_userId].accNumbers[i]).c_str());
                    wattroff(selectAccWin, A_REVERSE);
               }
               if (selected == users[_userId].accIds.size())
               {
                    wattron(selectAccWin, A_REVERSE);
                    mvwprintw(selectAccWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
               }
               else
               {
                    wattroff(selectAccWin, A_REVERSE);
                    mvwprintw(selectAccWin, LINES - 5, (COLS - strlen("Back")) / 2, "Back");
               }
               wrefresh(selectAccWin);
               cbreak();
               option = wgetch(selectAccWin);
               if (option == KEY_UP)
               {
                    if (selected != 0)
                         selected--;
               }
               else if (option == KEY_DOWN)
               {
                    if (selected != users[_userId].accIds.size())
                         selected++;
               }
               else if (option == 10)
                    break;
          }
     }
     delwin(selectAccWin);
     endwin();
     clear();
     if (selected == users[_userId].accIds.size())
     {
          return -1;
     }
     return selected;
}