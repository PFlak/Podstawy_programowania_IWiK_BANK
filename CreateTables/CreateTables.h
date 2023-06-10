#pragma once

#include <sqlite3.h>
#include <string>
#include "DatabaseConnection.h"

class CreateTables {
public:
    CreateTables(DatabaseConnection database);

    bool createUserTable();
    bool createAccountTable();
    bool createTransferTable();

private:
    DatabaseConnection database;
};