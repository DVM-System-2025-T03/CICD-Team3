#include <iostream>
#include "Services/Controller/RequestPrePaymentController.h"
#include "Services/Controller/EnterAuthCodeController.h"
using namespace std;

int main(int argc, char* argv[]) {
  int num = argc - 1;
  EnterAuthCodeController* enterAuthCodeController = new EnterAuthCodeController();
  RequestPrePaymentController* requestPrePaymentController = new RequestPrePaymentController();

  enterAuthCodeController->enterAuthCode("authCode");

  requestPrePaymentController->enterPrePayIntention("yes", Beverage(), 1, 1, 2);

  return 0;
}
