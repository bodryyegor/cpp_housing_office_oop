#ifndef MODEL_REPOSITORY_HOUSE_H
#define MODEL_REPOSITORY_HOUSE_H

#include "../table/OrderedTable.h"
#include "../entity/Apartment.h"
#include <string>

/**
 * @brief Дом.
 *
 * Содержит информацию об адресе, тарифах и упорядоченную таблицу квартир.
 */
class House {
private:
    std::string streetName;
    std::string houseNumber;
    double paymentPerSqMeter;
    double paymentPerTenant;
    OrderedTable<int, Apartment> apartments;

public:
    /**
     * @brief Конструктор по умолчанию.
     */
    House() = default;

    /**
     * @brief Конструктор с параметрами.
     * @param streetName Название улицы
     * @param houseNumber Номер дома
     * @param paymentPerSqMeter Плата за кв. метр
     * @param paymentPerTenant Плата за жильца
     */
    House(
        std::string streetName,
        std::string houseNumber,
        double paymentPerSqMeter,
        double paymentPerTenant
    );

    /**
     * @brief Добавить квартиру в дом.
     * @param apartment Квартира для добавления
     * @throws std::invalid_argument если квартира с таким номером уже существует
     */
    void addApartment(const Apartment& apartment);

    /**
     * @brief Найти квартиру по номеру.
     * @param number Номер квартиры
     * @return Константная ссылка на квартиру
     * @throws std::out_of_range если квартира не найдена
     */
    [[nodiscard]] const Apartment& findApartment(int number) const;

    /**
     * @brief Найти квартиру по номеру (неконстантная версия).
     * @param number Номер квартиры
     * @return Ссылка на квартиру
     * @throws std::out_of_range если квартира не найдена
     */
    Apartment& findApartment(int number);

    /**
     * @brief Удалить квартиру по номеру.
     * @param number Номер квартиры
     * @throws std::out_of_range если квартира не найдена
     */
    void removeApartment(int number);

    /**
     * @brief Вывести информацию обо всех квартирах в доме.
     */
    void outputAllApartments() const;

    [[nodiscard]] const std::string& getStreetName() const { return streetName; }
    [[nodiscard]] const std::string& getHouseNumber() const { return houseNumber; }
    [[nodiscard]] double getPaymentPerSqMeter() const { return paymentPerSqMeter; }
    [[nodiscard]] double getPaymentPerTenant() const { return paymentPerTenant; }

    /**
     * @brief Получить итератор на начало таблицы квартир.
     */
    auto begin() const noexcept { return apartments.begin(); }

    /**
     * @brief Получить итератор на конец таблицы квартир.
     */
    auto end() const noexcept { return apartments.end(); }
};

#endif
