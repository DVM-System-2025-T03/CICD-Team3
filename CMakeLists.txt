cmake_minimum_required(VERSION 3.10)
project(sonar_scanner_example)

set(CMAKE_CXX_STANDARD 17)

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

# 💡 전역 include (src 전체 사용 가능)
include_directories(${CMAKE_SOURCE_DIR}/src)

enable_testing()

# ==============================
# ✅ 실행파일 (main.cpp + SocketManager.cpp)
# ==============================
add_executable(sonar_scanner_example
    src/main.cpp
    src/Domain/Socket/SocketManager.cpp
)
target_link_libraries(sonar_scanner_example PRIVATE nlohmann_json::nlohmann_json)

# ==============================
# ✅ AuthCodeManagerTest
# ==============================
add_executable(AuthCodeManagerTest
    test/Domain/Auth/AuthCodeManagerTest.cpp
    src/Domain/Auth/AuthCodeManager.cpp
)
target_link_libraries(AuthCodeManagerTest
    gtest gmock gtest_main pthread nlohmann_json::nlohmann_json
)
add_test(NAME AuthCodeManagerTest COMMAND AuthCodeManagerTest)

# ==============================
# ✅ BeverageManagerTest
# ==============================
add_executable(BeverageManagerTest
    test/Domain/Beverage/BeverageManagerTest.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
)
target_link_libraries(BeverageManagerTest
    gtest gmock gtest_main pthread nlohmann_json::nlohmann_json
)
add_test(NAME BeverageManagerTest COMMAND BeverageManagerTest)

# ==============================
# ✅ CreditCardTest
# ==============================
add_executable(CreditCardTest
    test/Domain/Credit/CreditCardTest.cpp
    src/Domain/Credit/CreditCard.cpp
)
target_link_libraries(CreditCardTest
    gtest gmock gtest_main pthread nlohmann_json::nlohmann_json
)
add_test(NAME CreditCardTest COMMAND CreditCardTest)

# ==============================
# ✅ BankTest
# ==============================
add_executable(BankTest
    test/Domain/Credit/BankTest.cpp
    src/Domain/Credit/Bank.cpp
    src/Domain/Credit/CreditCard.cpp
)
target_link_libraries(BankTest
    gtest gmock gtest_main pthread nlohmann_json::nlohmann_json
)
add_test(NAME BankTest COMMAND BankTest)

# ==============================
# ✅ EnterAuthCodeControllerTest (통합테스트)
# ==============================
add_executable(EnterAuthCodeControllerTest
    test/Services/Controller/EnterAuthCodeControllerTest.cpp
    src/Domain/Auth/AuthCodeManager.cpp
    src/Domain/Beverage/BeverageManager.cpp
    src/Domain/Beverage/Beverage.cpp
    src/Services/Controller/EnterAuthCodeController.cpp
)
target_link_libraries(EnterAuthCodeControllerTest
    gtest gmock gtest_main pthread nlohmann_json::nlohmann_json
)
add_test(NAME EnterAuthCodeControllerTest COMMAND EnterAuthCodeControllerTest)