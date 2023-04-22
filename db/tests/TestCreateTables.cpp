#include <gtest/gtest.h>
#include <CreateTables.h>

TEST(CreateTablesTest, CreateUsersTableTest) {
    CreateTables createTables;
    ASSERT_TRUE(createTables.createUsersTable());
}

TEST(CreateTablesTest, CreateAccountsTableTest) {
    CreateTables createTables;
    ASSERT_TRUE(createTables.createAccountsTable());
}
