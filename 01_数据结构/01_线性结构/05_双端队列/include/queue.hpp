#include <iostream>
#include <vector>
/**
 * 简单复习，表达原理即可，不详细实现每个功能
 */

template <typename T>
class Deque
{
public:
    struct Node
    {
        Node(T data)
            : m_data(data)
            , m_pre(nullptr)
            , m_next(nullptr)
        {
        }
        T m_data;
        Node* m_pre;
        Node* m_next;
    };

private:
    Node* m_head { nullptr };
    Node* m_tail { nullptr };
    int m_size { 0 };

public:
    // 构造
    Deque()
    {
    }
    Deque(std::initializer_list<T> list)
    {
        for (auto val : list)
        {
            push_back(val);
        }
    }
    ~Deque()
    {
        while (!empty())
        {
            pop_front();
        }
    }
    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("队列为空");
        }
        return m_head->m_data;
    }
    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("队列为空");
        }
        return m_tail->m_data;
    }
    void push_front(const T& val)
    {
        Node* tmp = new Node(val);
        tmp->m_next = m_head;
        if (m_head)
        {
            m_head->m_pre = tmp;
        }
        else
        {
            m_tail = tmp;
        }
        m_head = tmp;
        m_size++;
    }
    void push_back(const T& val)
    {
        Node* tmp = new Node(val);
        tmp->m_pre = m_tail;
        if (m_tail)
        {
            m_tail->m_next = tmp;
        }
        else
        {
            m_head = tmp;
        }
        m_tail = tmp;
        m_size++;
    }
    void pop_front()
    {
        if (empty())
        {
            throw std::out_of_range("队列为空");
        }
        Node* toDelete = m_head;
        m_head = toDelete->m_next;
        if (m_head)
        {
            m_head->m_pre = nullptr;
        }
        else
        {
            m_tail = nullptr;
        }
        delete toDelete;
        m_size--;
    }
    void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("队列为空");
        }
        Node* toDelete = m_tail;
        m_tail = toDelete->m_pre;
        if (m_tail)
        {
            m_tail->m_next = nullptr;
        }
        else
        {
            m_head = nullptr;
        }
        delete toDelete;
        m_size--;
    }
    bool empty()
    {
        return m_size == 0;
    }
    int size() { return m_size; }
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Deque<U>& src);
};

template <typename U>
inline std::ostream& operator<<(std::ostream& out, const Deque<U>& src)
{
    out << "show Deque[";
    typename Deque<U>::Node* tmp = src.m_head;
    while (tmp)
    {
        out << tmp->m_data;
        tmp = tmp->m_next;
    }
    out << "]" << '\n';
    return out;
}
