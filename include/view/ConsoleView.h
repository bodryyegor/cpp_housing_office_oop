#ifndef VIEW_CONSOLEVIEW_H
#define VIEW_CONSOLEVIEW_H

#include <string>

/**
 * @brief Консольное представление.
 */
class ConsoleView {
public:
    /**
     * @brief Показать меню.
     */
    void showMenu() const;

    /**
     * @brief Прочитать выбор меню.
     */
    int readMenuChoice() const;

    /**
     * @brief Прочитать строку.
     */
    std::string readString(const std::string& prompt) const;

    /**
     * @brief Прочитать целое число с проверкой диапазона.
     */
    int readInt(const std::string& prompt, int min_value = 0, int max_value = 10000) const;

    /**
     * @brief Прочитать вещественное число с проверкой минимума.
     */
    double readDouble(const std::string& prompt, double min_value = 0.0) const;

    /**
     * @brief Вывести сообщение.
     */
    void printMessage(const std::string& message) const;

    /**
     * @brief Вывести ошибку.
     */
    void printError(const std::string& message) const;
};

#endif
