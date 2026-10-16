#ifndef MODEL_ENTITY_ITENANT_H
#define MODEL_ENTITY_ITENANT_H

#include <string>

/**
 * @brief Интерфейс съёмщика (жильца квартиры).
 *
 * Определяет базовые операции, доступные для любого типа съёмщика:
 * - получение категории (обычный / льготный);
 * - вывод информации о съёмщике.
 */
class ITenant {
public:
    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~ITenant() = default;

    /**
     * @brief Возвращает категорию съёмщика.
     * @return Строка, описывающая категорию.
     */
    [[nodiscard]] virtual std::string getCategory() const = 0;

    /**
     * @brief Выводит информацию о съёмщике.
     */
    virtual void outputInfo() const = 0;
};

#endif
