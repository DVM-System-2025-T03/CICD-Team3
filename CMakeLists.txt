cmake_minimum_required(VERSION 3.9)# 최소 cmake 버전 명시
project(sonar_scanner_example)# 프로젝트 이름 명시

set(CMAKE_CXX_STANDARD 17)# 사용할 C++ 표준(여기선 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(googletest json)

include_directories(/opt/homebrew/include ${CMAKE_SOURCE_DIR}/src)

enable_testing()

# AuthCodeManagerTest
add_executable(AuthCodeManagerTest
    test/Domain/Auth/AuthCodeManagerTest.cpp
    src/Domain/Auth/AuthCodeManager.cpp
)

target_include_directories(AuthCodeManagerTest PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/test
)

target_link_libraries(AuthCodeManagerTest
    gtest
    gmock
    gtest_main
    pthread
    nlohmann_json::nlohmann_json
)
add_test(NAME AuthCodeManagerTest COMMAND AuthCodeManagerTest)

# BeverageManagerTest
add_executable(BeverageManagerTest
    test/Domain/Beverage/BeverageManagerTest.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
)

target_include_directories(BeverageManagerTest PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/test
)

target_link_libraries(BeverageManagerTest
    gtest
    gmock
    gtest_main
    pthread
    nlohmann_json::nlohmann_json
)
add_test(NAME BeverageManagerTest COMMAND BeverageManagerTest)

# CreditCardTest
add_executable(CreditCardTest
    test/Domain/Credit/CreditCardTest.cpp
    src/Domain/Credit/CreditCard.cpp
)

target_link_libraries(CreditCardTest
    gtest
    gmock
    gtest_main
    pthread
    nlohmann_json::nlohmann_json
)

add_test(NAME CreditCardTest COMMAND CreditCardTest)

# BankTest
add_executable(BankTest
    test/Domain/Credit/BankTest.cpp
    src/Domain/Credit/Bank.cpp
    src/Domain/Credit/CreditCard.cpp
)

target_link_libraries(BankTest
    gtest
    gmock
    gtest_main
    pthread
    nlohmann_json::nlohmann_json
)

add_test(NAME BankTest COMMAND BankTest)

add_executable(sonar_scanner_example src/main.cpp src/Domain/Socket/SocketManager.cpp)# 빌드할 실행파일 및 소스 목록
target_link_libraries(sonar_scanner_example PRIVATE nlohmann_json::nlohmann_json)
