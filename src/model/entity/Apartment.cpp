#include "model/entity/Apartment.h"
#include <iostream>

Apartment::Apartment(int number, double area, std::vector<std::shared_ptr<ITenant>> tenants)
    : number(number), area(area), tenants(std::move(tenants)) {
    tenantCount = static_cast<int>(this->tenants.size());
}

void Apartment::outputInfo() const {
    std::cout << "\n--- Квартира №" << number << " ---\n";
    std::cout << "Площадь: " << area << " м²\n";
    std::cout << "Количество жильцов: " << tenantCount << "\n";
    std::cout << "Жильцы:\n";
    for (const auto& tenant : tenants) {
        tenant->outputInfo();
    }
}

void Apartment::setTenants(const std::vector<std::shared_ptr<ITenant>>& newTenants) {
    tenants = newTenants;
    tenantCount = static_cast<int>(tenants.size());
}

int Apartment::getRegularTenantCount() const {
    int count = 0;
    for (const auto& tenant : tenants) {
        if (tenant->getCategory() == "обычный") {
            ++count;
        }
    }
    return count;
}

int Apartment::getDiscountTenantCount() const {
    int count = 0;
    for (const auto& tenant : tenants) {
        if (tenant->getCategory() == "льготный") {
            ++count;
        }
    }
    return count;
}

std::string Apartment::getMainTenantCategory() const {
    if (tenants.empty()) {
        return "";
    }
    return tenants[0]->getCategory();
}
