#pragma once

#include <exception>
#include "Domain/DTO/DVMInfoDTO.h"

class DVMInfoException : public std::exception {
private:
    DVMInfoDTO nearestDVM_;
public:
    explicit DVMInfoException(const DVMInfoDTO& info) noexcept
        : nearestDVM_(info) {}

    // 예외 처리기에서 DVMInfo를 꺼낼 수 있도록 getter 제공
    const DVMInfoDTO& getNearestDVM() const noexcept {
        return nearestDVM_;
    }

    // what()도 간단히 오버라이드
    const char* what() const noexcept override {
        return "Nearest DVM information available";
    }
};