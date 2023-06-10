#include "CreateTables.h"

CreateTables::CreateTables(sqlite3* db) {
	database = db;
}


bool CreateTables::createUserTable() {
	const char* query = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            password TEXT NOT NULL,
            name TEXT NOT NULL,
            surname TEXT NOT NULL,
            personalCode TEXT NOT NULL,
            mail TEXT NOT NULL,
            phoneNumber TEXT NOT NULL
            isEmployee INTEGER NOT NULL
        );
    )";

	char* errorMessage = nullptr;
	int result = sqlite3_exec(database, query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}

	return true;
}

bool CreateTables::createAccountTable() {
	const char* query = R"(
        CREATE TABLE IF NOT EXISTS accounts (
            account_number INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL,
            currency TEXT NOT NULL,
            balance INTEGER NOT NULL,
            type TEXT NOT NULL,
            interest_rate REAL,
            FOREIGN KEY (user_id) REFERENCES users (id)
        );
    )";

	char* errorMessage = nullptr;
	int result = sqlite3_exec(database, query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}

	return true;
}

bool CreateTables::createTransferTable() {
	const char* query = R"(
        CREATE TABLE IF NOT EXISTS transfers (
            id INTEGER PRIMARY KEY,
            sender_account_id INTEGER NOT NULL,
            recipient_account_id INTEGER NOT NULL,
            currency TEXT NOT NULL,
            amount REAL NOT NULL,
            header TEXT NOT NULL,
            info TEXT NOT NULL,
            time TEXT NOT NULL,
            FOREIGN KEY (sender_account_id) REFERENCES accounts (account_number),
            FOREIGN KEY (recipient_account_id) REFERENCES accounts (account_number)
        );
    )";

	char* errorMessage = nullptr;
	int result = sqlite3_exec(database, query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}

	return true;
}
