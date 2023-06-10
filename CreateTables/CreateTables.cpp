#include "CreateTables.h"

CreateTables::CreateTables(DatabaseConnection database) {
	database = database;
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
            phoneNumber TEXT NOT NULL,
            isEmployee INTEGER NOT NULL
        );
    )";
    database.openDatabase();
	char* errorMessage = nullptr;
    sqlite3_stmt* statement;
	int result = sqlite3_exec(database.getDatabase(), query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}
    const char* query2 = R"(
INSERT INTO users 
VALUES ('admin', 'admin', 'administrator', '00000000000', 'admin@admin.com', '+00 000 000 000', 1);
)";
    int result2 = sqlite3_exec(database.getDatabase(), query, nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        return false;
    }

    database.closeDatabase();
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
    database.openDatabase();
	char* errorMessage = nullptr;
	int result = sqlite3_exec(database.getDatabase(), query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}

    database.closeDatabase();

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
    database.openDatabase();

	char* errorMessage = nullptr;
	int result = sqlite3_exec(database.getDatabase(), query, nullptr, nullptr, &errorMessage);
	if (result != SQLITE_OK) {
		return false;
	}
    database.closeDatabase();


	return true;
}
