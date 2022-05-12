#ifndef CURCULARBUFFER_CIRCULARBUFFER_H
#define CURCULARBUFFER_CIRCULARBUFFER_H

#include <iostream>

template<class T>
class CircularBuffer {
private:
    size_t m_Capacity;
    size_t m_FrontIndex;
    size_t m_BackIndex;

    size_t m_Size = 0;

    T *m_Data;
public:


    class Iterator {
    private:
        T *m_Data;
        size_t m_Index;
        size_t &m_FrontIndex;
        size_t &m_Capacity;


    public:
        /* I had to do it */
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T *Data, size_t Index, size_t &FrontIndex, size_t &Capacity)
        : m_Data(Data)
        , m_Index(Index)
        , m_FrontIndex(FrontIndex)
        , m_Capacity(Capacity) {}

        Iterator(const Iterator &other)
        : m_Data(other.m_Data)
        , m_Index(other.m_Index)
        , m_FrontIndex(other.m_FrontIndex)
        , m_Capacity(other.m_Capacity) {}

        Iterator& operator=(const Iterator &other) {
            if (&other == this) {
                return *this;
            }

            this->m_Data = other.m_Data;
            this->m_Index = other.m_Index;

            return *this;
        }

        Iterator& operator+=(size_t number) {
            m_Index += number;

            return *this;
        }

        Iterator& operator-=(size_t number) {
            m_Index -= number;

            return *this;
        }

        Iterator& operator++() {
            ++m_Index;
            return *this;
        }

        Iterator& operator--() {
            --m_Index;
            return *this;
        }

        Iterator operator+(size_t arg2) {
            Iterator tmp(*this);
            return tmp += arg2;
        }

        Iterator operator-(size_t arg2) {
            Iterator tmp(*this);
            return tmp -= arg2;
        }

        std::ptrdiff_t operator-(const Iterator &other) {
            return this->m_Index - other.m_Index;
        }

        bool operator<(const Iterator &other) {
            return this->m_Index < other.m_Index;
        }

        bool operator==(const Iterator &other) {
            return this->m_Index == other.m_Index;
        }

        bool operator!=(const Iterator &other) {
            return this->m_Index != other.m_Index;
        }

        bool operator>(const Iterator &other) {
            return this->m_Index > other.m_Index;
        }

        bool operator>=(const Iterator &other) {
            return this->m_Index >= other.m_Index;
        }

        bool operator<=(const Iterator &other) {
            return this->m_Index <= other.m_Index;
        }

        T& operator*() {
            return m_Data[(m_FrontIndex + m_Index) % m_Capacity];
        }

        T* operator->() {
            return m_Data + (m_FrontIndex + m_Index) % m_Capacity;
        }
    };

    explicit CircularBuffer(size_t capacity = 16) : m_Capacity(capacity), m_FrontIndex(0), m_BackIndex(0) {
        m_Data = new T[capacity + 1];
    }

    ~CircularBuffer() {
        delete[] m_Data;
    }

    Iterator begin() {
        return Iterator(m_Data, 0, m_FrontIndex, m_Capacity);
    }

    Iterator end() {
        return Iterator(m_Data, m_Size, m_FrontIndex, m_Capacity);
    }

    void push_back(T const &elem) {
        m_Data[m_BackIndex] = elem;
        m_BackIndex = (m_BackIndex + 1) % m_Capacity;
        if (m_Size < m_Capacity) {
            ++m_Size;
        }
    }

    void push_front(T const &elem) {
        m_FrontIndex = (m_Capacity + m_FrontIndex - 1) % m_Capacity;
        m_Data[m_FrontIndex] = elem;
        if (m_Size < m_Capacity) {
            ++m_Size;
        }
    }

    void pop_front() {
        m_FrontIndex = (m_FrontIndex + 1) % m_Capacity;
        if (m_Size > 0) {
            --m_Size;
        }

    }

    void pop_back() {
        m_BackIndex = (m_Capacity + m_BackIndex - 1) % m_Capacity;
        if (m_Size > 0) {
            --m_Size;
        }
    };

    T& operator[](size_t number) {
        if (number < 0 || number >= m_Size) {
            throw std::out_of_range("Size: " + std::to_string(m_Size) + ", Your index: " + std::to_string(number));
        }
        return m_Data[(m_FrontIndex + number) % m_Capacity];
    }

    T const& operator[](size_t number) const {
        if (number < 0 || number >= m_Size) {
            throw std::out_of_range("Size: " + std::to_string(m_Size) + ", Your index: " + std::to_string(number));
        }
        return m_Data[(m_FrontIndex + number) % m_Capacity];
    }

    void resize(size_t newSize) {
        if (newSize < m_Size) {
            throw std::logic_error("New size should be >= current fill");
        }

        T *newData = new T[newSize + 1];
        size_t j = 0;
        for (auto i = begin(); i != end(); ++i, ++j) {
            newData[j] = *i;
        }

        delete[] m_Data;
        m_Data = newData;
        m_Capacity = newSize;
        m_FrontIndex = 0;
        m_BackIndex = j % m_Capacity;
    }

    T& first() {
        return *begin();
    }

    T& last() {
        return *(end() - 1);
    }
};


#endif //CURCULARBUFFER_CIRCULARBUFFER_H
