#include <gtest/gtest.h>
#include "../src/persistence.h"
#include "../src/database.h"

class PersistenceTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::remove("database.aof");
    }
};

TEST_F(PersistenceTest, SaveAndLoadData) {
    Database db;
    db.set("key1", "value1");
    Persistence::appendToAOF("SET key1 value1");
    
    Database newDb;
    Persistence::loadFromAOF(newDb.getData());
    EXPECT_EQ(newDb.get("key1"), "value1");
}