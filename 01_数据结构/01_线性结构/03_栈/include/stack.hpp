#include <iostream>
#include <vector>
/**
 * 简单复习，表达原理即可，不详细实现每个功能
 */

template <typename T>
class Stack
{
private:
    T* m_data{nullptr};
    int m_top{-1};
    int m_capacity{0};

public:
    // 构造
    Stack(int capacity = 2)
        : m_top(-1)
    {
        m_capacity = std::max(2,capacity);
        m_data = new T[m_capacity];
    }
    Stack(std::initializer_list<T> list)
    {
        for(const T& val: list)
        {
            push(val);
        }
    }
    Stack(const Stack& src)
    {
        m_capacity = src.m_capacity;
        m_data = new T[m_capacity];
        for(int i = 0;i <= src.m_top;++i)
        {
            m_data[i] = src.m_data[i];
        }
        m_top = src.m_top;
    }
    Stack(Stack&& src) noexcept
    {
        m_capacity = src.m_capacity;
        m_data = src.m_data;
        m_top = src.m_top;
        src.m_capacity = 0;
        src.m_data = nullptr;
        src.m_top = -1;
    }
    Stack& operator=(const Stack& src)
    {
        if(&src == this)
        {
            return *this;
        }
        delete[] m_data;
        m_top = src.m_top;
        m_capacity = src.m_capacity;
        m_data = new T[m_capacity];
        for(int i = 0;i <= src.m_top;++i)
        {
            m_data[i] = src.m_data[i];
        }
        return *this;
    }
    Stack& operator=(Stack&& src)
    {
        if(&src == this)
        {
            return *this;
        }
        delete[] m_data;
        m_capacity = src.m_capacity;
        m_data = src.m_data;
        m_top = src.m_top;
        src.m_capacity = 0;
        src.m_data = nullptr;
        src.m_top = -1;
        return *this;
    }
    // 获取属性
    int size() const
    {
        return m_top +1;
    }
    bool empty() const
    {
        return m_top == -1;
    }
    bool isFull() const
    {
        return (m_top +1) == m_capacity;
    }
    int capacity() const
    {
        return m_capacity;
    }
    // 操作
    void push(const T& val)
    {
        if(isFull())
        {
            expand();
        }
        m_data[++m_top] = val;
    }
    void push(T&& val)
    {
        if(isFull())
        {
            expand();
        }
        m_data[++m_top] = std::move(val);
    }
    void pop()
    {
        if(empty())
        {
            throw std::out_of_range("栈为空");
        }
        m_top--;
    }
    T& top()
    {
        if(empty())
        {
            throw std::out_of_range("栈为空");
        }
        return m_data[m_top];
    }
    void clear()
    {
        delete[] m_data;
        m_capacity = 0;
        m_data = nullptr;
        m_top = -1;

    }
    void swap(Stack& src)
    {
        std::swap(m_data,src.m_data);
        std::swap(m_top,src.m_top);
        std::swap(m_capacity,src.m_capacity);
    }
    void reverse()
    {
        Stack tmp1(size()),tmp2(size());
        while(!empty())
        {
            tmp1.push(top());
            pop();
        }
        // 可直接使用swap
        while(!tmp1.empty())
        {
            tmp2.push(tmp1.top());
            tmp1.pop();
        }
        while(!tmp2.empty())
        {
            push(tmp2.top());
            tmp2.pop();
        }
    }

    bool operator==(const Stack& src) const
    {
        if(src.m_top != m_top)
        {
            return false;
        }
        for(int i = 0;i <= m_top;++i)
        {
            if(m_data[i] != src.m_data[i])
            {
                return false;
            }
        }
        return true;
    }
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out,const Stack<U>& src);

    ~Stack()
    {
        delete[] m_data;
    }
private:
    void expand()
    {
        int newsize = std::max(2,m_capacity * 2);
        T* tmp = new T[newsize];
        for(int i = 0;i <= m_top;++i)
        {
            tmp[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = tmp;
        m_capacity = newsize;
    }
};

template <typename U>
inline std::ostream& operator<<(std::ostream& out, const Stack<U>& src)
{
    out << "Stack[";
    for(int i = 0;i <= src.m_top;++i)
    {
        out << src.m_data[i];
        if( i < src.m_top)
        {
            out << ", ";
        }
    }
    out << " ]";
    return out;
}
