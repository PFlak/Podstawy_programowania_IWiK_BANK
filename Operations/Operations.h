#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include "Domain.h"

class Operations {
public:


    Operations(sqlite3* db);

    // --------------USERS OPERATIONS --------------
    bool createUser(
        const User user
    );

    bool updateUser(
        const User user
    );

    bool deleteUser(const User user);

    User getUserByMail(const std::string email);

    vector<User> getAllUsers();

    bool createTransfer(
        int senderAccountId, 
        int recipientAccountId, 
        const std::string& currency,
        double amount, 
        const std::string& header, 
        const std::string& info
    );

    // --------------ACCOUNTS OPERATIONS --------------
    bool createAccount(int userId, const std::string& currency, int balance, const std::string& type, double interestRate);
    std::vector<std::string> displayUserTransfers(int userId);
    bool createTransaction(
        int accountId, 
        const std::string& currency, 
        double amount
    );
    std::vector<std::string> displayUserTransactions(int userId);
    std::vector<std::string> displayTransactionsAndTotalTransfers(int userId);

private:
    sqlite3* database;
};

class OperationFactory
{
public:
    static Operations CreateOperations();
};