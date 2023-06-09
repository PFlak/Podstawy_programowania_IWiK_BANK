#pragma once

#include <sqlite3.h>
#include <string>

class CreateTables {
public:
    CreateTables(sqlite3* db);

    bool createUserTable();
    bool createAccountTable();
    bool createTransferTable();

private:
    sqlite3* database;
};