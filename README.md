# Mini-Redis

A lightweight implementation of Redis-like functionality in C++. This project implements basic Redis commands with thread-safe operations, persistence, and key expiration.

## Features

- Basic Redis commands (SET, GET, DELETE)
- Thread-safe operations
- Key expiration (TTL)
- Append-Only File (AOF) persistence
- Multi-client support with thread pool
- Unit tests with Google Test

## Prerequisites

- C++17 compatible compiler (g++ or clang++)
- CMake (version 3.10 or higher)
- Google Test framework
- pthread library

### Installing Dependencies

#### macOS
```bash
brew install cmake googletest
```

#### Ubuntu/Debian
```bash
sudo apt-get install cmake libgtest-dev
```

#### CentOS/RHEL
```bash
sudo yum install cmake gtest-devel
```

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/yourusername/MiniRedis.git
cd MiniRedis
```

2. Create and enter build directory:
```bash
mkdir build
cd build
```

3. Generate build files:
```bash
cmake ..
```

4. Build the project:
```bash
make
```

## Running Tests

From the build directory:
```bash
./run_tests
```

## Running the Server

From the build directory:
```bash
./mini-redis
```

The server will start listening on port 6379.

## Testing with a Client

You can use telnet to test the server:
```bash
telnet localhost 6379
```

Example commands:
```
SET mykey myvalue
GET mykey
SET mykey myvalue EX 10  # Set with 10 seconds expiration
DELETE mykey
QUIT
```

## Project Structure

- `src/` - Source files
  - `main.cpp` - Server entry point
  - `database.cpp/h` - Database operations
  - `commands.cpp/h` - Command processing
  - `persistence.cpp/h` - AOF persistence
  - `thread_pool.cpp/h` - Thread pool implementation
- `tests/` - Unit tests
- `build/` - Build directory (generated)

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 