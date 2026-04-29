cmake_minimum_required(VERSION 3.20)
project(Lab_DoublyLinkedList)

set(CMAKE_CXX_STANDARD 17)

# Додаємо вихідні файли логіки (без main.cpp)
set(SOURCE_FILES Team.cpp Team.h)

# Основна програма
add_executable(Lab_main main.cpp ${SOURCE_FILES})

# --- Налаштування Google Test ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тестовий виконуваний файл (UnitTest.cpp замінює main.cpp)
add_executable(UnitTest UnitTest.cpp ${SOURCE_FILES})
target_link_libraries(UnitTest GTest::gtest_main)

# Дозволяємо виявлення тестів у CLion
include(GoogleTest)
gtest_discover_tests(UnitTest)