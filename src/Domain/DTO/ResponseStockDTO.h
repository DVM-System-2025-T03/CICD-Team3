#pragma once
#include <string>

class ResponseStockDTO {
public:
    int beverageId;
    int quantity;

    ResponseStockDTO() = default;
    ResponseStockDTO(int beverageId, int quantity) : beverageId(beverageId), quantity(quantity) {}

    int getBeverageId() const { return beverageId; }
    int getQuantity() const { return quantity; }
};