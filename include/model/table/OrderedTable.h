#ifndef MODEL_TABLE_ORDEREDTABLE_H
#define MODEL_TABLE_ORDEREDTABLE_H

#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <utility>
#include <algorithm>
#include <concepts>

/**
 * @brief Шаблонный контейнер "упорядоченная таблица".
 *
 * Хранит пары (ключ, значение), упорядоченные по возрастанию ключа.
 * Обеспечивает вставку, поиск, удаление и итерацию по элементам.
 *
 * @tparam Key тип ключа
 * @tparam Value тип значения
 */
template <std::totally_ordered Key, typename Value>
class OrderedTable {
private:
    /**
     * @brief Внутренний узел таблицы.
     */
    struct Node {
        Key key;
        Value value;
    };

    std::unique_ptr<Node[]> data;
    std::size_t size_;
    std::size_t capacity_;

    /**
     * @brief Увеличивает ёмкость таблицы при необходимости.
     * @param new_capacity Новая ёмкость
     */
    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        auto new_data = std::make_unique<Node[]>(new_capacity);
        std::move(data.get(), data.get() + size_, new_data.get());
        data = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    /**
     * @brief Random-access итератор для упорядоченной таблицы.
     */
    class iterator {
    private:
        Node* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = Node*;
        using reference = Node&;

        /**
         * @brief Конструктор итератора.
         * @param p Указатель на узел
         */
        explicit iterator(Node* p) : ptr(p) {}

        /**
         * @brief Разыменование итератора.
         * @return Ссылка на узел
         */
        reference operator*() const { return *ptr; }

        /**
         * @brief Доступ к членам узла.
         * @return Указатель на узел
         */
        pointer operator->() const { return ptr; }

        /**
         * @brief Префиксный инкремент.
         */
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        /**
         * @brief Постфиксный инкремент.
         */
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Префиксный декремент.
         */
        iterator& operator--() {
            --ptr;
            return *this;
        }

        /**
         * @brief Постфиксный декремент.
         */
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Арифметика: +=
         */
        iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        /**
         * @brief Арифметика: +
         */
        iterator operator+(difference_type n) const {
            return iterator(ptr + n);
        }

        /**
         * @brief Арифметика: -=
         */
        iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        /**
         * @brief Арифметика: -
         */
        iterator operator-(difference_type n) const {
            return iterator(ptr - n);
        }

        /**
         * @brief Разность двух итераторов.
         */
        difference_type operator-(const iterator& other) const {
            return ptr - other.ptr;
        }

        /**
         * @brief Доступ по индексу.
         */
        reference operator[](difference_type n) const {
            return *(ptr + n);
        }

        /**
         * @brief Сравнение на равенство.
         */
        bool operator==(const iterator& other) const { return ptr == other.ptr; }

        /**
         * @brief Сравнение на неравенство.
         */
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        /**
         * @brief Меньше.
         */
        bool operator<(const iterator& other) const { return ptr < other.ptr; }

        /**
         * @brief Меньше или равно.
         */
        bool operator<=(const iterator& other) const { return ptr <= other.ptr; }

        /**
         * @brief Больше.
         */
        bool operator>(const iterator& other) const { return ptr > other.ptr; }

        /**
         * @brief Больше или равно.
         */
        bool operator>=(const iterator& other) const { return ptr >= other.ptr; }
    };

    /**
     * @brief Константный random-access итератор.
     */
    class const_iterator {
    private:
        const Node* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = const Node;
        using difference_type = std::ptrdiff_t;
        using pointer = const Node*;
        using reference = const Node&;

        /**
         * @brief Конструктор константного итератора.
         * @param p Указатель на узел
         */
        explicit const_iterator(const Node* p) : ptr(p) {}

        /**
         * @brief Конструктор из обычного итератора.
         */
        const_iterator(iterator it) : ptr(it.operator->()) {}

        /**
         * @brief Разыменование итератора.
         */
        reference operator*() const { return *ptr; }

        /**
         * @brief Доступ к членам узла.
         */
        pointer operator->() const { return ptr; }

        /**
         * @brief Префиксный инкремент.
         */
        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        /**
         * @brief Постфиксный инкремент.
         */
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Префиксный декремент.
         */
        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        /**
         * @brief Постфиксный декремент.
         */
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Арифметика: +=
         */
        const_iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        /**
         * @brief Арифметика: +
         */
        const_iterator operator+(difference_type n) const {
            return const_iterator(ptr + n);
        }

        /**
         * @brief Арифметика: -=
         */
        const_iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        /**
         * @brief Арифметика: -
         */
        const_iterator operator-(difference_type n) const {
            return const_iterator(ptr - n);
        }

        /**
         * @brief Разность двух итераторов.
         */
        difference_type operator-(const const_iterator& other) const {
            return ptr - other.ptr;
        }

        /**
         * @brief Доступ по индексу.
         */
        reference operator[](difference_type n) const {
            return *(ptr + n);
        }

        /**
         * @brief Сравнение на равенство.
         */
        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }

        /**
         * @brief Сравнение на неравенство.
         */
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }

        /**
         * @brief Меньше.
         */
        bool operator<(const const_iterator& other) const { return ptr < other.ptr; }

        /**
         * @brief Меньше или равно.
         */
        bool operator<=(const const_iterator& other) const { return ptr <= other.ptr; }

        /**
         * @brief Больше.
         */
        bool operator>(const const_iterator& other) const { return ptr > other.ptr; }

        /**
         * @brief Больше или равно.
         */
        bool operator>=(const const_iterator& other) const { return ptr >= other.ptr; }
    };

    /**
     * @brief Конструктор по умолчанию.
     */
    OrderedTable() : data(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Получить количество элементов в таблице.
     * @return Число элементов
     */
    std::size_t size() const noexcept { return size_; }

    /**
     * @brief Вставить элемент с заданным ключом.
     * Если ключ уже существует, вставка не выполняется.
     * @param key Ключ
     * @param value Значение (перемещается)
     * @return true, если вставка выполнена; false, если ключ уже существует
     */
    bool insert(const Key& key, Value&& value) {
        auto it = std::lower_bound(
            data.get(), data.get() + size_, key,
            [](const Node& a, const Key& k) { return a.key < k; }
        );
        std::size_t idx = it - data.get();

        if (idx < size_ && key == it->key) {
            return false;
        }

        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 4 : capacity_ * 2);
        }

        for (std::size_t i = size_; i > idx; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[idx].key = key;
        data[idx].value = std::move(value);
        ++size_;
        return true;
    }

    /**
     * @brief Найти элемент по ключу (неконстантная версия).
     * @param key Ключ для поиска
     * @return Указатель на значение или nullptr, если не найдено
     */
    Value* find(const Key& key) {
        auto it = std::lower_bound(
            data.get(), data.get() + size_, key,
            [](const Node& a, const Key& k) { return a.key < k; }
        );
        if (it != data.get() + size_ && key == it->key) {
            return &it->value;
        }
        return nullptr;
    }

    /**
     * @brief Найти элемент по ключу (константная версия).
     * @param key Ключ для поиска
     * @return Указатель на значение или nullptr, если не найдено
     */
    const Value* find(const Key& key) const {
        auto it = std::lower_bound(
            data.get(), data.get() + size_, key,
            [](const Node& a, const Key& k) { return a.key < k; }
        );
        if (it != data.get() + size_ && key == it->key) {
            return &it->value;
        }
        return nullptr;
    }

    /**
     * @brief Удалить элемент по ключу.
     * @param key Ключ для удаления
     * @return true, если удаление выполнено; false, если ключ не найден
     */
    bool erase(const Key& key) {
        auto it = std::lower_bound(
            data.get(), data.get() + size_, key,
            [](const Node& a, const Key& k) { return a.key < k; }
        );
        if (it == data.get() + size_ || key != it->key) {
            return false;
        }
        std::size_t idx = it - data.get();
        for (std::size_t i = idx; i + 1 < size_; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
        return true;
    }

    /**
     * @brief Получить итератор на начало таблицы.
     */
    iterator begin() noexcept { return iterator(data.get()); }

    /**
     * @brief Получить итератор на конец таблицы.
     */
    iterator end() noexcept { return iterator(data.get() + size_); }

    /**
     * @brief Получить константный итератор на начало таблицы.
     */
    const_iterator begin() const noexcept { return const_iterator(data.get()); }

    /**
     * @brief Получить константный итератор на конец таблицы.
     */
    const_iterator end() const noexcept { return const_iterator(data.get() + size_); }
};

#endif
