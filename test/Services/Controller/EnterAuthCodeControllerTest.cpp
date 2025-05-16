#include "Domain/Auth/AuthCodeManager.h"
#include "Domain/Beverage/BeverageManager.h"
#include "Services/Controller/EnterAuthCodeController.h"
#include "Domain/Beverage/Beverage.h"
#include "exception/CustomException.h"
#include <gtest/gtest.h>

using namespace customException;

class EnterAuthCodeControllerTest : public ::testing::Test {
protected:
    AuthCodeManager authCodeManager;
    BeverageManager beverageManager;
    EnterAuthCodeController* controller;

    void SetUp() override {
        beverageManager.addBeverage(Beverage(1, "콜라", 1000, 10));
        beverageManager.addBeverage(Beverage(2, "사이다", 1000, 10));

        authCodeManager.saveAuthCode(1,3,"ABC12");

        controller = new EnterAuthCodeController(&beverageManager, &authCodeManager);
    }

    void TearDown() override {
        delete controller;
    }
};

TEST_F(EnterAuthCodeControllerTest, EnterAuthCode_유효한코드_음료반환) {
    Beverage beverage = controller->enterAuthCode("ABC12");

    EXPECT_EQ(beverage.getId(), 1);
}

TEST_F(EnterAuthCodeControllerTest, EnterAuthCode_잘못된코드_예외발생) {
    EXPECT_THROW({
        controller->enterAuthCode("INVALID_CODE");
    }, NotFoundException);
}
