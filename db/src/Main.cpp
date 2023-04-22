#include "DatabaseConnection.h"
#include "CreateTables.h"

int main() {
    // łączymy się z bazą danych
    DatabaseConnection dbConnection;
    dbConnection.openDatabase();

    // tworzymy tabele w bazie danych
    CreateTables createTables;
    createTables.createUsersTable();
    createTables.createAccountsTable();

    // zamykamy połączenie z bazą danych
    dbConnection.closeDatabase();

    return 0;
}
