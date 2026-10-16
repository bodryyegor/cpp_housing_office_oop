#ifndef MODEL_ENTITY_IHASDISCOUNT_H
#define MODEL_ENTITY_IHASDISCOUNT_H

/**
 * @brief Интерфейс для объектов, имеющих льготу.
 *
 * Обеспечивает доступ к размеру льготы и возможность её изменения.
 */
class IHasDiscount {
public:
    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~IHasDiscount() = default;

    /**
     * @brief Возвращает размер льготы.
     * @return Значение от 0 до 1.
     */
    [[nodiscard]] virtual double getDiscount() const = 0;

    /**
     * @brief Устанавливает новый размер льготы.
     * @param discount Новое значение льготы.
     */
    virtual void setDiscount(double discount) = 0;
};

#endif
