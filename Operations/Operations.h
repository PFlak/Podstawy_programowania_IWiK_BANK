#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include "Domain.h"
#include "UserFactory.h"

class Operations {
public:
    Operations(sqlite3* db);

    // --------------USERS OPERATIONS --------------
    bool createUser(
        string login,
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber, 
        UserFactory *factory
    );

    bool updateUser(
        string login,
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber,
        UserFactory* factory
    );

    bool deleteUser(string login,
        string password,
        string name,
        string surname,
        string personalCode,
        string mail,
        string phoneNumber,
        UserFactory* factory);

    User getUserByMail(const std::string email);

    vector<User> getAllUsers();

    bool createTransfer(Transfer transfer);

    // --------------ACCOUNTS OPERATIONS --------------
    bool createAccount(Account account);
    std::vector<std::string> displayUserTransfers(int userId);
    bool createTransaction(
        int accountId, 
        const std::string& currency, 
        double amount
    );
    std::vector<std::string> displayUserTransactions(int userId);
    std::vector<std::string> displayTransactionsAndTotalTransfers(int userId);
    std::vector<std::string> displayTransactionsAndTransfers();

private:
    sqlite3* database;
};

class OperationFactory
{
public:
    static Operations CreateOperations();
};