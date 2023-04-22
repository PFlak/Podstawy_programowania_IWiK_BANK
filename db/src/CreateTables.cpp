#include "CreateTables.h"

CreateTables::CreateTables(sqlite3* db) {
    database = db;
}

bool CreateTables::createUserTable() {
    const char* query = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);";

    char* errorMessage = nullptr;
    int result = sqlite3_exec(database, query, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        return false;
    }

    return true;
}

bool CreateTables::createAccountTable() {
    const char* query = "CREATE TABLE IF NOT EXISTS accounts (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, balance INTEGER NOT NULL, FOREIGN KEY (user_id) REFERENCES
        char* errorMessage = nullptr;
    int result = sqlite3_exec(database, query, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        return false;
    }

    return true;
}