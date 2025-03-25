#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>

class Database {
private:
    std::unordered_map<std::string, std::string> data;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> expiryMap;
    std::mutex dbMutex;
public:
    std::string set(const std::string& key, const std::string& value, int ttl = -1);
    std::string get(const std::string& key);
    std::string del(const std::string& key);
    void checkExpiry();
    std::unordered_map<std::string, std::string>& getData() { return data; }
}; 