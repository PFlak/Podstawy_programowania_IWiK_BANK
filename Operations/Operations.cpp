#include "Operations.h"
#include "DataBaseConnection.h"

Operations OperationFactory::CreateOperations()
{
    DatabaseConnection connection = DatabaseConnection();
    sqlite3* db = connection.getDatabase();
    return Operations(db);
}

Operations::Operations(sqlite3* db) : database(db) {}


// --------------USERS OPERATIONS --------------
// register 
bool Operations::createUser(const User user) {
    const char* query = R"(
        INSERT INTO users (login, password, name, surname, personalCode, mail, phoneNumber)
        VALUES (?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement;
    

    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, user.login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, user.password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, user.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, user.surname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 5, user.personalCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, user.mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 7, user.phoneNumber.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}


// edit user data 
bool Operations::updateUser(const User user) {
    const char* query = R"(
        UPDATE users SET login = ?, password = ?, name = ?, surname = ?, personalCode = ?, mail = ?, phoneNumber = ? WHERE id = ?;
    )";//to do: dodaæ isEmployee handling

    sqlite3_stmt* statement;
    

    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, user.login.c_str(), - 1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, user.password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, user.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, user.surname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 5, user.personalCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, user.mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 7, user.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 8, user.id);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}

// delete 
bool Operations::deleteUser(const User user) {
    const char* query = "DELETE FROM users WHERE id = ?;";

    sqlite3_stmt* statement;
    
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameter to the query
    sqlite3_bind_int(statement, 1, user.id);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}

User Operations::getUserByMail(const std::string email)
{
    const char* query = "SELECT * FROM users WHERE email = ?;";
    sqlite3_stmt* statement;
    
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return User();
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, email.c_str(), -1, SQLITE_STATIC);

    User user;
    user.id = int(sqlite3_column_int(statement, 0));
    user.login = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
    user.password = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
    user.name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
    user.surname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
    user.personalCode = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5)));
    user.mail = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
    user.phoneNumber = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7)));

    sqlite3_finalize(statement);

    return user;
}

// display users 
std::vector<User> Operations::getAllUsers() {
    std::vector<User> users;

    const char* query = "SELECT * FROM users;";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return users;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        User user;
        user.id = int(sqlite3_column_int(statement, 0));
        user.login = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        user.password = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
        user.name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        user.surname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
        user.personalCode = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5)));
        user.mail = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
        user.phoneNumber = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7)));
        users.push_back(user);
    }

    sqlite3_finalize(statement);

    return users;
}

// --------------ACCOUNTS OPERATIONS --------------
// create account 
bool Operations::createAccount(int userId, const std::string& currency, int balance, const std::string& type, double interestRate) {
    const char* query = "INSERT INTO accounts (user_id, currency, balance, type, interest_rate) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_text(statement, 2, currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 3, balance);
    sqlite3_bind_text(statement, 4, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(statement, 5, interestRate);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}

// transfer 
bool Operations::createTransfer(int senderAccountId, int recipientAccountId, const std::string& currency,
    double amount, const std::string& header, const std::string& info) {
    const char* query = R"(
        INSERT INTO transfers (action, sender_account_id, recipient_account_id, currency, amount, header, info, time)
        VALUES (?, ?, ?, ?, ?, ?, ?, datetime('now'));
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, "Transfer", -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 2, senderAccountId);
    sqlite3_bind_int(statement, 3, recipientAccountId);
    sqlite3_bind_text(statement, 4, currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(statement, 5, amount);
    sqlite3_bind_text(statement, 6, header.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 7, info.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}

// display transfers 
std::vector<std::string> Operations::displayUserTransfers(int userId) {
    std::vector<std::string> transfers;

    const char* query = R"(
        SELECT * FROM transfers
        WHERE sender_account_id IN (SELECT account_number FROM accounts WHERE user_id = ?)
        OR recipient_account_id IN (SELECT account_number FROM accounts WHERE user_id = ?);
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return transfers;
    }

    // Bind the parameters to the query
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_int(statement, 2, userId);

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int transferId = sqlite3_column_int(statement, 0);
        const unsigned char* action = sqlite3_column_text(statement, 1);
        int senderAccountId = sqlite3_column_int(statement, 2);
        int recipientAccountId = sqlite3_column_int(statement, 3);
        const unsigned char* currency = sqlite3_column_text(statement, 4);
        double amount = sqlite3_column_double(statement, 5);
        const unsigned char* header = sqlite3_column_text(statement, 6);
        const unsigned char* info = sqlite3_column_text(statement, 7);
        const unsigned char* time = sqlite3_column_text(statement, 8);

        std::string transferInfo = "Transfer ID: " + std::to_string(transferId) +
            ", Action: " + reinterpret_cast<const char*>(action) +
            ", Sender Account ID: " + std::to_string(senderAccountId) +
            ", Recipient Account ID: " + std::to_string(recipientAccountId) +
            ", Currency: " + reinterpret_cast<const char*>(currency) +
            ", Amount: " + std::to_string(amount) +
            ", Header: " + reinterpret_cast<const char*>(header) +
            ", Info: " + reinterpret_cast<const char*>(info) +
            ", Time: " + reinterpret_cast<const char*>(time);

        transfers.push_back(transferInfo);
    }

    sqlite3_finalize(statement);

    return transfers;
}

// transaction 
bool Operations::createTransaction(int accountId, const std::string& currency, double amount) {
    const char* query = R"(
        INSERT INTO transactions (action, account_id, currency, amount, time)
        VALUES (?, ?, ?, ?, datetime('now'));
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, "Transaction", -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 2, accountId);
    sqlite3_bind_text(statement, 3, currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(statement, 4, amount);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);

    return result == SQLITE_DONE;
}

// display transactions 
std::vector<std::string> Operations::displayUserTransactions(int userId) {
    std::vector<std::string> transactions;

    const char* query = R"(
        SELECT * FROM transactions WHERE account_id IN (SELECT account_number FROM accounts WHERE user_id = ?);
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return transactions;
    }

    // Bind the parameters to the query
    sqlite3_bind_int(statement, 1, userId);

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int transactionId = sqlite3_column_int(statement, 0);
        const unsigned char* action = sqlite3_column_text(statement, 1);
        int accountId = sqlite3_column_int(statement, 2);
        const unsigned char* currency = sqlite3_column_text(statement, 3);
        double amount = sqlite3_column_double(statement, 4);
        const unsigned char* time = sqlite3_column_text(statement, 5);

        std::string transactionInfo = "Transaction ID: " + std::to_string(transactionId) +
            ", Action: " + reinterpret_cast<const char*>(action) +
            ", Account ID: " + std::to_string(accountId) +
            ", Currency: " + reinterpret_cast<const char*>(currency) +
            ", Amount: " + std::to_string(amount) +
            ", Time: " + reinterpret_cast<const char*>(time);

        transactions.push_back(transactionInfo);
    }

    sqlite3_finalize(statement);

    return transactions;
}

// display transactions and transfers 
std::vector<std::string> Operations::displayTransactionsAndTransfers() {
    std::vector<std::string> transactionsAndTransfers;

    const char* query = R"(
        SELECT * FROM transactions
        UNION ALL
        SELECT * FROM transfers;
    )";

    sqlite3_stmt* statement;
    int result = sqlite3_prepare_v2(database, query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return transactionsAndTransfers;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        const unsigned char* action = sqlite3_column_text(statement, 1);
        int accountId = sqlite3_column_int(statement, 2);
        const unsigned char* currency = sqlite3_column_text(statement, 3);
        double amount = sqlite3_column_double(statement, 4);
        const unsigned char* time = sqlite3_column_text(statement, 5);

        std::string info = "ID: " + std::to_string(id) +
            ", Action: " + reinterpret_cast<const char*>(action) +
            ", Account ID: " + std::to_string(accountId) +
            ", Currency: " + reinterpret_cast<const char*>(currency) +
            ", Amount: " + std::to_string(amount) +
            ", Time: " + reinterpret_cast<const char*>(time);

        transactionsAndTransfers.push_back(info);
    }

    sqlite3_finalize(statement);

    return transactionsAndTransfers;
}
