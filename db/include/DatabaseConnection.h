#pragma once

#include <sqlite3.h>
#include <string>

class DatabaseConnection {
public:
    DatabaseConnection();
    ~DatabaseConnection();

    bool openDatabase();
    void closeDatabase();
    sqlite3* getDatabase();

private:
    sqlite3* database;
    std::string databaseName;
};