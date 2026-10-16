#include "model/entity/DiscountTenant.h"
#include <iostream>

DiscountTenant::DiscountTenant(
    std::string name,
    int birthYear,
    char gender,
    std::string status,
    std::string discountType,
    double discountPercent
) : RegularTenant(std::move(name), birthYear, gender, std::move(status)),
    discountType(std::move(discountType)),
    discountPercent(discountPercent) {}

double DiscountTenant::getDiscount() const {
    return discountPercent;
}

void DiscountTenant::setDiscount(double discount) {
    discountPercent = discount;
}

std::string DiscountTenant::getCategory() const {
    return "льготный";
}

void DiscountTenant::outputInfo() const {
    std::cout << "ФИО: " << getName()
              << ", Год рождения: " << getBirthYear()
              << ", Пол: " << getGender()
              << ", Статус: " << getStatus()
              << ", Тип льготы: " << discountType
              << ", Размер льготы: " << discountPercent * 100 << "%"
              << ", Категория: " << getCategory() << "\n";
}
