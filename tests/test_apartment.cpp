#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "model/entity/Apartment.h"
#include "model/entity/RegularTenant.h"
#include "model/entity/DiscountTenant.h"
#include <sstream>
#include <iostream>

TEST_CASE("Apartment: basic properties", "[apartment][coverage]") {
    auto t1 = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    auto t2 = std::make_shared<DiscountTenant>("Петрова", 1970, 'F', "пенсионер", "ветеран", 0.3);
    Apartment apt(15, 56.7, {t1, t2});

    REQUIRE(apt.getNumber() == 15);
    REQUIRE(apt.getArea() == 56.7);
    REQUIRE(apt.getTenantCount() == 2);
    REQUIRE(apt.getRegularTenantCount() == 1);
    REQUIRE(apt.getDiscountTenantCount() == 1);
    REQUIRE(apt.getMainTenantCategory() == "обычный");
}

TEST_CASE("Apartment: empty tenants", "[apartment][coverage]") {
    Apartment apt(10, 45.0, {});
    REQUIRE(apt.getTenantCount() == 0);
    REQUIRE(apt.getRegularTenantCount() == 0);
    REQUIRE(apt.getDiscountTenantCount() == 0);
    REQUIRE(apt.getMainTenantCategory() == "");
}

TEST_CASE("Apartment: only discount tenants", "[apartment][coverage]") {
    auto d1 = std::make_shared<DiscountTenant>("A", 1970, 'F', "p", "v", 0.2);
    auto d2 = std::make_shared<DiscountTenant>("B", 1980, 'M', "p", "i", 0.4);
    Apartment apt(5, 50.0, {d1, d2});
    REQUIRE(apt.getMainTenantCategory() == "льготный");
}

TEST_CASE("Apartment: setTenants", "[apartment][coverage]") {
    Apartment apt(1, 30.0, {});
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    apt.setTenants({t});
    REQUIRE(apt.getTenantCount() == 1);
    REQUIRE(apt.getRegularTenantCount() == 1);
}

TEST_CASE("Apartment: outputInfo", "[apartment][coverage]") {
    auto t = std::make_shared<RegularTenant>("Иванов", 1990, 'M', "работающий");
    Apartment apt(5, 50.0, {t});
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    apt.outputInfo();
    std::cout.rdbuf(old);
    std::string out = ss.str();
    REQUIRE(out.find("Квартира №5") != std::string::npos);
    REQUIRE(out.find("Иванов") != std::string::npos);
}
