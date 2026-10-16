#include "model/repository/House.h"
#include <stdexcept>

House::House(
    std::string streetName,
    std::string houseNumber,
    double paymentPerSqMeter,
    double paymentPerTenant
) : streetName(std::move(streetName)),
    houseNumber(std::move(houseNumber)),
    paymentPerSqMeter(paymentPerSqMeter),
    paymentPerTenant(paymentPerTenant) {}

void House::addApartment(const Apartment& apartment) {
    int number = apartment.getNumber();
    if (!apartments.insert(number, Apartment(apartment))) {
        throw std::invalid_argument("Квартира с таким номером уже существует");
    }
}

const Apartment& House::findApartment(int number) const {
    const Apartment* apt = apartments.find(number);
    if (!apt) {
        throw std::out_of_range("Квартира не найдена");
    }
    return *apt;
}

Apartment& House::findApartment(int number) {
    Apartment* apt = apartments.find(number);
    if (!apt) {
        throw std::out_of_range("Квартира не найдена");
    }
    return *apt;
}

void House::removeApartment(int number) {
    if (!apartments.erase(number)) {
        throw std::out_of_range("Квартира не найдена");
    }
}

void House::outputAllApartments() const {
    for (auto it = apartments.begin(); it != apartments.end(); ++it) {
        it->value.outputInfo();
    }
}
