#include <gtest/gtest.h>
#include <DatabaseConnection.h>

TEST(DatabaseConnectionTest, OpenDatabaseTest) {
    DatabaseConnection dbConnection;
    ASSERT_TRUE(dbConnection.openDatabase());
}

TEST(DatabaseConnectionTest, CloseDatabaseTest) {
    DatabaseConnection dbConnection;
    dbConnection.openDatabase();
    ASSERT_TRUE(dbConnection.closeDatabase());
}
