#pragma once
#include <iostream>
/**
 * 带迭代器和空间配置器
 */

template <typename T>
class Iterator
{
public:
    Iterator(T* ptr = nullptr) : m_ptr(ptr){}
    T& operator*() const
    {
        return *m_ptr;
    }
    T* operator->() const
    {
        return m_ptr;
    }
    Iterator& operator++()
    {
        ++m_ptr;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ++tmp;
        return tmp;
    }
    Iterator& operator--()
    {
        --m_ptr;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp = *this;
        --tmp;
        return tmp;
    }
    bool operator==(const Iterator& src) const
    {
        return m_ptr == src.m_ptr;
    }
    bool operator!=(const Iterator& src) const
    {
        return m_ptr != src.m_ptr;
    }
private:
    T* m_ptr;
};

template <typename T>
class Allocator
{
public:
    auto allocate(size_t size) -> T*
    {
        if (size == 0)
        {
            return nullptr;
        }
        return static_cast<T*>(::operator new(size * sizeof(T)));
    }
    void deallocate(T* p)
    {
        ::operator delete(p);
    }
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        new (p) U(std::forward<Args>(args)...);
    }
    void destroy(T* p)
    {
        p->~T();
    }
};

template <typename T, typename Alloc = Allocator<T>>
class VectorPlus
{
public:
    using iterator = Iterator<T>;
    VectorPlus(int capacity = 2)
        : m_size(0)
        , m_capacity(capacity)
    {
        m_data = m_allocator.allocate(m_capacity);
        std::cout << "默认构造\n";
    }
    ~VectorPlus()
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_allocator.destroy(&m_data[i]);
        }
        m_allocator.deallocate(m_data);
    }
    VectorPlus(std::initializer_list<T> list)
        : m_size(0)
        , m_capacity(list.size())
    {
        std::cout << "列表构造\n";
        m_data = m_allocator.allocate(m_capacity);
        for (const T& val : list)
        {
            m_allocator.construct(&m_data[m_size], val);
            m_size++;
        }
    }
    VectorPlus(const VectorPlus& src)
        : m_size(src.m_size)
        , m_capacity(src.m_capacity)
    {
        std::cout << "拷贝构造\n";
        m_data = m_allocator.allocate(m_capacity);
        for (int i = 0; i < m_size; ++i)
        {
            m_allocator.construct(&m_data[i], src.m_data[i]);
        }
    }
    VectorPlus(VectorPlus&& src) noexcept
        : m_data(src.m_data)
        , m_size(src.m_size)
        , m_capacity(src.m_capacity)
    {
        std::cout << "移动构造\n";
        src.m_data = nullptr;
        src.m_size = 0;
        src.m_capacity = 0;
    }
    VectorPlus& operator=(const VectorPlus& src)
    {
        if (this == &src)
        {
            return *this;
        }
        VectorPlus tmp(src);
        swap(tmp);
        return *this;
    }
    VectorPlus& operator=(VectorPlus&& src) noexcept
    {
        if (this == &src)
        {
            return *this;
        }
        clear();
        swap(src);
        return *this;
    }
    auto operator[](int index) const -> const T&
    {
        return m_data[index];
    }
    auto operator[](int index) -> T&
    {
        return m_data[index];
    }
    auto size() noexcept -> int
    {
        return m_size;
    }
    auto data() -> T*
    {
        return m_data;
    }
    auto capacity() noexcept -> int
    {
        return m_capacity;
    }
    auto empty() noexcept -> bool { return m_size == 0; }
    void resize(int size)
    {
        if (size < 0)
        {
            clear();
            return;
        }
        if (size > m_capacity)
        {
            reallocate(size);
        }
        if (size > m_size)
        {
            for (int i = m_size; i < size; ++i)
            {
                m_allocator.construct(&m_data[i]);
            }
        }
        else
        {
            for (int i = size; i < m_size; ++i)
            {
                m_allocator.destroy(&m_data[i]);
            }
        }
        m_size = size;
    }
    iterator begin()
    {
        return iterator(m_data);
    }
    iterator end()
    {
        return iterator(m_data + m_size);
    }
    void reserve(int size)
    {
        reallocate(size);
    }
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (m_size >= m_capacity)
        {
            reallocate(m_size == 0 ? 2 : m_capacity * 2);
        }
        m_allocator.construct(&m_data[m_size], std::forward<Args>(args)...);
        m_size++;
    }
    template <typename U>
    void push_back(U&& val)
    {
        if (m_size >= m_capacity)
        {
            reallocate(m_size == 0 ? 2 : m_capacity * 2);
        }
        m_allocator.construct(&m_data[m_size], std::forward<U>(val));
        m_size++;
    }

    void erase(int pos)
    {
        if (pos < 0 || pos >= m_size)
        {
            throw std::out_of_range("删除的位置不存在");
        }
        for (int i = pos; i < m_size - 1; ++i)
        {
            m_data[i] = std::move(m_data[i + 1]);
        }
        m_size--;
    }
    auto back() -> const T&
    {
        return m_data[m_size - 1];
    }
    auto front() -> const T&
    {
        return m_data[0];
    }

private:
    void reallocate(int size)
    {
        if (size <= 0)
        {
            clear();
            return;
        }
        T* tmpdata = m_allocator.allocate(size);
        int movesize = std::min(size, m_size);
        int index = 0;
        for (; index < movesize; ++index)
        {
            m_allocator.construct(&tmpdata[index], std::move(m_data[index]));
        }
        for (; index < m_size; ++index)
        {
            m_allocator.destroy(&m_data[index]);
        }
        m_allocator.deallocate(m_data);
        m_data = tmpdata;
        m_capacity = size;
        m_size = movesize;
    }
    void swap(VectorPlus& src) noexcept
    {
        std::swap(src.m_data, m_data);
        std::swap(src.m_size, m_size);
        std::swap(src.m_capacity, m_capacity);
    }
    void clear()
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_allocator.destroy(&m_data[i]);
        }
        m_allocator.deallocate(m_data);
        m_size = 0;
        m_data = nullptr;
        m_capacity = 0;
    }

    int m_size; // 当前元素个数
    int m_capacity; // 容量
    T* m_data;
    Alloc m_allocator;
};
