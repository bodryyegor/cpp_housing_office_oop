#ifndef MODEL_ENTITY_DISCOUNTTENANT_H
#define MODEL_ENTITY_DISCOUNTTENANT_H

#include "RegularTenant.h"
#include "IHasDiscount.h"
#include <string>

/**
 * @brief Льготный съёмщик — расширение обычного съёмщика.
 *
 * Добавляет информацию о типе и размере льготы.
 */
class DiscountTenant : public RegularTenant, public IHasDiscount {
private:
    std::string discountType;
    double discountPercent;

public:
    /**
     * @brief Конструктор с параметрами.
     * @param name Фамилия и инициалы
     * @param birthYear Год рождения
     * @param gender Пол ('M' или 'F')
     * @param status Статус
     * @param discountType Тип льготы
     * @param discountPercent Размер льготы
     */
    DiscountTenant(
        std::string name,
        int birthYear,
        char gender,
        std::string status,
        std::string discountType,
        double discountPercent
    );

    /**
     * @brief Возвращает размер льготы.
     * @return Значение от 0.0 до 1.0
     */
    [[nodiscard]] double getDiscount() const override;

    /**
     * @brief Устанавливает новый размер льготы.
     * @param discount Новое значение льготы
     */
    void setDiscount(double discount) override;

    /**
     * @brief Возвращает категорию съёмщика.
     * @return Строка "льготный"
     */
    [[nodiscard]] std::string getCategory() const override;

    /**
     * @brief Выводит информацию о съёмщике.
     */
    void outputInfo() const override;

    [[nodiscard]] const std::string& getDiscountType() const { return discountType; }
};

#endif
