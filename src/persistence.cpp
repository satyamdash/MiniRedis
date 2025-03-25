#include "persistence.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

const std::string Persistence::AOF_FILE = "database.aof";

void Persistence::appendToAOF(const std::string& command) {
    std::ofstream aof(AOF_FILE, std::ios::app);
    if (aof.is_open()) {
        aof << command << std::endl;
        aof.close();
    }
}

void Persistence::loadFromAOF(std::unordered_map<std::string, std::string>& database) {
    std::ifstream aof(AOF_FILE);
    std::string line;
    while (std::getline(aof, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        if (tokens.size() == 3 && tokens[0] == "SET") {
            database[tokens[1]] = tokens[2];
        } else if (tokens.size() == 2 && tokens[0] == "DELETE") {
            database.erase(tokens[1]);
        }
    }
}

void Persistence::rewriteAOF(const std::unordered_map<std::string, std::string>& database) {
    std::ofstream newAOF("database.aof.tmp");
    if (!newAOF.is_open()) return;

    for (const auto& pair : database) {
        newAOF << "SET " << pair.first << " " << pair.second << "\n";
    }

    newAOF.close();
    rename("database.aof.tmp", "database.aof");
}

void Persistence::checkAOFSize() {
    std::ifstream aof(AOF_FILE, std::ios::ate);
    if (aof.is_open() && aof.tellg() > 1024 * 1024) {  // 1MB threshold
        std::cout << "Triggering AOF compaction...\n";
    }
}
