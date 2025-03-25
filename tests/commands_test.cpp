#include <gtest/gtest.h>
#include "../src/commands.h"
#include "../src/database.h"

class CommandsTest : public ::testing::Test {
protected:
    Database db;
    CommandProcessor cmd{db};
};

TEST_F(CommandsTest, ValidSetCommand) {
    EXPECT_EQ(cmd.processCommand("SET key1 value1"), "OK");
}

TEST_F(CommandsTest, InvalidSetCommand) {
    EXPECT_EQ(cmd.processCommand("SET"), "ERROR: Usage SET key value [EX seconds]");
}

TEST_F(CommandsTest, ValidGetCommand) {
    cmd.processCommand("SET key1 value1");
    EXPECT_EQ(cmd.processCommand("GET key1"), "value1");
}

TEST_F(CommandsTest, InvalidGetCommand) {
    EXPECT_EQ(cmd.processCommand("GET"), "ERROR: Invalid Command");
} 