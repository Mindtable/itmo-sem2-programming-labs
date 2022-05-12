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


    class iterator {
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

        iterator(T *Data, size_t Index, size_t &FrontIndex, size_t &Capacity)
        : m_Data(Data)
        , m_Index(Index)
        , m_FrontIndex(FrontIndex)
        , m_Capacity(Capacity) {}

        iterator(const iterator &other)
        : m_Data(other.m_Data)
        , m_Index(other.m_Index)
        , m_FrontIndex(other.m_FrontIndex)
        , m_Capacity(other.m_Capacity) {}

        iterator& operator=(const iterator &other) {
            if (&other == this) {
                return *this;
            }

            this->m_Data = other.m_Data;
            this->m_Index = other.m_Index;

            return *this;
        }

        iterator& operator+=(size_t number) {
            m_Index += number;

            return *this;
        }

        iterator& operator-=(size_t number) {
            m_Index -= number;

            return *this;
        }

        iterator& operator++() {
            ++m_Index;
            return *this;
        }

        iterator& operator--() {
            --m_Index;
            return *this;
        }

        iterator operator+(size_t arg2) {
            iterator tmp(*this);
            return tmp += arg2;
        }

        iterator operator-(size_t arg2) {
            iterator tmp(*this);
            return tmp -= arg2;
        }

        std::ptrdiff_t operator-(const iterator &other) {
            return this->m_Index - other.m_Index;
        }

        bool operator<(const iterator &other) {
            return this->m_Index < other.m_Index;
        }

        bool operator==(const iterator &other) {
            return this->m_Index == other.m_Index;
        }

        bool operator!=(const iterator &other) {
            return this->m_Index != other.m_Index;
        }

        bool operator>(const iterator &other) {
            return this->m_Index > other.m_Index;
        }

        bool operator>=(const iterator &other) {
            return this->m_Index >= other.m_Index;
        }

        bool operator<=(const iterator &other) {
            return this->m_Index <= other.m_Index;
        }

        T& operator*() {
            return m_Data[(m_FrontIndex + m_Index) % m_Capacity];
        }

        T* operator->() {
            return m_Data + (m_FrontIndex + m_Index) % m_Capacity;
        }
    };

    class const_iterator {
    private:
        T *m_Data;
        size_t m_Index;
        const size_t &m_FrontIndex;
        const size_t &m_Capacity;


    public:
        /* I had to do it */
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        const_iterator(T *Data, size_t Index, const size_t &FrontIndex, const size_t &Capacity)
                : m_Data(Data)
                , m_Index(Index)
                , m_FrontIndex(FrontIndex)
                , m_Capacity(Capacity) {}

        const_iterator(const const_iterator &other)
                : m_Data(other.m_Data)
                , m_Index(other.m_Index)
                , m_FrontIndex(other.m_FrontIndex)
                , m_Capacity(other.m_Capacity) {}

        const_iterator& operator=(const const_iterator &other) {
            if (&other == this) {
                return *this;
            }

            this->m_Data = other.m_Data;
            this->m_Index = other.m_Index;

            return *this;
        }

        const_iterator& operator+=(size_t number) {
            m_Index += number;

            return *this;
        }

        const_iterator& operator-=(size_t number) {
            m_Index -= number;

            return *this;
        }

        const_iterator& operator++() {
            ++m_Index;
            return *this;
        }

        const_iterator& operator--() {
            --m_Index;
            return *this;
        }

        const_iterator operator+(size_t arg2) {
            const_iterator tmp(*this);
            return tmp += arg2;
        }

        const_iterator operator-(size_t arg2) {
            const_iterator tmp(*this);
            return tmp -= arg2;
        }

        std::ptrdiff_t operator-(const const_iterator &other) {
            return this->m_Index - other.m_Index;
        }

        bool operator<(const const_iterator &other) {
            return this->m_Index < other.m_Index;
        }

        bool operator==(const const_iterator &other) {
            return this->m_Index == other.m_Index;
        }

        bool operator!=(const const_iterator &other) {
            return this->m_Index != other.m_Index;
        }

        bool operator>(const const_iterator &other) {
            return this->m_Index > other.m_Index;
        }

        bool operator>=(const const_iterator &other) {
            return this->m_Index >= other.m_Index;
        }

        bool operator<=(const const_iterator &other) {
            return this->m_Index <= other.m_Index;
        }

        const T& operator*() {
            return m_Data[(m_FrontIndex + m_Index) % m_Capacity];
        }

        const T* operator->() {
            return m_Data + (m_FrontIndex + m_Index) % m_Capacity;
        }
    };

    explicit CircularBuffer(size_t capacity = 16) : m_Capacity(capacity), m_FrontIndex(0), m_BackIndex(0) {
        m_Data = new T[capacity + 1];
    }

    CircularBuffer(const CircularBuffer<T>& other)
    : m_Capacity(other.m_Capacity)
    , m_Size(other.m_Size)
    , m_FrontIndex(other.m_FrontIndex)
    , m_BackIndex(other.m_BackIndex)
    , m_Data(new T[m_Capacity + 1]){
        for (size_t i = 0; i != other.m_Capacity + 1; ++i) {
            m_Data[i] = other.m_Data[i];
        }
    }

    CircularBuffer<T>& operator=(const CircularBuffer<T>& other) {
        if (this == &other) {
            return *this;
        }

        this->m_FrontIndex = 0;
        this->m_BackIndex = 0;
        this->m_Size = 0;
        delete[] this->m_Data;
        this->m_Data = new T[std::max(this->m_Capacity, other.m_Capacity)];
        this->m_Capacity = std::max(this->m_Capacity, other.m_Capacity);

        for (const auto& elem: other) {
            this->push_back(elem);
            std::cout << "Push " << elem << std::endl;
        }

        return *this;
    }

    ~CircularBuffer() {
        delete[] m_Data;
    }

    iterator begin() {
        return iterator(m_Data, 0, m_FrontIndex, m_Capacity);
    }

    iterator end() {
        return iterator(m_Data, m_Size, m_FrontIndex, m_Capacity);
    }

    const_iterator begin() const {
        return const_iterator(m_Data, 0, m_FrontIndex, m_Capacity);
    }

    const_iterator end() const {
        return const_iterator(m_Data, m_Size, m_FrontIndex, m_Capacity);
    }

    void push_back(T const &elem) {
        m_Data[m_BackIndex] = elem;
        m_BackIndex = (m_BackIndex + 1) % m_Capacity;
        if (m_Size < m_Capacity) {
            ++m_Size;
        }
        std::cout << m_Capacity << ' ' << m_FrontIndex << ' ' << m_BackIndex << ' ' << m_Size << std::endl;
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
        return m_Data[(m_FrontIndex + number) % m_Capacity];
    }

    T const& operator[](size_t number) const {
        return m_Data[(m_FrontIndex + number) % m_Capacity];
    }

    void resize(size_t newSize) {
        CircularBuffer<T> tmp(*this);

        this->m_Capacity = newSize;
        *this = tmp;
    }

    T& first() {
        return *begin();
    }

    T& last() {
        return *(end() - 1);
    }
};


#endif //CURCULARBUFFER_CIRCULARBUFFER_H
