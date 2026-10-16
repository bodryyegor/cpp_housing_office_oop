#ifndef MODEL_SERVICE_ISERVICE_H
#define MODEL_SERVICE_ISERVICE_H

/**
 * @brief Базовый интерфейс для всех сервисов.
 *
 */
class IService {
public:
    /**
     * @brief Виртуальный деструктор.
     *
     * Обеспечивает корректное удаление полиморфных объектов.
     */
    virtual ~IService() = default;
};

#endif
