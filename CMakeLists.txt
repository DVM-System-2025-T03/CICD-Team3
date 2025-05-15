cmake_minimum_required(VERSION 3.9)# 최소 cmake 버전 명시
project(sonar_scanner_example)# 프로젝트 이름 명시

set(CMAKE_CXX_STANDARD 17)# 사용할 C++ 표준(여기선 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

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
)

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
)

add_executable(sonar_scanner_example src/main.cpp)# 빌드할 실행파일 및 소스 목록