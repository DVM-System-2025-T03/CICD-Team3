#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <list>
#include <string>
#include <vector>

#include "Services/Controller/ResponseStockController.h"
#include "Services/Controller/ResponsePrePaymentController.h"
#include "Domain/DTO/ResponseStockDTO.h"
#include "Domain/DTO/ResponsePrePaymentDTO.h"
#include "Domain/DTO/RequestStockDTO.h"
#include "Domain/DTO/RequestPrePaymentDTO.h"

#define PORT 8888
#define BROADCAST_IP "255.255.255.255"

using namespace std;
using json = nlohmann::json;

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
    SocketManager() noexcept;

    list<ResponseStockDTO> requestBeverageStockToOthers(int beverageId, int quantity, int srcId, int dstId);
    
    ResponseStockDTO requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId);
    ResponsePrePaymentDTO requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId);
    bool requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId);
};