# projectBM
A bank management system using C++.
#
Please Note that project is not complete and would consist some incomplete and malfunctioning functions.
#
The Application consists of 5 modules linked with the main cpp file:
Bank.h
User.h
Account.h
Transections.h
Validations.h
#
bank.h: Access and store the users, accounts, transections and validations objects but reverse is not possible unless the information is passed though a function.
Account.h: consists functions to create and manage account details.
User.h: creates and manages user accounts and a perticular user's all account IDs and account Numbers.
Transection.h: Creates and save a transection entry for every payment done- transfers, deposits, withdrawls.
Validations.h: Every input required by the user in the application is processed through a series of checks and exception handlers to get safe and valid input from the user.
# Working:
1. The CSV files are first loaded to load whole data in the application:
there are total 3 csv files to be loaded:
users_csv, accounts_csv and transection csv (please ignore the users_csv file and need not to edit any related function in User.h and function bool loadUsers() in main.cpp).
For every action performed, the 'Bank' class in bank.h file updates the data in the csv files with updated data like account balance, adding new transection details, etc.
#
Note: Some libraries may not work on github codespaces!
#
Note: Feel free to update any relevent info in the file to mention the left things. Thankyou!
