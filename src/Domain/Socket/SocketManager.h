#pragma once
#include <vector>
#include <string>
#include <vector>
#include <map>
#include "../DTO/RequestStockDTO.h"
#include "../DTO/ResponseStockDTO.h"
#include "../DTO/RequestPrePaymentDTO.h"
#include "../DTO/ResponsePrePaymentDTO.h"
#include "../../Services/Controller/ResponseStockController.h"
#include "../../Services/Controller/ResponsePrePaymentController.h"

using namespace std;

class SocketManager {
private:
    ResponseStockController responseStockController;
    ResponsePrePaymentController responsePrePaymentController;
    map<int,pair<string,int>> otherDVMInfo;

    map<int,int> otherDVMSockets;
    int serverSocket;

    void connectOtherDVMSocket();
    void openServerSocket();
    void waitingRequest();


public:
    //새로 추가한 생성자 및 메서드
    SocketManager();

    //2040 정의 메서드
    list<ResponseStockDTO> requestBeverageStockToOthers(int beverageId, int quantity, int srcId, int dstId);
    ResponseStockDTO requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId);
    ResponsePrePaymentDTO requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId);
    bool requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId);
};