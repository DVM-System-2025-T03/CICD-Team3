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
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {

    SocketManager* socketManager = new SocketManager(atoi(argv[1]), atoi(argv[2]));
    AuthCodeManager* authCodeManager = new AuthCodeManager();
    Bank* bank = new Bank();
    BeverageManager* beverageManager = new BeverageManager();
    LocationManager* locationManager = new LocationManager(0, 0);   // 현재 DVM 위치 (0, 0) -> 임시로 설정
    
    SelectBeverageController* selectBeverageController = new SelectBeverageController(locationManager, beverageManager, socketManager);
    RequestPrePaymentController* requestPrePaymentController = new RequestPrePaymentController(authCodeManager, bank, socketManager, beverageManager);
    EnterAuthCodeController* enterAuthCodeController = new EnterAuthCodeController(beverageManager, authCodeManager);
    ResponsePrePaymentController* responsePrePaymentController = new ResponsePrePaymentController(beverageManager, authCodeManager);
    RequestPaymentController* requestPaymentController = new RequestPaymentController(beverageManager, bank);
    ResponseStockController* responseStockController = new ResponseStockController(locationManager, beverageManager);

    socketManager->setController(responseStockController, responsePrePaymentController);

    authCodeManager->saveAuthCode(1, 2, "AB123");
    map<int, pair<string, int>> beverageMap;
    beverageMap[1] = make_pair("콜라", 1200);
    beverageMap[2] = make_pair("사이다", 1100);
    beverageMap[3] = make_pair("녹차", 1600);
    beverageMap[4] = make_pair("홍차", 1300);
    beverageMap[5] = make_pair("밀크티", 1400);
    beverageMap[6] = make_pair("탄산수", 2000);
    beverageMap[7] = make_pair("보리차", 2500);
    beverageMap[8] = make_pair("캔커피", 2600);
    beverageMap[9] = make_pair("물", 1500);
    beverageMap[10] = make_pair("에너지드링크", 1700);
    beverageMap[11] = make_pair("유자차", 1800);
    beverageMap[12] = make_pair("식혜", 1900);
    beverageMap[13] = make_pair("아이스티", 2000);
    beverageMap[14] = make_pair("딸기주스", 2100);
    beverageMap[15] = make_pair("오렌지주스", 2200);
    beverageMap[16] = make_pair("포도주스", 2300);
    beverageMap[17] = make_pair("이온음료", 2400);
    beverageMap[18] = make_pair("아메리카노", 2500);
    beverageMap[19] = make_pair("핫초코", 2600);
    beverageMap[20] = make_pair("카페라떼", 2700);
    vector<int> beverageIds;
    for(int i = 0; i < 20; i++){
      // 랜덤하게 인풋을 추가
      beverageIds.push_back(i);
    }
    for (const auto& pair : beverageMap) {
        int id = pair.first;
        string name = pair.second.first;
        int price = pair.second.second;
        // 보유중인 음료
        if(find(beverageIds.begin(), beverageIds.end(), id) != beverageIds.end()){
          beverageManager->addBeverage(Beverage(id, name, 10, price));
          cout << "음료 추가: " << id << ", " << name << ", " << price << endl;
        }
        // 보유중이지 않은 음료
        else{
          beverageManager->addBeverage(Beverage(id, name, 0, price));
        }
        // cout << "음료 추가: " << id << ", " << name << ", " << price << endl;
    }

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
        try {
          Beverage beverage = enterAuthCodeController->enterAuthCode(authCode);
          cout << "인증 코드 확인 성공! 음료를 받으세요 : " << beverage.getId() << endl; 
          continue;
        } catch (const customException::InvalidException& e) {
            // 인증 코드 3회 실패한 경우
            std::cout << e.what() << std::endl;
            continue;
        }
      } else if (menu != 1) {
          cout << "잘못된 메뉴입니다. 다시 선택하세요." << endl;
          continue;
      }

      // uc1
      try {
        cout << "음료 아이디를 입력하세요 (1~20): ";
        cin >> beverageId;
        cout << "수량을 입력하세요 (1~10): ";
        cin >> quantity;
        selectBeverageController->selectBeverage(beverageId, quantity);
      } catch (const customException::InvalidException& e) {
          std::cout << e.what() << " 다시 입력하세요." << std::endl;
          continue;
      } catch (const customException::DVMInfoException& e) {
          // uc3
          DVMInfoDTO nearestDVM = e.getNearestDVM();
          
          cout << "음료 선결제" << endl;
          cout << "가장 가까운 DVM 정보: DvmId = " << nearestDVM.getPrePaymentDvmId() << ", 위치 = (" << nearestDVM.getX() << ", " << nearestDVM.getY() << ")" << endl;
          cout << "선결제 의사를 입력하세요 (1: 선결제, 0: 일반 결제): ";
          int intention;
          cin >> intention;
          bool intentionBool = (intention == 1);
          string cardNumber;

          try {
            requestPrePaymentController->enterPrePayIntention(intentionBool);
            Beverage beverage = beverageManager->getBeverage(beverageId);

            string authCode = requestPrePaymentController->enterCardNumber(cardNumber, beverage, quantity, 1);
            cout << "선결제 성공: " << authCode << endl;
          } catch (const customException::InvalidException& e) {
              // 선결제 의사 없는 경우 or 카드번호 3회 실패한 경우
              continue;
          } catch (const customException::NotEnoughBalanceException& e) {
              // 카드 잔액 부족한 경우
              cout << e.what() << " 다시 입력하세요." << endl;
              continue;
          } catch (const customException::FailedToPrePaymentException& e) {
              // 선결제 실패한 경우
              cout << e.what() << " 다시 입력하세요." << endl;
              continue;
          } catch (const customException::FileOpenException& e) {
            // 카드 DB 파일 열기 실패한 경우
            cerr << e.what() << endl;
            exit(EXIT_FAILURE);
        }
      }

      // uc2
      cout << "음료 결제" << endl;
      string cardNumber;
      cout << "카드 번호를 입력하세요: ";
      cin >> cardNumber;
      try{
          Beverage beverage = requestPaymentController->enterCardNumber(cardNumber, beverageId, quantity);
          cout << "결제 성공: " << beverage.getId() << endl;
      } catch (const RequestPaymentController::CardNotFoundException& e) {
          cout << e.what() << endl;
      } catch (const RequestPaymentController::InsufficientBalanceException& e) {
        cout << e.what() << endl;
      } catch (const RequestPaymentController::BeverageReductionException& e) {
        cout << e.what() << endl;
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