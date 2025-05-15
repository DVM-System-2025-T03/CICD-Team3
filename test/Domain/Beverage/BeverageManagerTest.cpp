#include "Domain/Beverage/BeverageManager.h"
#include <gtest/gtest.h>

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

TEST_F(BeverageManagerTest, GetBeverage_Found_ReturnsBeverage) {
    Beverage result = manager.getBeverage(1);
    EXPECT_EQ(result.getId(), 1);
}

TEST_F(BeverageManagerTest, GetBeverage_NotFound_CharInput_ReturnsDefaultBeverage) {
    Beverage result = manager.getBeverage('ab');
    EXPECT_EQ(result.getId(), 0);
}

TEST_F(BeverageManagerTest, GetBeverage_NotFound_NegativeInput_ReturnsDefaultBeverage) {
    Beverage result = manager.getBeverage(-1);
    EXPECT_EQ(result.getId(), 0);
}

TEST_F(BeverageManagerTest, GetBeverage_NotFound_ZeroInput_ReturnsDefaultBeverage) {
    Beverage result = manager.getBeverage(0);
    EXPECT_EQ(result.getId(), 0);
}

TEST_F(BeverageManagerTest, GetBeverage_NotFound_OverMaxInput_ReturnsDefaultBeverage) {
    Beverage result = manager.getBeverage(999);
    EXPECT_EQ(result.getId(), 0);
}