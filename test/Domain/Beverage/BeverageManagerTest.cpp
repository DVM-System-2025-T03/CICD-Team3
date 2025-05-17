#include "Domain/Beverage/BeverageManager.h"
#include "Exception/CustomException.h"
#include <gtest/gtest.h>
using namespace customException;
class BeverageManagerTest : public ::testing::Test {
protected:
    BeverageManager manager;
    Beverage beverage1;
    Beverage beverage2;

    void SetUp() override {
        beverage1 = Beverage(1, "콜라", 5, 1000);
        beverage2 = Beverage(2, "사이다", 10, 500);
        manager.addBeverage(beverage1);
        manager.addBeverage(beverage2);
    }
};

TEST_F(BeverageManagerTest, GetBeverage_성공_Beverage반환) {
    Beverage result = manager.getBeverage(1);
    EXPECT_EQ(result.getId(), 1);
}

TEST_F(BeverageManagerTest, GetBeverage_실패_문자입력_예외) {
    EXPECT_THROW(manager.getBeverage('a'), NotFoundException);
}

TEST_F(BeverageManagerTest, GetBeverage_실패_음수입력_예외) {
    EXPECT_THROW(manager.getBeverage(-1), NotFoundException);
}

TEST_F(BeverageManagerTest, GetBeverage_실패_0입력_예외) {
    EXPECT_THROW(manager.getBeverage(0), NotFoundException);
}

TEST_F(BeverageManagerTest, GetBeverage_실패_초과입력_예외) {
    EXPECT_THROW(manager.getBeverage(999), NotFoundException);
}