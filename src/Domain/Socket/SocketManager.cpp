#include "SocketManager.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <list>
#include <arpa/inet.h>
#include <cstring>

//other DVM socket 미리 다 생성해놓기 (client socket)
void SocketManager::connectOtherDVMSocket(){
    for(auto dvmInfo : this->otherDVMInfo){
        int srdId = dvmInfo.first;
        string address = dvmInfo.second.first;
        int port = dvmInfo.second.second;

        //socket 기본 정보를 생성하는 것
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cout << "\nClient Socket 생성 실패\n";
            exit(EXIT_FAILURE);
        }

        //socket 설정정보를 위한 구조체
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
            cout << "\n올바르지 않는 client socket 주소와 포트번호\n";
            exit(EXIT_FAILURE);
        }

        //연결 시도
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cout << "\nClient Socket 연결실패\n";
            exit(EXIT_FAILURE);
        }

        this->otherDVMSockets.insert({srdId, sock});
    }
}

//우리 DVM socket 생성해놓기 (server socket)
void SocketManager::openServerSocket(){
    //socket 기본 정보를 생성하는 것
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        perror("\nServer Socket 생성 실패\n");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    // 소켓 옵션 (바인드 에러 방지용)
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    //socket 설정정보를 위한 구조체
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (::bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("\n바인딩 실패\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("\nlisten 실패\n");
        exit(EXIT_FAILURE);
    }

    this->serverSocket = server_socket;
}

void SocketManager::waitingRequest(){
    while(true){
        char buffer[2048] = {0};
        ssize_t valread = recv(this->serverSocket,  buffer, sizeof(buffer)-1, 0);
        if (valread > 0) {
            std::string json_str(buffer, valread);
            try {
                nlohmann::json j = nlohmann::json::parse(json_str);

                // 특정 JSON 값으로 처리 분기
                if (j.contains("msg_type") && j["msg_type"] == "req_stock") {
                    // 스레드로 처리
                    std::thread t(&SocketManager::requestBeverageInfo,this, j["msg_content"]["item_code"], j["msg_content"]["item_num"], j["src_id"], j["dst_id"]);
                    t.detach();
                }
                if (j.contains("msg_type") && j["msg_type"] == "req_prepay") {
                    // 스레드로 처리
                    std::thread t(&SocketManager::requestPrePay,this, j["msg_content"]["item_code"], j["msg_content"]["item_num"], j["msg_content"]["cert_code"], j["src_id"], j["dst_id"]);
                    t.detach();
                }
            } catch (std::exception& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        }
    }
}


SocketManager::SocketManager(){
    otherDVMInfo.insert({1, {"localhost", 8080}});
    //.... 미리 알고 있다고 가정했음.

    connectOtherDVMSocket();
    openServerSocket();
    thread t(&SocketManager::waitingRequest, this);
    t.detach();
}


// (해석) UC1에서 SelectBeverageController에 의해서 호출 당하는 것
// (변경) SelectBeverageController에 의해 호출 당하고 자체적으로 stream에 json 변환된거 흘려 보내는 것까지. 그리고 응답을 다 받아서 list로 줘야 함.
list<ResponseStockDTO> SocketManager::requestBeverageStockToOthers(int beverageId, int quantity, int srcId, int dstId) {

    list<ResponseStockDTO> result;

    for(auto dvmSocket : otherDVMSockets){
        RequestStockDTO requestStockDTO(beverageId, quantity, dvmSocket.first, 0); // PFR에 broadcast는 dstId 0으로 하랬음.
        json j = requestStockDTO;

        //보내기
        send(dvmSocket.second, j.dump().c_str(), j.size(), 0);

        //읽기
        char buf[2048] = {0};
        ssize_t bytes_received = recv(dvmSocket.second, buf, sizeof(buf) - 1, 0);
        std::string json_string(buf, bytes_received);

        //json으로 바꾸어서 DTO에 mapping
        nlohmann::json rj = nlohmann::json::parse(json_string);
        ResponseStockDTO responseStockDTO = rj;

        result.push_back(responseStockDTO);
    }

    return result;
}

// (해석) UC1에서 다른 DVM의 이 함수를 호출, 그리고 UC5에서 이 함수가 호출 당하며 시작
// (변경) SocketManager의 stream 관찰 함수의 분기처리에 의해 thread가 새로이 생성되어 호출되는 것. 응답으로 다시 stream에 json 흘려보내야 함.
ResponseStockDTO SocketManager::requestBeverageInfo(int beverageId, int quantity, int srcId, int dstId) {
    ResponseStockDTO responseStockDTO = this->responseStockController .responseBeverageStock(beverageId, quantity);
    responseStockDTO.setSrcAndDst(dstId, srcId);
    return responseStockDTO;
}

// (해석) UC3에서 RequestPrepaymentController에 의해서 호출 당하는 것
// (변경) RequestPrepaymentController에 의해 호출 당하고 자체적으로 stream에 json 변환된거 흘려 보내는 것까지. 그리고 응답을 받아서 boolean 반환.
bool SocketManager::requestPrePayment(int beverageId, int quantity, string authCode, int srcId, int dstId) {

    RequestPrePaymentDTO requestPrePaymentDTO(beverageId, quantity, authCode, srcId, dstId);
    json j = requestPrePaymentDTO;

    //보내기
    int dvmSocket = otherDVMSockets[srcId];
    send(dvmSocket, j.dump().c_str(), j.size(), 0);

    //읽기
    char buf[2048] = {0};
    ssize_t bytes_received = recv(dvmSocket, buf, sizeof(buf) - 1, 0);
    std::string json_string(buf, bytes_received);

    //json으로 바꾸어서 DTO에 mapping
    nlohmann::json rj = nlohmann::json::parse(json_string);
    ResponsePrePaymentDTO responsePrePaymentDTO = rj;

    return responsePrePaymentDTO.getAvailability();
}

// (해석) UC3에서 다른 DVM의 이 함수를 호출, 그리고 UC6에서 이 함수가 호출 당하며 시작
// (변경) SocketManager의 stream 관찰 함수의 분기처리에 의해 thread가 새로이 생성되어 호출되는 것. 응답으로 다시 stream에 json 흘려보내야 함.
ResponsePrePaymentDTO SocketManager::requestPrePay(int beverageId, int quantity, string authCode, int srcId, int dstId) {
    ResponsePrePaymentDTO responsePrePaymentDTO =  this->responsePrePaymentController.responsePrePay(beverageId, quantity, authCode);
    responsePrePaymentDTO.setSrcAndDst(srcId, dstId);
    return responsePrePaymentDTO;
}
