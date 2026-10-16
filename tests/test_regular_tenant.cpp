#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "model/entity/RegularTenant.h"
#include <sstream>
#include <iostream>

TEST_CASE("RegularTenant: basic properties", "[tenant][coverage]") {
    RegularTenant t("Иванов И.И.", 1990, 'M', "работающий");
    REQUIRE(t.getName() == "Иванов И.И.");
    REQUIRE(t.getBirthYear() == 1990);
    REQUIRE(t.getGender() == 'M');
    REQUIRE(t.getStatus() == "работающий");
    REQUIRE(t.getCategory() == "обычный");
}

TEST_CASE("RegularTenant: outputInfo", "[tenant][coverage]") {
    RegularTenant t("Петров", 1985, 'F', "пенсионер");
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    t.outputInfo();
    std::cout.rdbuf(old);
    std::string out = ss.str();
    REQUIRE(out.find("Петров") != std::string::npos);
    REQUIRE(out.find("обычный") != std::string::npos);
}
