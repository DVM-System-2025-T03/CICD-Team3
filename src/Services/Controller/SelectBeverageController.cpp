#include "SelectBeverageController.h"

void SelectBeverageController::selectBeverage(int beverageId, int quantity) {
    // 1. 입력 검증
    if (beverageId <= 0 || beverageId > 20) {
        throw std::invalid_argument("beverageId는 1 이상 20 이하의 값이어야 합니다.");
    }
    if (quantity <= 0) {
        throw std::invalid_argument("quantity는 1 이상이어야 합니다.");
    }

    // 2. 로컬 재고 확인
    if (beverageManager.hasEnoughStock(beverageId, quantity)) {
        // 3. 재고가 충분하면 아무 것도 하지 않고 종료
        return;
    }

    // 4. 재고 부족 → 다른 DVM에 재고 요청
    auto responseList = socketManager.requestBeverageStockToOthers(beverageId, quantity);

    // 5. 가장 가까운 DVM 계산
    DVMInfoDTO nearestDVM = locationManager.calculateNearest(responseList);

    // 6. 계산된 DVM 정보를 예외로 던져서 호출 쪽에서 처리하도록 함
    throw DVMInfoException(nearestDVM);
}
