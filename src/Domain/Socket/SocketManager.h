#pragma once
#include <list>
#include <string>
#include "../DTO/ResponseStockDTO.h"
#include "../DTO/ResponsePrePaymentDTO.h"
#include "../../Services/Controller/ResponseStockController.h"
#include "../../Services/Controller/ResponsePrePaymentController.h"

using namespace std;

class SocketManager {
private:
    ResponseStockController responseStockController;
    ResponsePrePaymentController responsePrePaymentController;

public:
    list<ResponseStockDTO> requestBeverageStockToOthers(int beverageId, int quantity);
    ResponseStockDTO requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId);
    ResponsePrePaymentDTO requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId);
    bool requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId);
};