// #include "Services/Controller/RequestPrePaymentController.h"
// #include <gtest/gtest.h>
// #include <gmock/gmock.h>

// using namespace std;
// using ::testing::Return;
// using ::testing::_;
// using ::testing::NiceMock;

// class MockAuthCodeManager : public AuthCodeManager{
// public:
//     MOCK_METHOD(string, generateAuthCode, (), ());
// };

// class MockBank : public Bank{
// public:
//     MOCK_METHOD(CreditCard*, requestCard, (const string&), ());
// };

// class MockSocketManager : public SocketManager{
// public:
//     MOCK_METHOD(bool, requestPrePayment, (int, int, const string&, int, int), ());
// };

// class MockCreditCard : public CreditCard {
// public:
//     MOCK_METHOD(bool, isValid, (), (const));
//     MOCK_METHOD(bool, validateBalance, (int), (const));
// };

// class MockBeverage : public Beverage {
// public:
//     MOCK_METHOD(int, getId, (), (const));
//     MOCK_METHOD(int, getPrice, (), (const));
// };

// // 선결제 요청 성공
// TEST(RequestPrePaymentControllerTest, PrePayment_Success) {
//     NiceMock<MockAuthCodeManager> mockAuthCodeManager;
//     NiceMock<MockBank> mockBank;
//     NiceMock<MockSocketManager> mockSocketManager;
//     NiceMock<MockCreditCard> mockCard;
//     NiceMock<MockBeverage> mockBeverage;

//     EXPECT_CALL(mockBank, requestCard(_))
//         .WillOnce(Return(&mockCard));

//     EXPECT_CALL(mockCard, isValid())
//         .WillOnce(Return(true));

//     EXPECT_CALL(mockCard, validateBalance(100))
//         .WillOnce(Return(true));

//     EXPECT_CALL(mockAuthCodeManager, generateAuthCode())
//         .WillOnce(Return("AUTH123"));

//     EXPECT_CALL(mockSocketManager, requestPrePayment(_, _, _, _, _))
//         .WillOnce(Return(true));

//     EXPECT_CALL(mockBeverage, getPrice())
//         .WillRepeatedly(Return(100));

//     EXPECT_CALL(mockBeverage, getId())
//         .WillRepeatedly(Return(1));

//     ON_CALL(mockBank, requestCard(_)).WillByDefault([](const std::string& num) {
//     std::cout << "[MOCK CALL] requestCard called with: " << num << std::endl;
//     return nullptr;
// });

//     std::istringstream input("1234\n");
//     std::streambuf* origCin = std::cin.rdbuf();
//     std::cin.rdbuf(input.rdbuf());

//     RequestPrePaymentController controller(&mockAuthCodeManager, &mockBank, &mockSocketManager);
//     bool result = controller.enterPrePayIntention(true, mockBeverage, 1, 0, 0);

//     std::cin.rdbuf(origCin);

//     ASSERT_TRUE(result);
// }

// // 선결제 요청 실패
// TEST(RequestPrePaymentControllerTest, PrePayment_CardInvalidThreeTimes_Fail) {
//     NiceMock<MockAuthCodeManager> mockAuthCodeManager;
//     NiceMock<MockBank> mockBank;
//     NiceMock<MockSocketManager> mockSocketManager;
//     NiceMock<MockBeverage> mockBeverage;

//     EXPECT_CALL(mockBank, requestCard(_))
//         .Times(3)
//         .WillRepeatedly(Return(nullptr));

//     std::istringstream input("1111\n2222\n3333\n");
//     std::streambuf* origCin = std::cin.rdbuf();
//     std::cin.rdbuf(input.rdbuf());

//     RequestPrePaymentController controller(&mockAuthCodeManager, &mockBank, &mockSocketManager);
//     bool result = controller.enterPrePayIntention(true, mockBeverage, 1, 0, 0);

//     std::cin.rdbuf(origCin);

//     ASSERT_FALSE(result);
// }