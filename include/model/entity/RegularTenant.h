#ifndef MODEL_ENTITY_REGULARTENANT_H
#define MODEL_ENTITY_REGULARTENANT_H

#include "ITenant.h"
#include <string>

/**
 * @brief Обычный съёмщик (жилец без льгот).
 *
 * Содержит основные данные о жильце: ФИО, год рождения, пол, статус.
 */
class RegularTenant : public ITenant {
private:
    std::string name;
    int birthYear;
    char gender;
    std::string status;

public:
    /**
     * @brief Конструктор с параметрами.
     * @param name Фамилия и инициалы
     * @param birthYear Год рождения
     * @param gender Пол ('M' или 'F')
     * @param status Статус
     */
    RegularTenant(std::string name, int birthYear, char gender, std::string status);

    /**
     * @brief Возвращает категорию съёмщика.
     * @return Строка "обычный"
     */
    [[nodiscard]] std::string getCategory() const override;

    /**
     * @brief Выводит информацию о съёмщике.
     */
    void outputInfo() const override;

    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getBirthYear() const { return birthYear; }
    [[nodiscard]] char getGender() const { return gender; }
    [[nodiscard]] const std::string& getStatus() const { return status; }
};

#endif
