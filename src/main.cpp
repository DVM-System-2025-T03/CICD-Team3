#include "Domain/Socket/SocketManager.h"
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    std::string id = "T1";
    int server_port = 9999;
    std::string target_ip = "127.0.0.1";
    int target_port = 9999;
    std::string dst_id = "T2";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--port") == 0 && i + 1 < argc)
            server_port = std::stoi(argv[++i]);
        else if (strcmp(argv[i], "--id") == 0 && i + 1 < argc)
            id = argv[++i];
        else if (strcmp(argv[i], "--target_ip") == 0 && i + 1 < argc)
            target_ip = argv[++i];
        else if (strcmp(argv[i], "--target_port") == 0 && i + 1 < argc)
            target_port = std::stoi(argv[++i]);
        else if (strcmp(argv[i], "--dst_id") == 0 && i + 1 < argc)
            dst_id = argv[++i];
    }

    SocketManager socketManager;

    // Start server always in background
    std::thread serverThread([&]() {
        socketManager.startServer(server_port, id);
    });

    // Client functionality can run anytime in main thread
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[메인] 다른 DVM에게 선결제 요청 시도" << std::endl;
    auto dto = socketManager.requestPrePay(1, 2, "ABC123", id, dst_id, target_ip, target_port);
    std::cout << "[메인] 응답 availability: " << (dto.availability ? "T" : "F") << std::endl;

    serverThread.join();
    return 0;
}