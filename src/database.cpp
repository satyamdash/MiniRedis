#include "database.h"
#include <chrono>

std::string Database::set(const std::string& key, const std::string& value, int ttl) {
    std::lock_guard<std::mutex> lock(dbMutex);
    data[key] = value;
    
    if (ttl > 0) {
        expiryMap[key] = std::chrono::steady_clock::now() + std::chrono::seconds(ttl);
    }
    
    return "OK";
}

std::string Database::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(dbMutex);
    auto it = data.find(key);

    if (it != data.end()) {
        if (expiryMap.count(key) && std::chrono::steady_clock::now() > expiryMap[key]) {
            data.erase(key);
            expiryMap.erase(key);
            return "NULL";
        }
        return it->second;
    }
    return "NULL";
}

std::string Database::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(dbMutex);
    if (data.erase(key)) {
        expiryMap.erase(key);
        return "DELETED";
    }
    return "KEY NOT FOUND";
}

void Database::checkExpiry() {
    std::lock_guard<std::mutex> lock(dbMutex);
    for (auto it = expiryMap.begin(); it != expiryMap.end(); ) {
        if (std::chrono::steady_clock::now() > it->second) {
            data.erase(it->first);
            it = expiryMap.erase(it);
        } else {
            ++it;
        }
    }
}
