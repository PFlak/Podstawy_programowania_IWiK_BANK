#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include "Domain.h"
#include "UserFactory.h"
#include "DataBaseConnection.h"

class Operations {
public:
    Operations(DatabaseConnection db);

    // --------------USERS OPERATIONS --------------
    bool createUser(
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber, 
        UserFactory *factory
    );

    bool updateUser(
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber,
        UserFactory* factory
    );

    bool deleteUser(
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber,
        UserFactory* factory
    );

    User getUserByMail(const std::string email);

    vector<User> getAllUsers();


    // --------------ACCOUNTS OPERATIONS --------------
    bool createAccount(Account account);
    bool createTransfer(Transfer transfer);

    vector<Transfer> displayUserTransfers(int account_number);

    vector<Account> getAccount(int account_number);

    bool uploadAccount(int account_number)


private:
    DatabaseConnection database;
};

class OperationFactory
{
public:
    static Operations CreateOperations();
};