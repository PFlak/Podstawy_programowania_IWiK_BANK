#include "Operations.h"


Operations OperationFactory::CreateOperations()
{
    DatabaseConnection connection = DatabaseConnection();
    return Operations(connection);
}

Operations::Operations(DatabaseConnection db) : database(db) {}


// --------------USERS OPERATIONS --------------
// register 
bool Operations::createUser(
    string password,
    string name,
    string surname,
    string personalCode,
    string mail,
    string phoneNumber,
    UserFactory* factory) {
    User user = factory->CreateUser(password, name, surname, personalCode, mail, phoneNumber);
    const char* query = R"(
        INSERT INTO users (password, name, surname, personalCode, mail, phoneNumber, isEmployee)
        VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7);
    )";// TO DO admin handling
    sqlite3_stmt* statement;
    
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        const char* errorMessage = sqlite3_errmsg(database.getDatabase());
        printf("Error executing SQL statement: %s\n", errorMessage);
        sqlite3_finalize(statement);
        database.closeDatabase();
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, user.password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, user.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, user.surname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, user.personalCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 5, user.mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, user.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 7, user.isEmployee);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    database.closeDatabase();

    return result == SQLITE_DONE;
}


// edit user data 
bool Operations::updateUser(
    string password,
    string name,
    string surname,
    string personalCode,
    string mail,
    string phoneNumber,
    UserFactory* factory) {
    User user = factory->CreateUser(password, name, surname, personalCode, mail, phoneNumber);
    const char* query = R"(
        UPDATE users SET password = ?, name = ?, surname = ?, personalCode = ?, mail = ?, phoneNumber = ?, isEmployee = ?  WHERE id = ?;
    )";//to do: doda� isEmployee handling

    sqlite3_stmt* statement;
    
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, user.password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, user.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, user.surname.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, user.personalCode.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 5, user.mail.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, user.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 7, user.isEmployee);
    sqlite3_bind_int(statement, 8, user.id);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    database.closeDatabase();

    return result == SQLITE_DONE;
}

// delete 
bool Operations::deleteUser(
    string password,
    string name,
    string surname,
    string personalCode,
    string mail,
    string phoneNumber,
    UserFactory* factory) {
    User user = factory->CreateUser(password, name, surname, personalCode, mail, phoneNumber);

    const char* query = "DELETE FROM users WHERE id = ?;";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameter to the query
    sqlite3_bind_int(statement, 1, user.id);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    database.closeDatabase();

    return result == SQLITE_DONE;
}

User Operations::getUserByMail(const std::string email)
{
    const char* query = "SELECT * FROM users WHERE mail = ?1;";
    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return User();
    }

    // Bind the parameters to the query
    sqlite3_bind_text(statement, 1, email.c_str(), -1, SQLITE_STATIC);

    User user;
    int rowResult = sqlite3_step(statement);
    if (rowResult == SQLITE_ROW)
    {
        user.id = int(sqlite3_column_int(statement, 0));
        const unsigned char* password = sqlite3_column_text(statement, 1);
        user.password = string(reinterpret_cast<const char*>(password));
        user.name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
        user.surname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        user.personalCode = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
        user.mail = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5)));
        user.phoneNumber = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
        user.isEmployee = bool(sqlite3_column_int(statement, 7));
    }
    
    sqlite3_finalize(statement);
    database.closeDatabase();

    return user;
}

// display users 
std::vector<User> Operations::getAllUsers() {
    std::vector<User> users;

    const char* query = "SELECT * FROM users;";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return users;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        User user;
        user.id = int(sqlite3_column_int(statement, 0));
        user.password = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        user.name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
        user.surname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        user.personalCode = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
        user.mail = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5)));
        user.phoneNumber = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
        user.isEmployee = int(sqlite3_column_int(statement, 7));
        users.push_back(user);
    }

    sqlite3_finalize(statement);
    database.closeDatabase();

    return users;
}

// --------------ACCOUNTS OPERATIONS --------------
// create account 
bool Operations::createAccount(Account account) {
    const char* query = "INSERT INTO accounts (user_id, currency, balance, type, interest_rate) VALUES (?, ?, 200, ?, ?);";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_int(statement, 1, account.userId);
    sqlite3_bind_text(statement, 2, account.currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, account.type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(statement, 4, account.interestRate);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    database.closeDatabase();

    return result == SQLITE_DONE;
}

vector<Account> Operations::GetUserAccounts(int id)
{
    std::vector<Account> accounts;

    const char* query = "SELECT * FROM accounts WHERE user_id = ?1;";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return accounts;
    }
    sqlite3_bind_int(statement, 1, id);

    while (sqlite3_step(statement) == SQLITE_ROW) {
        Account account;
        account.accountNumber = int(sqlite3_column_int(statement, 0));
        account.userId = int(sqlite3_column_int(statement, 1));

        account.currency = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
        account.balance = int(sqlite3_column_int(statement, 3));
        account.type = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
        account.interestRate = int(sqlite3_column_int(statement, 5));
    }

    sqlite3_finalize(statement);
    database.closeDatabase();

    return accounts;
}

// transfer 
bool Operations::createTransfer(Transfer transfer) {
    const char* query = R"(
        INSERT INTO transfers (sender_account_id, recipient_account_id, currency, amount, header, info, time)
        VALUES (?, ?, ?, ?, ?, ?, datetime('now'));
    )";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return false;
    }

    // Bind the parameters to the query
    sqlite3_bind_int(statement, 1, transfer.senderAccountId);
    sqlite3_bind_int(statement, 2, transfer.recipientAccountId);
    sqlite3_bind_text(statement, 3, transfer.currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(statement, 4, transfer.amount);
    sqlite3_bind_text(statement, 5, transfer.header.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 6, transfer.info.c_str(), -1, SQLITE_STATIC);

    result = sqlite3_step(statement);
    sqlite3_finalize(statement);
    database.closeDatabase();

    return result == SQLITE_DONE;
}

// display transfers 
std::vector<Transfer> Operations::displayUserTransfers(int accountNumber) {
    std::vector<Transfer> transfers;

    const char* query = R"(
        SELECT * FROM transfers
        WHERE sender_account_id IN (SELECT account_number FROM accounts WHERE account_number = ?)
        OR recipient_account_id IN (SELECT account_number FROM accounts WHERE account_number = ?);
    )";

    sqlite3_stmt* statement;
    database.openDatabase();
    int result = sqlite3_prepare_v2(database.getDatabase(), query, -1, &statement, nullptr);
    if (result != SQLITE_OK) {
        return transfers;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        Transfer transfer;
        transfer.id = int(sqlite3_column_int(statement, 0));
        transfer.senderAccountId = int(sqlite3_column_int(statement, 1));
        transfer.recipientAccountId = int(sqlite3_column_int(statement, 2));
        transfer.currency = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        transfer.amount = sqlite3_column_double(statement, 4);
        transfer.header = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5)));
        transfer.info = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
        transfer.time = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7)));
        transfers.push_back(transfer);
    }

    sqlite3_finalize(statement);
    database.closeDatabase();

    return transfers;
}
