#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "model/repository/House.h"
#include "model/entity/RegularTenant.h"
#include <sstream>
#include <iostream>

TEST_CASE("House: basic properties", "[house][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    REQUIRE(house.getStreetName() == "Ленина");
    REQUIRE(house.getHouseNumber() == "10");
    REQUIRE(house.getPaymentPerSqMeter() == 100.0);
    REQUIRE(house.getPaymentPerTenant() == 50.0);
}

TEST_CASE("House: add/find/remove apartment", "[house][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    Apartment apt(5, 50.0, {t});
    house.addApartment(apt);

    const Apartment& found = house.findApartment(5);
    REQUIRE(found.getNumber() == 5);

    house.removeApartment(5);
    REQUIRE_THROWS_AS(house.findApartment(5), std::out_of_range);
}

TEST_CASE("House: duplicate apartment", "[house][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    Apartment a1(5, 50.0, {});
    Apartment a2(5, 60.0, {});
    house.addApartment(a1);
    REQUIRE_THROWS_AS(house.addApartment(a2), std::invalid_argument);
}

TEST_CASE("House: outputAllApartments", "[house][coverage]") {
    House house("Ленина", "10", 100.0, 50.0);
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    house.addApartment(Apartment(1, 30.0, {t}));
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    house.outputAllApartments();
    std::cout.rdbuf(old);
    std::string out = ss.str();
    REQUIRE(out.find("Квартира №1") != std::string::npos);
}
