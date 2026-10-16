// src/view/ConsoleView.cpp

#include "view/ConsoleView.h"
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
void clearLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
}

void ConsoleView::showMenu() const {
    std::cout << "\n=== Жилищная система ===\n";
    std::cout << "1. Создать дом\n";
    std::cout << "2. Добавить квартиру\n";
    std::cout << "3. Заселить квартиру\n";
    std::cout << "4. Рассчитать платёж\n";
    std::cout << "5. Льготы (однопоточно)\n";
    std::cout << "6. Льготы (многопоточно)\n";
    std::cout << "7. Показать все квартиры\n";
    std::cout << "8. Benchmark (сравнение времени)\n";
    std::cout << "0. Выход\n";
}

int ConsoleView::readMenuChoice() const {
    return readInt("Ваш выбор: ", 0, 8);
}

std::string ConsoleView::readString(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin >> std::ws, value)) {
        throw std::runtime_error("Поток ввода закрыт");
    }
    return value;
}

int ConsoleView::readInt(const std::string& prompt, int min_value, int max_value) const {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            if (value >= min_value && value <= max_value) {
                clearLine();
                return value;
            }
        } else if (std::cin.eof()) {
            throw std::runtime_error("Поток ввода закрыт");
        }
        printError("Некорректное целое число.");
        clearLine();
    }
}

double ConsoleView::readDouble(const std::string& prompt, double min_value) const {
    while (true) {
        std::cout << prompt;
        double value = 0.0;
        if (std::cin >> value) {
            if (value >= min_value) {
                clearLine();
                return value;
            }
        } else if (std::cin.eof()) {
            throw std::runtime_error("Поток ввода закрыт");
        }
        printError("Некорректное число.");
        clearLine();
    }
}

void ConsoleView::printMessage(const std::string& message) const {
    std::cout << "[INFO] " << message << "\n";
}

void ConsoleView::printError(const std::string& message) const {
    std::cout << "[ERROR] " << message << "\n";
}
