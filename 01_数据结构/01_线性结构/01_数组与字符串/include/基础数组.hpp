#include <iostream>
#include <vector>
template<typename T>
class Vector
{
public:
    Vector(int capacity = 2)
        :m_size(0),m_capacity(capacity)
    {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        std::cout << "默认构造" << std::endl;
    }
    ~Vector()
    {
        for(int i = 0;i < m_size;++i)
        {
            m_data[i].~T();
        }
        ::operator delete(m_data);
    }
    Vector(std::initializer_list<T> list)
        :m_size(0)
        ,m_capacity(list.size())
    {
        std::cout << "列表构造" << std::endl;
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        for(const T& val : list)
        {
            new (&m_data[m_size]) T(val);
            m_size++;
        }
    }
    Vector(const Vector& src)
        :m_size(src.m_size),m_capacity(src.m_capacity)
    {
        std::cout << "拷贝构造" << std::endl;
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        for(int i = 0;i < m_size;++i)
        {
            new (&m_data[i]) T(src.m_data[i]);
        }
    }
    Vector(Vector&& src)
        :m_data(src.m_data),m_size(src.m_size),m_capacity(src.m_capacity)
    {
        std::cout << "移动构造" << std::endl;
        src.m_data = nullptr;
        src.m_size = 0;
        src.m_capacity = 0;
    }
    const T& operator[](int i) const
    {
        return m_data[i];
    }
    T& operator[](int i)
    {
        return m_data[i];
    }
    int size()
    {
        return m_size;
    }
    T* data()
    {
        return m_data;
    }
    int capacity()
    {
        return m_capacity;
    }
    bool empty(){ return m_size == 0;}
    
    void resize(int size)
    {
        if(size < 0)
        {
            clear();
            return;
        }
        while(size > m_capacity)
        {
            reallocate(m_capacity * 2);
        }
        if(size > m_size)
        {
            for(int i = m_size;i < size;++i)
            {
                new (&m_data[i]) T();
            }
        }else
        {
            for(int i = size;i < m_size;++i)
            {
                m_data[i].~T();
            }
        }
        m_size = size;
    }
    void reserve(int size)
    {
        reallocate(size);
    }
    void push_back(const T& val)
    {
        if(m_size >= m_capacity)
        {
            reallocate(m_size == 0 ? 2 : m_capacity * 2);
        }
        new (&m_data[m_size]) T(val);
        m_size++;
    }
    void erase(int pos)
    {
        if(pos < 0 || pos >= m_size)
        {
            throw std::out_of_range("删除的位置不存在");
        }
        for(int i = pos;i < m_size - 1;++i)
        {
            m_data[i] = std::move(m_data[i + 1]);
        }
        m_size--;
        m_data[m_size].~T();
    }
    const T& back()
    {
        return m_data[m_size-1];
    }
    const T& front()
    {
        return m_data[0];
    }
private:
    void reallocate(int size)
    {
        if(size <= 0)
        {
            clear();
            return;
        }
        T* tmpdata = static_cast<T*>(::operator new(size * sizeof(T)));
        int movesize = std::min(size,m_size);
        int i = 0;
        for(;i < movesize;++i)
        {
            new (&tmpdata[i]) T(std::move(m_data[i]));
        }
        for(;i < m_size;++i)
        {
            m_data[i].~T();
        }
        ::operator delete(m_data);
        m_data = tmpdata;
        m_capacity = size;
    }
    void swap(Vector& src)
    {
        std::swap(src.m_data,m_data);
        std::swap(src.m_size,m_size);
        std::swap(src.m_capacity,m_capacity);
    }
    void clear()
    {
        for(int i = 0;i < m_size;++i)
        {
            m_data[i].~T();
        }
        ::operator delete(m_data);
        m_size = 0;
        m_data = nullptr;
        m_capacity = 0;
    }
private:
    int m_size; // 当前元素个数
    int m_capacity; // 容量
    T* m_data;
};
