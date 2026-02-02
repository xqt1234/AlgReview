#include <iostream>
#include <vector>
/**
 * 简单复习，表达原理即可，不详细实现每个功能
 */

template <typename T>
class Queue
{
private:
    T* m_data{nullptr};
    int m_front{0};
    int m_rear{0};
    int m_capacity{0};
public:
    // 构造
    Queue(int size = 4)
        :m_capacity(size + 1)
        ,m_front(0)
        ,m_rear(0)
    {
        m_data = new T[m_capacity];
    }
    ~Queue()
    {
        delete[] m_data;
    }
    void enqueue(const T& val)
    {
        if(isFull())
        {
            expand();
        }
        m_data[m_rear] = val;
        m_rear = (m_rear + 1) % m_capacity;
    }
    void dequeue()
    {
        if(empty())
        {
            throw std::out_of_range("栈为空");
        }
        m_front = (m_front + 1)% m_capacity;
    }
    T& front() const
    {
        if(empty())
        {
            throw std::out_of_range("栈为空");
        }
        return m_data[m_front];
    }
    T& back() const
    {
        if(empty())
        {
            throw std::out_of_range("栈为空");
        }
        return m_data[(m_rear - 1+ m_capacity)% m_capacity];
    }
    bool isFull() const
    {
        return (m_rear + 1)% m_capacity == m_front;
    }
    // 获取属性
    int size() const
    {
        return (m_rear - m_front + m_capacity) % m_capacity;
    }
    bool empty() const
    {
        return m_rear == m_front;
    }
    
    int capacity() const
    {
        return m_capacity - 1;
    }
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out,const Queue<U>& src);
    
private:
    void expand()
    {
        int newsize = std::max(2,m_capacity * 2);
        T* tmp = new T[newsize];
        int i = 0;
        int j = m_front;
        for(;j != m_rear;i++,j = (j + 1)%m_capacity)
        {
            tmp[i] = m_data[j];
        }
        delete[] m_data;
        m_capacity = newsize;
        m_rear = i;
        m_front = 0;
        m_data = tmp;
    }
};

template <typename U>
inline std::ostream& operator<<(std::ostream& out, const Queue<U>& src)
{
    int i = 0;
    int j = src.m_front;
    out << "show Queue[";
    for(;j != src.m_rear;i++,j = (j + 1)%src.m_capacity)
    {
        out << src.m_data[i];
    }
    out << "]" << '\n';
    return out;
}
