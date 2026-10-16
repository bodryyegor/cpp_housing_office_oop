#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "view/ConsoleView.h"
#include "model/repository/House.h"
#include "model/service/HousingService.h"

class Controller {
private:
    House house_;
    HousingService service_;
    ConsoleView view_;

    void handleCreateHouse();
    void handleAddApartment();
    void handleSettleApartment();
    void handleCalculatePayment();
    void handleDiscountsSingle();
    void handleDiscountsMulti();
    void handleShowApartments();
    void handleBenchmark();

public:
    void run();
};

#endif
