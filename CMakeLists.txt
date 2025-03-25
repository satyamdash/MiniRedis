cmake_minimum_required(VERSION 3.10)
project(mini-redis)

set(CMAKE_CXX_STANDARD 17)

# Find GTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add main executable
add_executable(mini-redis
    src/main.cpp
    src/database.cpp
    src/commands.cpp
    src/persistence.cpp
    src/thread_pool.cpp
)

target_link_libraries(mini-redis
    pthread
)

# Add test executable
add_executable(run_tests
    tests/database_test.cpp
    src/database.cpp
)

target_link_libraries(run_tests
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    pthread
) 