#include "gtest/gtest.h"
#include "Services/Controller/RequestPrePaymentController.h"
#include "Domain/Beverage/Beverage.h"
#include "Domain/Socket/SocketManager.h"
#include "Domain/Credit/Bank.h"
#include "Domain/Auth/AuthCodeManager.h"
#include "Domain/Beverage/BeverageManager.h"
#include <queue>
#include <stdexcept>
#include <string>

using namespace std;

// ----------------- Mock SocketManager ------------------
class MockSocketManager : public SocketManager {
public:
    MockSocketManager() : SocketManager(0, 0) {}
};

// ------------- Testable Controller with Mocked Input -------------
class TestableRequestPrePaymentController : public RequestPrePaymentController {
private:
    queue<string> mockInputs;

public:
    TestableRequestPrePaymentController(AuthCodeManager* auth, Bank* bank,
        SocketManager* socket, BeverageManager* bev)
        : RequestPrePaymentController(auth, bank, socket, bev) {}

    void setMockInputs(const vector<string>& inputs) {
        mockInputs = queue<string>(deque<string>(inputs.begin(), inputs.end()));
    }

protected:
    string inputCardNumber() override {
        if (mockInputs.empty()) throw runtime_error("No more mock inputs");
        string result = mockInputs.front();
        mockInputs.pop();
        return result;
    }
};

// ----------------------------- Test Suite -----------------------------
class RequestPrePaymentControllerTest : public ::testing::Test {
protected:
    AuthCodeManager authCodeManager;
    Bank bank;
    MockSocketManager socketManager;
    BeverageManager beverageManager;
};

TEST_F(RequestPrePaymentControllerTest, InvalidCardNumbersShouldFail) {
    Beverage beverage(15, "오렌지주스", 0, 2200);
    TestableRequestPrePaymentController controller(&authCodeManager, &bank, &socketManager, &beverageManager);
    controller.setMockInputs({"invalid-card-1", "invalid-card-2"});

    EXPECT_THROW(controller.enterCardNumber("", beverage, 10, 1), runtime_error);
}

TEST_F(RequestPrePaymentControllerTest, InsufficientBalanceShouldThrow) {
    Beverage beverage(15, "오렌지주스", 0, 2200);

    TestableRequestPrePaymentController controller(&authCodeManager, &bank, &socketManager, &beverageManager);
    controller.setMockInputs({"1111-2222-3333-4444"});

    EXPECT_THROW(controller.enterCardNumber("", beverage, 10, 1), customException::NotEnoughBalanceException);
}

TEST_F(RequestPrePaymentControllerTest, SuccessfulPrePaymentShouldReturnAuthCode) {
    Beverage beverage(15, "오렌지주스", 0, 220);

    TestableRequestPrePaymentController controller(&authCodeManager, &bank, &socketManager, &beverageManager);
    controller.setMockInputs({"1111-2222-3333-4444"});

    string authCode = controller.enterCardNumber("", beverage, 1, 1);
    EXPECT_FALSE(authCode.empty());
}
