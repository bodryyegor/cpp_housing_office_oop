#include "controller/Controller.h"
#include "model/entity/RegularTenant.h"
#include "model/entity/DiscountTenant.h"
#include <chrono>
#include <fstream>
#include <random>
#include <filesystem>

void Controller::run() {
    bool running = true;
    while (running) {
        view_.showMenu();
        int choice = view_.readMenuChoice();
        try {
            switch (choice) {
                case 1: handleCreateHouse(); break;
                case 2: handleAddApartment(); break;
                case 3: handleSettleApartment(); break;
                case 4: handleCalculatePayment(); break;
                case 5: handleDiscountsSingle(); break;
                case 6: handleDiscountsMulti(); break;
                case 7: handleShowApartments(); break;
                case 8: handleBenchmark(); break;
                case 0: running = false; break;
                default: view_.printError("Неверный выбор.");
            }
        } catch (const std::exception& ex) {
            view_.printError(ex.what());
        }
    }
}

void Controller::handleCreateHouse() {
    std::string street = view_.readString("Улица: ");
    std::string number = view_.readString("Номер дома: ");
    double paySq = view_.readDouble("Плата за кв.м: ", 0.01);
    double payPerson = view_.readDouble("Плата за жильца: ", 0.01);
    house_ = House(street, number, paySq, payPerson);
    view_.printMessage("Дом создан.");
}

void Controller::handleAddApartment() {
    int num = view_.readInt("Номер квартиры: ", 1, 99999);
    double area = view_.readDouble("Площадь (м²): ", 1.0);
    house_.addApartment(Apartment(num, area, {}));
    view_.printMessage("Квартира добавлена.");
}

void Controller::handleSettleApartment() {
    int num = view_.readInt("Номер квартиры: ", 1, 99999);
    int count = view_.readInt("Количество жильцов: ", 1, 20);
    std::vector<std::shared_ptr<ITenant>> tenants;
    for (int i = 0; i < count; ++i) {
        view_.printMessage("Жилец #" + std::to_string(i+1));
        std::string type = view_.readString("Тип (обычный/льготный): ");
        std::string name = view_.readString("ФИО: ");
        int year = view_.readInt("Год рождения: ", 1900, 2025);
        char gender = view_.readString("Пол (M/F): ")[0];
        std::string status = view_.readString("Статус: ");

        if (type == "льготный") {
            std::string discountType = view_.readString("Тип льготы: ");
            double discount = view_.readDouble("Размер льготы (0.0–100.0): ", 0.0);
            if (discount > 100.0) discount = 100.0;
            tenants.push_back(std::make_shared<DiscountTenant>(
                name, year, gender, status, discountType, discount / 100.0
            ));
        } else {
            tenants.push_back(std::make_shared<RegularTenant>(
                name, year, gender, status
            ));
        }
    }
    service_.settleApartment(house_, num, tenants);
    view_.printMessage("Квартира заселена.");
}

void Controller::handleCalculatePayment() {
    int num = view_.readInt("Номер квартиры: ", 1, 99999);
    double payment = service_.calculatePaymentForApartment(house_, num);
    view_.printMessage("Платёж: " + std::to_string(payment));
}

void Controller::handleDiscountsSingle() {
    double total = service_.calculateTotalDiscountsSingleThread(house_);
    view_.printMessage("Льготы (однопоточно): " + std::to_string(total));
}

void Controller::handleDiscountsMulti() {
    double total = service_.calculateTotalDiscountsMultiThread(house_);
    view_.printMessage("Льготы (многопоточно): " + std::to_string(total));
}

void Controller::handleShowApartments() {
    house_.outputAllApartments();
}

void Controller::handleBenchmark() {
    int n = view_.readInt("Количество квартир для генерации: ", 100, 100000000);

    House benchHouse("Benchmark", "0", 100.0, 50.0);
    HousingService benchService;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> areaDist(30.0, 100.0);
    std::uniform_int_distribution<int> tenantCountDist(1, 5);
    std::uniform_int_distribution<int> yearDist(1950, 2000);
    std::uniform_real_distribution<double> discountDist(10.0, 50.0);

    for (int i = 0; i < n; ++i) {
        int num = i + 1;
        double area = areaDist(rng);
        int tenantCount = tenantCountDist(rng);
        std::vector<std::shared_ptr<ITenant>> tenants;
        for (int j = 0; j < tenantCount; ++j) {
            std::string name = "Жилец_" + std::to_string(num) + "_" + std::to_string(j);
            int year = yearDist(rng);
            char gender = (j % 2 == 0) ? 'M' : 'F';
            std::string status = "статус";

            if (j == 0 && (num % 3 == 0)) {
                double discount = discountDist(rng);
                tenants.push_back(std::make_shared<DiscountTenant>(
                    name, year, gender, status, "льгота", discount / 100.0
                ));
            } else {
                tenants.push_back(std::make_shared<RegularTenant>(
                    name, year, gender, status
                ));
            }
        }
        benchHouse.addApartment(Apartment(num, area, tenants));
    }

    auto startSingle = std::chrono::steady_clock::now();
    double single = benchService.calculateTotalDiscountsSingleThread(benchHouse);
    auto endSingle = std::chrono::steady_clock::now();

    auto startMulti = std::chrono::steady_clock::now();
    double multi = benchService.calculateTotalDiscountsMultiThread(benchHouse);
    auto endMulti = std::chrono::steady_clock::now();

    auto singleMs = std::chrono::duration_cast<std::chrono::milliseconds>(endSingle - startSingle).count();
    auto multiMs = std::chrono::duration_cast<std::chrono::milliseconds>(endMulti - startMulti).count();

    const std::string filename = "benchmark.csv";
    bool writeHeader = !std::filesystem::exists(filename);
    std::ofstream file(filename, std::ios::app);
    if (writeHeader) {
        file << "n,single_ms,multi_ms\n";
    }
    file << n << "," << singleMs << "," << multiMs << "\n";

    view_.printMessage("Benchmark сохранён в benchmark.csv");
    view_.printMessage("Однопоточно: " + std::to_string(singleMs) + " мс");
    view_.printMessage("Многопоточно: " + std::to_string(multiMs) + " мс");
}
