#include "Bank.h"
#include "CreditCard.h"

CreditCard* Bank::requestCard(string cardNumber) {
    std::ifstream file("card_db.txt");
    if (!file.is_open()) {
        cerr << "[Bank] 카드 데이터 파일 열기 실패" << endl;
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedCardNumber;
        int balance;

        if (!(iss >> storedCardNumber >> balance)) {
            continue;
        }

        if (storedCardNumber == cardNumber) {
            cout << "[Bank] 카드 조회 성공: " << storedCardNumber << " (잔액: " << balance << ")" << std::endl;
            return new CreditCard(storedCardNumber, balance);
        }
    }

    cout << "[Bank] 해당 카드 번호 없음: " << cardNumber << std::endl;

    return nullptr;
}

void Bank::saveCreditCard(CreditCard creditCard) {
    // 추가 구현
    
}
