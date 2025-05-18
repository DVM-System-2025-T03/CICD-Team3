#include <gtest/gtest.h>
#include "Domain/Credit/Bank.h"
#include "Domain/Credit/CreditCard.h"
#include "Exception/CustomException.h"

#include <fstream>

class BankTest : public ::testing::Test {
protected:
    Bank bank;

    void SetUp() override {
        // 테스트 전용 카드 데이터 생성
        ofstream file("card_db.txt");
        file << "1234-5678-9012-3456 15000\n";
        file << "9876-5432-1098-7654 5000\n";
        file << "0000-0000-0000-0000 0\n";
        file.close();
    }

    void TearDown() override {
        // 테스트 후 카드 데이터 삭제
        remove("card_db.txt");
    }
};

TEST_F(BankTest, RequestCard_있는번호_조회성공) {
    CreditCard* card = bank.requestCard("1234-5678-9012-3456");
    ASSERT_NE(card, nullptr);
    EXPECT_EQ(card->getCardNumber(), "1234-5678-9012-3456");
    delete card;
}

TEST_F(BankTest, RequestCard_없는번호_조회실패) {
    EXPECT_THROW(bank.requestCard("1111-2222-3333-4444"), NotFoundException);
}