cmake_minimum_required(VERSION 3.9)# 최소 cmake 버전 명시
project(sonar_scanner_example)# 프로젝트 이름 명시

set(CMAKE_CXX_STANDARD 17)# 사용할 C++ 표준(여기선 17)

# GTest 자동 설치
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# 테스트 실행파일 생성
add_executable(RequestPrePaymentControllerTest
    test/RequestPrePaymentControllerTest.cpp
    src/Services/Controller/RequestPrePaymentController.cpp
    src/Domain/Credit/CreditCard.cpp
    src/Domain/Credit/Bank.cpp
    src/Domain/Socket/SocketManager.cpp
    src/Domain/Auth/AuthCodeManager.cpp
    src/Domain/Beverage/Beverage.cpp
)

target_include_directories(RequestPrePaymentControllerTest PRIVATE 
    src
    src/Services/Controller
    src/Domain/Credit
    src/Domain/Socket
    src/Domain/Auth
    src/Domain/Beverage
    src/Domain/DTO
    src/Domain/Location
)
target_link_libraries(RequestPrePaymentControllerTest
    gtest
    gmock
    gtest_main
    pthread
)

add_executable(sonar_scanner_example src/main.cpp)# 빌드할 실행파일 및 소스 목록
