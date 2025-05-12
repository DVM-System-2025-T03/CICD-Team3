#include "SocketManager.h"

list<ResponseStockDTO> SocketManager::requestBeverageStockToOthers(int beverageId, int quantity, int srcId, int dstId) {
    return list<ResponseStockDTO>();
}

ResponseStockDTO SocketManager::requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId) {
    return ResponseStockDTO();
}

ResponsePrePaymentDTO SocketManager::requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId) {
    return ResponsePrePaymentDTO();
}

bool SocketManager::requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId) {
    return false;
}