#ifndef MODEL_SERVICE_HOUSINGSERVICE_H
#define MODEL_SERVICE_HOUSINGSERVICE_H

#include "IService.h"
#include "../repository/House.h"
#include "../entity/ITenant.h"
#include <vector>
#include <memory>

/**
 * @brief Сервис управления жилищным фондом.
 *
 * Реализует бизнес-логику: заселение, расчёт платежей, работа с льготами.
 */
class HousingService : public IService {
public:
    /**
     * @brief Заселить жильцов в квартиру.
     * @param house Дом
     * @param number Номер квартиры
     * @param tenants Список жильцов (обычных или льготных)
     * @throws std::out_of_range если квартира не найдена
     */
    void settleApartment(
        House& house,
        int number,
        const std::vector<std::shared_ptr<ITenant>>& tenants
    );

    /**
     * @brief Исправить данные о квартире.
     * @param house Дом
     * @param number Номер квартиры
     * @param updated Обновлённая квартира
     * @throws std::out_of_range если квартира не найдена
     */
    void correctApartmentData(
        House& house,
        int number,
        const Apartment& updated
    );

    /**
     * @brief Выселить всех жильцов из квартиры.
     * @param house Дом
     * @param number Номер квартиры
     * @throws std::out_of_range если квартира не найдена
     */
    void vacateApartment(
        House& house,
        int number
    );

    /**
     * @brief Рассчитать плату за квартиру.
     * Плата = площадь * paymentPerSqMeter + tenantCount * paymentPerTenant
     * @param house Дом
     * @param number Номер квартиры
     * @return Сумма платежа
     * @throws std::out_of_range если квартира не найдена
     */
    [[nodiscard]] double calculatePaymentForApartment(
        const House& house,
        int number
    ) const;
    
    [[nodiscard]] double calculateApartmentDiscount(const Apartment& apt) const;

    /**
     * @brief Рассчитать общую сумму льгот по дому (однопоточная версия).
     * @param house Дом
     * @return Общая сумма льгот
     */
    [[nodiscard]] double calculateTotalDiscountsSingleThread(
        const House& house
    ) const;

    /**
     * @brief Рассчитать общую сумму льгот по дому (многопоточная версия).
     * Каждая квартира обрабатывается в отдельном потоке (или через пул).
     * @param house Дом
     * @return Общая сумма льгот
     */
    [[nodiscard]] double calculateTotalDiscountsMultiThread(
        const House& house
    ) const;
};

#endif
