#include "Services/Controller/EnterAuthCodeController.h"
#include "Services/Controller/RequestPrePaymentController.h"
#include "Services/Controller/ResponsePrePaymentController.h"
#include "Services/Controller/ResponseStockController.h"
#include "Services/Controller/SelectBeverageController.h"
#include "Services/Controller/RequestPaymentController.h"

#include "Domain/Socket/SocketManager.h"
#include "Domain/Auth/AuthCodeManager.h"
#include "Domain/Beverage/BeverageManager.h"
#include "Domain/Credit/Bank.h"
#include "Domain/Credit/CreditCard.h"
#include "Domain/Location/LocationManager.h"
#include "Domain/Beverage/Beverage.h"
#include "Exception/CustomException.h"
#include "Exception/DVMInfoException.h"
#include <iostream>

int main(int argc, char* argv[]) {

    SocketManager* socketManager = new SocketManager();
    AuthCodeManager* authCodeManager = new AuthCodeManager();
    Bank* bank = new Bank();
    BeverageManager* beverageManager = new BeverageManager();
    LocationManager* locationManager = new LocationManager();
    
    SelectBeverageController* selectBeverageController = new SelectBeverageController();
    RequestPrePaymentController* requestPrePaymentController = new RequestPrePaymentController(authCodeManager, bank, socketManager);
    EnterAuthCodeController* enterAuthCodeController = new EnterAuthCodeController(beverageManager, authCodeManager);
    ResponsePrePaymentController* responsePrePaymentController = new ResponsePrePaymentController(beverageManager, authCodeManager);
    RequestPaymentController* requestPaymentController = new RequestPaymentController(beverageManager, bank, new CreditCard("", 0), 0, 0, 0);
    ResponseStockController* responseStockController = new ResponseStockController(beverageManager, locationManager);

    int beverageId = -1;
    int quantity = -1;
    bool status = false;
    int menu = -1;
    while (true) {
      cout << "메뉴를 선택하세요 (1: 음료 선택, 2: 선결제 코드 입력, 0: 종료): ";
      cin >> menu;
      if (menu == 0) {
          cout << "프로그램을 종료합니다." << endl;
          break;
      } else if (menu == 2) {
          // 인증 코드 입력
        cout << "인증 코드를 입력하세요: ";
        string authCode;
        cin >> authCode;
        try{
        Beverage beverage = enterAuthCodeController->enterAuthCode(authCode);
        cout << "인증 코드 확인 성공: " << beverage.getId() << endl; 
        } catch (const customException::InvalidException& e) {
            std::cout << "인증 코드가 유효하지 않습니다. 다시 입력하세요." << std::endl;
            continue;
        }
      } else if (menu != 1) {
          cout << "잘못된 메뉴입니다. 다시 선택하세요." << endl;
          continue;
      }
      try {
        cout << "음료 아이디를 입력하세요 (1~20): ";
        cin >> beverageId;
        cout << "수량을 입력하세요 (1~10): ";
        cin >> quantity;
        /*status = */selectBeverageController->selectBeverage(beverageId, quantity);
      } catch (const customException::InvalidException& e) {
          std::cout << "음료 아이디가 유효하지 않습니다. 다시 입력하세요." << std::endl;
          continue;
      }

      
      if (status) {
          cout << "음료 결제" << endl;
          string cardNumber;
          cout << "카드 번호를 입력하세요: ";
          cin >> cardNumber;
          try{
              Beverage beverage = requestPaymentController->enterCardNumber(cardNumber);
              cout << "결제 성공: " << beverage.getId() << endl;
          } catch (const RequestPaymentController::CardNotFoundException& e) {
              cout << e.what() << endl;
          }
      } else {
          cout << "음료 선결제" << endl;
          cout << "선결제 의사를 입력하세요 (1: 선결제, 0: 일반 결제): ";
          int intention;
          cin >> intention;
          bool intentionBool = (intention == 1);
          string cardNumber;
          if(intentionBool) {
            cout << "카드 번호를 입력하세요: ";
          cin >> cardNumber;
          }else{
            continue;
          }
          
          try {
            Beverage beverage = beverageManager->getBeverage(beverageId);
            requestPrePaymentController->enterPrePayIntention(intentionBool);
            string authCode = requestPrePaymentController->enterCardNumber(cardNumber, beverage, quantity, 0, 0);
            cout << "결제 성공: " << beverage.getId() << endl;
          } catch (const customException::InvalidException& e) {
              continue;
          }
      } 
    }
    delete socketManager;
    delete authCodeManager;
    delete bank;
    delete beverageManager;
    delete locationManager;
    delete selectBeverageController;
    delete requestPrePaymentController;
    delete enterAuthCodeController;
    delete responsePrePaymentController;
    delete requestPaymentController;
    delete responseStockController;


  return 0;
}