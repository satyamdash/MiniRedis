#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../src/database.h"

class DatabaseTest : public ::testing::Test {
protected:
    Database db;
};

TEST_F(DatabaseTest, SetAndGetValue) {
    EXPECT_EQ(db.set("key1", "value1"), "OK");
    EXPECT_EQ(db.get("key1"), "value1");
}

TEST_F(DatabaseTest, GetNonExistentKey) {
    EXPECT_EQ(db.get("nonexistent"), "NULL");
}

TEST_F(DatabaseTest, DeleteKey) {
    db.set("key1", "value1");
    EXPECT_EQ(db.del("key1"), "DELETED");
    EXPECT_EQ(db.get("key1"), "NULL");
}

TEST_F(DatabaseTest, ExpiryTest) {
    db.set("key1", "value1", 1); // 1 second TTL
    EXPECT_EQ(db.get("key1"), "value1");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(db.get("key1"), "NULL");
}