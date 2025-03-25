#include "commands.h"
#include <sstream>
#include <vector>

std::string CommandProcessor::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) tokens.push_back(token);
    if (tokens.empty()) return "ERROR: Empty Command";

    std::string cmd = tokens[0];

    if (cmd == "SET") {
        if (tokens.size() < 3) return "ERROR: Usage SET key value [EX seconds]";
        
        int ttl = -1;
        if (tokens.size() == 5 && tokens[3] == "EX") {
            ttl = std::stoi(tokens[4]);
        }

        std::string result = db.set(tokens[1], tokens[2], ttl);
        if (result == "OK") {
            Persistence::appendToAOF(command);
        }
        return result;
    } 
    else if (cmd == "GET" && tokens.size() == 2) {
        return db.get(tokens[1]);
    } 
    else if (cmd == "DELETE" && tokens.size() == 2) {
        std::string result = db.del(tokens[1]);
        if (result == "DELETED") {
            Persistence::appendToAOF(command);
        }
        return result;
    }
    return "ERROR: Invalid Command";
}
