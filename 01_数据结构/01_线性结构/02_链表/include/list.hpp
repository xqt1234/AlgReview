#include <iostream>

/**
 * 简单复习，表达原理即可，不详细实现每个功能
 */
template <typename T>
class List
{
public:
    struct Node
    {
        T m_data;
        Node* m_next;
        Node* m_pre;
        Node(const T& val)
            : m_data(val)
            , m_next(nullptr)
            , m_pre(nullptr)
        {
        }
    };

private:
    Node* m_head { nullptr };
    Node* m_tail { nullptr };
    int m_size { 0 };

public:
    // 构造
    List() { }
    List(std::initializer_list<T> list)
    {
        for (const T& val : list)
        {
            push_back(val);
        }
        m_size = list.size();
    }
    List(const List& src)
    {
        Node* tmphead = src.m_head;
        while (tmphead != nullptr)
        {
            push_back(tmphead->m_data);
            tmphead = tmphead->m_next;
        }
        m_size = src.m_size;
    }
    List(List&& src)
    {
        m_head = src.m_head;
        m_size = src.m_size;
        m_tail = src.m_tail;
        src.m_head = nullptr;
        src.m_size = 0;
        src.m_tail = nullptr;
    }
    List& operator=(const List& src)
    {
        if (this == &src)
        {
            return *this;
        }
        while (m_head != nullptr)
        {
            Node* tmp = m_head->m_next;
            delete m_head;
            m_head = tmp;
        }
        m_tail = m_head;
        Node* tmpHead = src.m_head;
        while (tmpHead != nullptr)
        {
            push_back(tmpHead->m_data);
            tmpHead = tmpHead->m_next;
        }
        m_size = src.m_size;
        return *this;
    }
    List& operator=(List&& src)
    {
        while (m_head != nullptr)
        {
            Node* tmp = m_head->m_next;
            delete m_head;
            m_head = tmp;
        }
        m_tail = m_head;
        m_head = src.m_head;
        m_size = src.m_size;
        m_tail = src.m_tail;
        src.m_head = nullptr;
        src.m_size = 0;
        src.m_tail = nullptr;
        return *this;
    }
    // 获取属性
    int size() { return m_size; }
    bool empty() { return m_head == nullptr; }
    // 添加元素
    void push_back(const T& val)
    {
        Node* tmp = new Node(val);
        if (m_head)
        {
            m_tail->m_next = tmp;
            tmp->m_pre = m_tail;
            m_tail = tmp;
        }
        else
        {
            m_head = tmp;
            m_tail = tmp;
        }
        m_size++;
    }
    void push_front(const T& val)
    {
        Node* tmp = new Node(val);
        tmp->m_next = m_head;
        m_head->m_pre = tmp;
        m_head = tmp;
        m_size++;
    }
    void insert(int index, const T& val)
    {
        if (index < 0 || index > m_size)
        {
            throw std::out_of_range("超出范围");
        }
        Node* newNode = new Node(val);
        if (empty())
        {
            m_head = m_tail = newNode;
        }
        else if (index == 0)
        {
            newNode->m_next = m_head;
            m_head->m_pre = newNode;
            m_head = newNode;
        }
        else if (index == m_size)
        {
            m_tail->m_next = newNode;
            newNode->m_pre = m_tail;
            m_tail = newNode;
        }
        else
        {
            Node* current = m_head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->m_next;
            }
            newNode->m_next = current->m_next;
            current->m_next->m_pre = newNode;
            current->m_next = newNode;
            newNode->m_pre = current;
        }
        m_size++;
    }
    // 移除元素
    void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("超出范围");
        }
        Node* tmp = m_tail;
        m_tail = m_tail->m_pre;
        if (m_tail)
        {
            m_tail->m_next = nullptr;
        }
        else
        {
            m_head = nullptr;
        }
        delete tmp;
        m_size--;
    }
    void pop_front()
    {
        if (empty())
        {
            throw std::out_of_range("超出范围");
        }
        Node* toDel = m_head;
        m_head = m_head->m_next;
        if (m_head)
        {
            m_head->m_pre = nullptr;
        }
        else
        {
            m_tail = nullptr;
        }
        delete toDel;
        m_size--;
    }
    void erase(int pos)
    {
        if (pos < 0 || pos >= m_size)
        {
            throw std::out_of_range("超出范围");
        }
        if (pos == 0)
        {
            pop_front();
            return;
        }
        else if (pos == (m_size - 1))
        {
            pop_back();
            return;
        }
        Node* toDel = m_head;
        for (int i = 0; i < pos; ++i)
        {
            toDel = toDel->m_next;
        }
        toDel->m_pre->m_next = toDel->m_next;
        toDel->m_next->m_pre = toDel->m_pre;
        delete toDel;
        m_size--;
    }
    void removeVal(const T& val)
    {
        Node* current = m_head;
        while(current)
        {
            Node* nextNode = current->m_next;
            if(current->m_data == val)
            {
                if(current->m_pre)
                {
                    current->m_pre->m_next = nextNode;
                }else
                {
                    m_head = current->m_next;
                }
                if(current->m_next)
                {
                    current->m_next->m_pre = current->m_pre;
                }else
                {
                    m_tail = current->m_pre;
                }
                delete current;
                m_size--;
            }
            current = nextNode;
        }
    }
    // 访问元素
    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("超出范围");
        }
        return m_head->m_data;
    }
    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("超出范围");
        }
        return m_tail->m_data;
    }
    T& at(int index)
    {
        if (index < 0 || index >= m_size)
        {
            throw std::out_of_range("超出范围");
        }
        Node* cur = m_head;
        for(int i = 0;i < index;++i)
        {
            cur = cur->m_next;
        }
        return cur->m_data;
    }

    // 其他功能
    void clear()
    {
        Node* cur = m_head;
        while(cur)
        {
            Node* next = cur->m_next;
            delete cur;
            cur = next;
        }
        m_size = 0;
        m_tail = m_head = nullptr;
    }
    void reverse()
    {
        if(m_head == nullptr || m_head == m_tail)
        {
            return;
        }
        Node* cur = m_head;
        Node* temp = nullptr;
        while(cur != nullptr)
        {
            temp = cur->m_pre;
            cur->m_pre = cur->m_next;
            cur->m_next = temp;
            cur = cur->m_pre;
        }
        temp = m_head;
        m_head = m_tail;
        m_tail = temp;
    }
    bool contain(const T& val) const
    {
        Node* cur = m_head;
        while(cur)
        {
            if(cur->m_data == val)
            {
                return true;
            }
            cur = cur->m_next;
        }
        return false;
    }
    int find(const T& val) const
    {
        int i = 0;
        Node* tmp = m_head;
        while(tmp)
        {
            if(tmp->m_data == val)
            {
                return i;
            }
            ++i;
            tmp = tmp->m_next;
        }
        return -1;
    }
    ~List()
    {
        Node* cur = m_head;
        while(cur)
        {
            Node* tmp = cur->m_next;
            delete cur;
            cur = tmp;
        }
        m_head = m_tail = nullptr;
        m_size = 0;
    }
};
