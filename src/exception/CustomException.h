#pragma once

#include <stdexcept>
#include <string>

using namespace std;

namespace exception {

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

class AuthenticationException : public CustomException {
public:
    explicit AuthenticationException(const string& message) 
        : CustomException("Authentication Error: " + message) {}
};

}