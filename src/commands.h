#pragma once

#include <string>
#include "database.h"
#include "persistence.h"

class CommandProcessor {
private:
    Database& db;

public:
    CommandProcessor(Database& database) : db(database) {}
    std::string processCommand(const std::string& command);
}; 