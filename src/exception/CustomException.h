#pragma once

#include <stdexcept>
#include <string>

using namespace std;

namespace customException {

class CustomException : public std::runtime_error {
public:
    explicit CustomException(const std::string& message) 
        : std::runtime_error(message) {}
    
    virtual ~CustomException() = default;
};

class NotFoundException : public CustomException {
public:
    explicit NotFoundException(const string& message) 
        : CustomException("Not Found: " + message) {}
};

class InvalidException : public CustomException {
public:
    explicit InvalidException(const string& message) 
        : CustomException("Invalid: " + message) {}
};

class DuplicateException : public CustomException {
public:
    explicit DuplicateException(const string& message) 
        : CustomException("Duplicate: " + message) {}
};

class NotEnoughStockException : public CustomException {
public:
    explicit NotEnoughStockException(const string& message) 
        : CustomException("Not Enough Stock: " + message) {}
};

class NotEnoughBalanceException : public CustomException {
public:
    explicit NotEnoughBalanceException(const string& message) 
        : CustomException("Not Enough Balance: " + message) {}
};

}