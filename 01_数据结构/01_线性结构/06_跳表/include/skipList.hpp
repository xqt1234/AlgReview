#include <iostream>
#include <random>
#include <vector>
/**
 * 简单复习，表达原理即可，不详细实现每个功能
 */

template <typename T>
class SkipList
{
private:
    struct Node
    {
        T m_data;
        std::vector<Node*> m_forward;
        Node(T val, int level)
            : m_data(val)
            , m_forward(level, nullptr)
        {
        }
    };
    Node* m_head;
    int m_maxLevel;
    int m_size{0};
    int m_currentLevel{1};
    float m_probability;
    int randomLevel() {
        int lvl = 1;
        while (rand() % 100 < m_probability * 100 && lvl < m_maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int maxlevel = 16, float p = 0.5)
        : m_maxLevel(maxlevel)
        , m_currentLevel(1)
        , m_size(0)
        , m_probability(p)
    {
        m_head = new Node(T(),maxlevel);
    }
    ~SkipList()
    {
        Node* cur = m_head;
        while(cur)
        {
            Node* next = cur->m_forward[0];
            delete cur;
            cur = next;
        }
    }
    
    bool insert(const T& val)
    {
        std::vector<Node*> tmp(m_maxLevel,nullptr);
        Node* cur = m_head;
        // 外层向下找。
        for(int i = m_currentLevel - 1;i >= 0;--i)
        {
            while(cur->m_forward[i] && cur->m_forward[i]->m_data < val)
            {
                // 在本层往右找。
                cur = cur->m_forward[i];
            }
            tmp[i] = cur;
        }
        cur = cur->m_forward[0];
        if(cur == nullptr || cur->m_data != val)
        {
            int newlevel = randomLevel();
            if(newlevel > m_currentLevel)
            {
                for(int i = m_currentLevel;i < newlevel;++i)
                {
                    tmp[i] = m_head;
                }
                m_currentLevel = newlevel;
            }
            cur = new Node(val,newlevel);
            for(int i = 0;i < newlevel;++i)
            {
                cur->m_forward[i] = tmp[i]->m_forward[i];
                tmp[i]->m_forward[i] = cur;
            }
            m_size++;
            return true;
        }
        return false;
    }
    bool search(const T& val)
    {
        Node* current = m_head;
        for(int i = m_currentLevel;i >= 0;--i)
        {
            while(current->m_forward[i] && current->m_forward[i]->m_data < val)
            {
                current = current->m_forward[i];
            }
        }
        current = current->m_forward[0];
        return current && current->m_data == val;
    }
    
    void deleteVal(const T& val)
    {
        std::vector<Node*> tmp(m_maxLevel,nullptr);
        Node* current = m_head;
        for(int i = m_currentLevel - 1;i >= 0; --i)
        {
            while(current->m_forward[i] && current->m_forward[i]->m_data < val)
            {
                current = current->m_forward[i];
            }
            tmp[i] = current;
        }
        current = current->m_forward[0];
        if(current && current->m_data == val)
        {
            for(int i = 0;i < m_currentLevel;++i)
            {
                if(tmp[i]->m_forward[i] != current)
                {
                    break;
                }
                tmp[i]->m_forward[i] = current->m_forward[i];
            }
            delete current;
            while(m_currentLevel > 1 && m_head->m_forward[m_currentLevel - 1] == nullptr)
            {
                -- m_currentLevel;
            }
            m_size--;
        }
    }
    void show()
    {
        for(int i = m_currentLevel - 1;i >= 0;--i)
        {
            Node* current = m_head->m_forward[i];
            while(current != nullptr)
            {
                std::cout << current->m_data << " ";
                current = current->m_forward[i];
            }
            std::cout << std::endl;
        }
    }
    int getSize(){return m_size;}
    bool isEmpty(){return m_size == 0;}
    void clear()
    {
        Node* cur =  m_head->m_forward[0];
        while(cur != nullptr)
        {
            Node* next = cur->m_forward[0];
            delete cur;
            cur = next;
        }
        for(int i = 0;i < m_maxLevel;++i)
        {
            m_head->m_forward[i] = nullptr;
        }
        m_currentLevel = 1;
        m_size = 0;
    }

};


// int main()
// {
//     srand(time(nullptr));
//     SkipList<int> tmplist;
//     tmplist.insert(42);
//     std::cout << tmplist.getSize() << std::endl;
//     tmplist.show();
//     std::cout << tmplist.search(42) << std::endl;
//     std::cout << "hello world" << std::endl;
//     return 0;
// }