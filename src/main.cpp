#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include "thread_pool.h"
#include "database.h"
#include "commands.h"
#include "persistence.h"

#define PORT 6379
#define THREAD_COUNT 4

ThreadPool threadPool(THREAD_COUNT);
Database database;
CommandProcessor commandProcessor(database);

void handleClient(int clientSocket) {
    char buffer[1024] = {0};

    while (true) {
        int bytesRead = read(clientSocket, buffer, 1024);
        
        if (bytesRead <= 0) {
            std::cout << "Client disconnected.\n";
            break;
        }

        std::string command(buffer, bytesRead);
        command.erase(command.find_last_not_of(" \n\r\t") + 1);

        if (command.empty()) {
            continue;
        }

        if (command == "QUIT") {
            std::cout << "Client sent QUIT. Closing connection.\n";
            break;
        }

        std::string response = commandProcessor.processCommand(command);
        send(clientSocket, response.c_str(), response.length(), 0);
    }

    close(clientSocket);
}

void expireKeys() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        database.checkExpiry();
    }
}

int main() {
    // Load data from AOF file
    Persistence::loadFromAOF(database.getData());

    // Start expiration thread
    std::thread expirationThread(expireKeys);
    expirationThread.detach();

    // Setup server
    int serverFd, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(serverFd, (struct sockaddr*)&address, sizeof(address));
    listen(serverFd, 5);

    std::cout << "Mini-Redis Server Listening on Port " << PORT << std::endl;

    // Accept connections
    while ((clientSocket = accept(serverFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        threadPool.enqueue([clientSocket] {
            handleClient(clientSocket);
        });
    }

    return 0;
}
