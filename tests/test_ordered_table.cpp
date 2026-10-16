#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "model/table/OrderedTable.h"
#include <vector>
#include <string>

TEST_CASE("OrderedTable: empty table", "[ordered_table][coverage]") {
    OrderedTable<int, std::string> table;
    REQUIRE(table.size() == 0);
    REQUIRE(table.begin() == table.end());
    REQUIRE(table.find(42) == nullptr);
    REQUIRE_FALSE(table.erase(1));
    table.outputAll();
}

TEST_CASE("OrderedTable: single element", "[ordered_table][coverage]") {
    OrderedTable<int, int> table;
    REQUIRE(table.insert(100, 42));
    REQUIRE(table.size() == 1);
    auto* val = table.find(100);
    REQUIRE(val != nullptr);
    REQUIRE(*val == 42);
    REQUIRE(table.erase(100));
    REQUIRE(table.size() == 0);
}

TEST_CASE("OrderedTable: insert in all orders", "[ordered_table][coverage]") {
    OrderedTable<int, char> table;
    table.insert(3, 'c');
    table.insert(2, 'b');
    table.insert(1, 'a');
    std::vector<char> actual;
    for (const auto& node : table) actual.push_back(node.value);
    REQUIRE(actual == std::vector<char>{'a', 'b', 'c'});
}

TEST_CASE("OrderedTable: duplicate key", "[ordered_table][coverage]") {
    OrderedTable<std::string, int> table;
    REQUIRE(table.insert("key", 1));
    REQUIRE_FALSE(table.insert("key", 2));
    REQUIRE(table.size() == 1);
    REQUIRE(*table.find("key") == 1);
}

TEST_CASE("OrderedTable: erase all positions", "[ordered_table][coverage]") {
    OrderedTable<int, char> table;
    table.insert(1, 'a');
    table.insert(2, 'b');
    table.insert(3, 'c');
    REQUIRE(table.erase(2));
    REQUIRE(table.erase(1));
    REQUIRE(table.erase(3));
    REQUIRE(table.size() == 0);
}

TEST_CASE("OrderedTable: const correctness", "[ordered_table][coverage]") {
    OrderedTable<int, std::string> table;
    table.insert(1, "test");
    const auto& ctable = table;
    REQUIRE(*ctable.find(1) == "test");
    for (auto it = ctable.begin(); it != ctable.end(); ++it) {
        REQUIRE(it->value == "test");
    }
}

TEST_CASE("OrderedTable: reserve and growth", "[ordered_table][coverage]") {
    OrderedTable<int, int> table;
    for (int i = 0; i < 10; ++i) {
        REQUIRE(table.insert(i, i * 10));
    }
    REQUIRE(table.size() == 10);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(*table.find(i) == i * 10);
    }
}

TEST_CASE("OrderedTable: default constructor", "[ordered_table][coverage]") {
    OrderedTable<int, int> table;
    REQUIRE(table.size() == 0);
}

TEST_CASE("OrderedTable: random access iterator", "[ordered_table][coverage]") {
    OrderedTable<int, char> table;
    table.insert(1, 'a');
    table.insert(2, 'b');
    table.insert(3, 'c');

    auto it = table.begin();
    REQUIRE((it + 1)->value == 'b');
    REQUIRE((table.end() - table.begin()) == 3);
    REQUIRE(it[2].value == 'c');
}
