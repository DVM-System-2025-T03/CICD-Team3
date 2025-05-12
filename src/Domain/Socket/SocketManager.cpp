#include <iostream>

class SocketManager{
    private ResponseStockController ResponseStockController;
    private ResponsePrePaymentController ResponsePrePaymentController;

    public List<ResponseStockDTO> requestBeverageStockToOthers(int beverageId, int quantity, int srcId, int dstId){
        return NULL;
    }

    public ResponseStockDTO requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId){
        return NULL;
    }

    public ResponsePrePaymentDTO requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId){
        return NULL;
    }

    public boolean requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId){
        return false;
    }
}