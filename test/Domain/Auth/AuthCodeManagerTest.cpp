#include "Domain/Auth/AuthCodeManager.h"
#include "exception/CustomException.h"
#include <gtest/gtest.h>
using namespace customException;
class AuthCodeManagerTest : public ::testing::Test {
protected:
    AuthCodeManager manager;

    void SetUp() override {
        // 테스트를 위한 인증 코드 등록
        manager.saveAuthCode(1,2,"ABC12");
        manager.saveAuthCode(2,5,"ABC34");
    }
};

TEST_F(AuthCodeManagerTest, ValidateAuthCode_등록된코드_True반환) {
    EXPECT_TRUE(manager.validateAuthCode("ABC12"));
    EXPECT_TRUE(manager.validateAuthCode("ABC34"));
}

TEST_F(AuthCodeManagerTest, ValidateAuthCode_없는코드_False반환) {
    EXPECT_THROW(manager.validateAuthCode("INVALID999"), NotFoundException);
    EXPECT_THROW(manager.validateAuthCode(""), NotFoundException);
}

TEST_F(AuthCodeManagerTest, GetBeverageId_등록된코드_Id반환) {
    EXPECT_EQ(manager.getBeverageId("ABC12"), 1);
    EXPECT_EQ(manager.getBeverageId("ABC34"), 2);
}

TEST_F(AuthCodeManagerTest, GetBeverageId_없는코드_Minus1반환) {
    EXPECT_THROW(manager.getBeverageId("INVALID999"), NotFoundException);
    EXPECT_THROW(manager.getBeverageId(""), NotFoundException);
}

TEST_F(AuthCodeManagerTest, GenerateAuthCode_길이가5) {
    string code = manager.generateAuthCode();
    EXPECT_EQ(code.length(), 5);
}

TEST_F(AuthCodeManagerTest, GenerateAuthCode_영어와_숫자만포함) {
    string code = manager.generateAuthCode();
    EXPECT_TRUE(all_of(code.begin(), code.end(), [](char c) {
        return isalnum(static_cast<unsigned char>(c));
    }));
}