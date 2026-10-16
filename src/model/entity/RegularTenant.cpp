#include "model/entity/RegularTenant.h"
#include <iostream>

RegularTenant::RegularTenant(std::string name, int birthYear, char gender, std::string status)
    : name(std::move(name)), birthYear(birthYear), gender(gender), status(std::move(status)) {}

std::string RegularTenant::getCategory() const {
    return "обычный";
}

void RegularTenant::outputInfo() const {
    std::cout << "ФИО: " << name
              << ", Год рождения: " << birthYear
              << ", Пол: " << gender
              << ", Статус: " << status
              << ", Категория: " << getCategory() << "\n";
}
