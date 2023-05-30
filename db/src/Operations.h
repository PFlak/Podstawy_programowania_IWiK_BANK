#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

class Operations {
public:
    Operations(sqlite3* db);

    // --------------USERS OPERATIONS --------------
    bool createUser(
        const std::string& login, 
        const std::string& password, 
        const std::string& name,
        const std::string& surname, 
        const std::string& personalCode, 
        const std::string& mail,
        const std::string& phoneNumber
    );
    bool login(
        const std::string& login, 
        const std::string& password
    );
    bool editUserData(
        int userId, 
        const std::string& newUserId
    );
    bool changePassword(
        const std::string& emailOrLogin, 
        const std::string& newPassword
    );
    bool deleteUserById(int userId);
    std::vector<std::string> displayUsers();
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