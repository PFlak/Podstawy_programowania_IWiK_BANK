#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection() {
    database = nullptr;
    databaseName = "mydatabase.db";
}

DatabaseConnection::~DatabaseConnection() {}

bool DatabaseConnection::openDatabase() {
    int result = sqlite3_open(databaseName.c_str(), &database);
    if (result != SQLITE_OK) {
        sqlite3_close(database);
        return false;
    }
    return true;
}

void DatabaseConnection::closeDatabase() {
    sqlite3_close(database);
}

sqlite3* DatabaseConnection::getDatabase() {
    return database;
}