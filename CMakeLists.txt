cmake_minimum_required(VERSION 3.10)
project(sonar_scanner_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/test
)

# ==============================
# ✅ Main Application
# ==============================
add_executable(sonar_scanner_example
    src/main.cpp
    src/Domain/Socket/SocketManager.cpp
    src/Domain/Auth/AuthCodeManager.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
    src/Domain/Credit/Bank.cpp
    src/Domain/Credit/CreditCard.cpp
    src/Domain/Location/LocationManager.cpp
    src/Services/Controller/ResponseStockController.cpp
    src/Services/Controller/ResponsePrePaymentController.cpp
    src/Services/Controller/RequestPrePaymentController.cpp
    src/Services/Controller/EnterAuthCodeController.cpp
    src/Services/Controller/SelectBeverageController.cpp
    src/Services/Controller/RequestPaymentController.cpp
)
target_link_libraries(sonar_scanner_example PRIVATE nlohmann_json::nlohmann_json pthread)

# ==============================
# ✅ Tests Section
# ==============================
enable_testing()

add_executable(AuthCodeManagerTest
    test/Domain/Auth/AuthCodeManagerTest.cpp
    src/Domain/Auth/AuthCodeManager.cpp
)
target_link_libraries(AuthCodeManagerTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME AuthCodeManagerTest COMMAND AuthCodeManagerTest)

add_executable(BeverageTest
    test/Domain/Beverage/BeverageTest.cpp
    src/Domain/Beverage/Beverage.cpp
)
target_link_libraries(BeverageTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME BeverageTest COMMAND BeverageTest)

add_executable(BeverageManagerTest
    test/Domain/Beverage/BeverageManagerTest.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
)
target_link_libraries(BeverageManagerTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME BeverageManagerTest COMMAND BeverageManagerTest)

add_executable(CreditCardTest
    test/Domain/Credit/CreditCardTest.cpp
    src/Domain/Credit/CreditCard.cpp
)
target_link_libraries(CreditCardTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME CreditCardTest COMMAND CreditCardTest)

add_executable(BankTest
    test/Domain/Credit/BankTest.cpp
    src/Domain/Credit/Bank.cpp
    src/Domain/Credit/CreditCard.cpp
)
target_link_libraries(BankTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME BankTest COMMAND BankTest)

add_executable(LocationTest
    test/Domain/Location/LocationTest.cpp
)
target_link_libraries(LocationTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME LocationTest COMMAND LocationTest)

add_executable(LocationManagerTest
    test/Domain/Location/LocationManagerTest.cpp
    src/Domain/Location/LocationManager.cpp
)
target_link_libraries(LocationManagerTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME LocationManagerTest COMMAND LocationManagerTest)

add_executable(EnterAuthCodeControllerTest
    test/Services/Controller/EnterAuthCodeControllerTest.cpp
    src/Domain/Auth/AuthCodeManager.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
    src/Services/Controller/EnterAuthCodeController.cpp
)
target_link_libraries(EnterAuthCodeControllerTest gtest gmock gtest_main pthread nlohmann_json::nlohmann_json)
add_test(NAME EnterAuthCodeControllerTest COMMAND EnterAuthCodeControllerTest)