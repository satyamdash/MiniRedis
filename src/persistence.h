#pragma once

#include <string>
#include <unordered_map>

class Persistence {
private:
    static const std::string AOF_FILE;

public:
    static void appendToAOF(const std::string& command);
    static void loadFromAOF(std::unordered_map<std::string, std::string>& database);
    static void rewriteAOF(const std::unordered_map<std::string, std::string>& database);
    static void checkAOFSize();
}; 