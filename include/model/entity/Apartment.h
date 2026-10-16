#ifndef MODEL_ENTITY_APARTMENT_H
#define MODEL_ENTITY_APARTMENT_H

#include "ITenant.h"
#include <vector>
#include <memory>

/**
 * @brief Квартира в доме.
 *
 * Содержит информацию о номере, площади и жильцах.
 */
class Apartment {
private:
    int number;
    double area;
    int tenantCount;
    std::vector<std::shared_ptr<ITenant>> tenants;

public:
    /**
     * @brief Конструктор по умолчанию.
     */
    Apartment() = default;
    /**
     * @brief Конструктор с параметрами.
     * @param number Номер квартиры
     * @param area Площадь (в кв. метрах)
     * @param tenants Вектор жильцов (обычных или льготных)
     */
    Apartment(int number, double area, std::vector<std::shared_ptr<ITenant>> tenants);

    /**
     * @brief Выводит информацию о квартире (номер, площадь, жильцы).
     */
    void outputInfo() const;

    [[nodiscard]] int getNumber() const { return number; }
    [[nodiscard]] double getArea() const { return area; }
    [[nodiscard]] int getTenantCount() const { return tenantCount; }

    /**
     * @brief Устанавливает новый список жильцов.
     * Обновляет tenantCount автоматически.
     */
    void setTenants(const std::vector<std::shared_ptr<ITenant>>& newTenants);

    /**
     * @brief Возвращает количество обычных жильцов.
     */
    [[nodiscard]] int getRegularTenantCount() const;
    
    /**
    * @brief Получить список жильцов.
    * @return Константная ссылка на вектор жильцов
    */
    [[nodiscard]] const std::vector<std::shared_ptr<ITenant>>& getTenants() const {
        return tenants;
    }

    /**
     * @brief Возвращает количество льготных жильцов.
     */
    [[nodiscard]] int getDiscountTenantCount() const;

    /**
     * @brief Возвращает категорию главного жильца (первого в списке).
     * @return "обычный" или "льготный", либо пустая строка, если жильцов нет.
     */
    [[nodiscard]] std::string getMainTenantCategory() const;
};

#endif
