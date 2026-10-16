#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "model/service/HousingService.h"
#include "model/entity/RegularTenant.h"
#include "model/entity/DiscountTenant.h"

TEST_CASE("HousingService: settleApartment", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    house.addApartment(Apartment(5, 50.0, {}));

    service.settleApartment(house, 5, {t});
    const Apartment& apt = house.findApartment(5);
    REQUIRE(apt.getTenantCount() == 1);
}

TEST_CASE("HousingService: vacateApartment", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    house.addApartment(Apartment(5, 50.0, {t}));

    service.vacateApartment(house, 5);
    const Apartment& apt = house.findApartment(5);
    REQUIRE(apt.getTenantCount() == 0);
}

TEST_CASE("HousingService: correctApartmentData", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    house.addApartment(Apartment(5, 50.0, {}));

    Apartment updated(5, 60.0, {});
    service.correctApartmentData(house, 5, updated);
    const Apartment& apt = house.findApartment(5);
    REQUIRE(apt.getArea() == 60.0);
}

TEST_CASE("HousingService: payment without discount", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    house.addApartment(Apartment(5, 60.0, {t}));

    double payment = service.calculatePaymentForApartment(house, 5);
    double expected = 60.0 * 100.0 + 1 * 50.0;
    REQUIRE(std::abs(payment - expected) < 1e-6);
}

TEST_CASE("HousingService: payment with discount", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    auto d = std::make_shared<DiscountTenant>("Анна", 1975, 'F', "пенсионер", "ветеран", 0.2);
    house.addApartment(Apartment(1, 50.0, {d}));

    double payment = service.calculatePaymentForApartment(house, 1);
    double expected = (50.0 * 100.0 + 1 * 50.0) * (1.0 - 0.2);
    REQUIRE(std::abs(payment - expected) < 1e-6);
}

TEST_CASE("HousingService: single vs multi thread", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    auto d1 = std::make_shared<DiscountTenant>("A", 1970, 'F', "p", "v", 0.2);
    auto d2 = std::make_shared<DiscountTenant>("B", 1980, 'M', "p", "i", 0.4);
    house.addApartment(Apartment(1, 50.0, {d1}));
    house.addApartment(Apartment(2, 60.0, {d2}));

    double s = service.calculateTotalDiscountsSingleThread(house);
    double m = service.calculateTotalDiscountsMultiThread(house);
    REQUIRE(std::abs(s - m) < 1e-6);
}

TEST_CASE("HousingService: apartment not found", "[service][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    HousingService service;
    REQUIRE_THROWS_AS(service.settleApartment(house, 5, {}), std::out_of_range);
}
