#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "model/entity/DiscountTenant.h"
#include <sstream>
#include <iostream>

TEST_CASE("DiscountTenant: basic properties", "[tenant][coverage]") {
    DiscountTenant t("Сидорова А.С.", 1970, 'F', "инвалид", "ветеран", 0.3);
    REQUIRE(t.getName() == "Сидорова А.С.");
    REQUIRE(t.getBirthYear() == 1970);
    REQUIRE(t.getGender() == 'F');
    REQUIRE(t.getStatus() == "инвалид");
    REQUIRE(t.getDiscountType() == "ветеран");
    REQUIRE(t.getDiscount() == 0.3);
    REQUIRE(t.getCategory() == "льготный");
}

TEST_CASE("DiscountTenant: setDiscount", "[tenant][coverage]") {
    DiscountTenant t("Кузнецов", 1960, 'M', "пенсионер", "инвалид", 0.25);
    t.setDiscount(0.5);
    REQUIRE(t.getDiscount() == 0.5);
}

TEST_CASE("DiscountTenant: outputInfo", "[tenant][coverage]") {
    DiscountTenant t("Анна", 1975, 'F', "пенсионер", "ветеран", 0.2);
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    t.outputInfo();
    std::cout.rdbuf(old);
    std::string out = ss.str();
    REQUIRE(out.find("Анна") != std::string::npos);
    REQUIRE(out.find("льготный") != std::string::npos);
    REQUIRE(out.find("20%") != std::string::npos);
}

TEST_CASE("DiscountTenant: dynamic_cast to IHasDiscount", "[tenant][coverage]") {
    DiscountTenant t("Борис", 1980, 'M', "работающий", "инвалид", 0.4);
    ITenant* base = &t;
    IHasDiscount* discount = dynamic_cast<IHasDiscount*>(base);
    REQUIRE(discount != nullptr);
    REQUIRE(discount->getDiscount() == 0.4);
}
