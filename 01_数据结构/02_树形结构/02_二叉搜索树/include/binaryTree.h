#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <vector>
/**
 * 二叉搜索树阶段​
 * 完成：BST 的插入、查找、删除、区间查找、验证 BST、找第 K 小等。
 */
template <typename T, typename Comp = std::greater<T>>
class BinaryTree
{
public:
    struct Node
    {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node(T val)
            : m_data(val)
            , m_left(nullptr)
            , m_right(nullptr)
        {
        }
    };
    enum class showType
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder,
    };
private:
    Node* m_root { nullptr };
    int m_size { 0 };
    Comp m_comp;

public:
    // 构造函数和析构函数
    BinaryTree()
    {
    }
    ~BinaryTree()
    {
        if (m_root == nullptr)
        {
            return;
        }
        std::queue<Node*> st;
        st.push(m_root);
        while (!st.empty())
        {
            Node* node = st.front();
            st.pop();
            if (node->m_left)
            {
                st.push(node->m_left);
            }
            if (node->m_right)
            {
                st.push(node->m_right);
            }
            delete node;
        }
    }
    Node* getRoot()
    {
        return m_root;
    }
    void insert(const T& val)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(val);
            return;
        }
        Node* cur = m_root;
        Node* p = nullptr;
        while (cur != nullptr)
        {
            if (m_comp(cur->m_data, val))
            {
                p = cur;
                cur = cur->m_left;
            }
            else if (cur->m_data == val)
            {
                return;
            }
            else
            {
                p = cur;
                cur = cur->m_right;
            }
        }
        if (m_comp(p->m_data, val))
        {
            p->m_left = new Node(val);
        }
        else
        {
            p->m_right = new Node(val);
        }
        m_size++;
    }

    bool search(const T& val)
    {
        Node* p = m_root;
        while (p != nullptr)
        {
            if (p->m_data == val)
            {
                return true;
            }
            if (m_comp(p->m_data, val))
            {
                p = p->m_left;
            }
            else
            {
                p = p->m_right;
            }
        }
        return false;
    }
    void remove(const T& val)
    {
        Node* cur = m_root;
        Node* p = nullptr;
        while (cur != nullptr)
        {
            if(cur->m_data == val)
            {
                break;
            }
            p = cur;
            if (m_comp(cur->m_data, val))
            {
                cur = cur->m_left;
            }
            else
            {
                cur = cur->m_right;
            }
        }
        if(cur == nullptr)
        {
            return;
        }
        // 找前驱节点，把cur的值设置为前驱节点的值，p为前驱节点的父节点，cur为前驱节点，
        if (cur->m_left != nullptr && cur->m_right != nullptr)
        {
            Node* node = cur->m_left;
            Node* pre = cur;
            while (node->m_right != nullptr)
            {
                pre = node;
                node = node->m_right;
            }
            cur->m_data = node->m_data;
            cur = node;
            p = pre;
        }
        // 此时，只可能是只剩左边节点，或者只剩右边节点，或者是叶子节点
        // 拿到子节点之后，看p的左节点是cur还是有节点是cur
        Node* child = cur->m_left;
        if (child == nullptr)
        {
            child = cur->m_right;
        }
        if(p == nullptr)
        {
            m_root = child;
        }else if(p->m_left == cur)
        {
            p->m_left = child;
        }else
        {
            p->m_right = child;
        }
        delete cur;
        m_size--;
        
    }
    std::vector<T> preorder()
    {
        std::vector<T> res;
        if(m_root == nullptr)
        {
            return res;
        }
        std::stack<Node*> st;
        st.push(m_root);
        while(!st.empty())
        {
            Node* node = st.top();
            st.pop();
            res.push_back(node->m_data);
            if(node->m_right != nullptr)
            {
                st.push(node->m_right);
            }
            if(node->m_left != nullptr)
            {
                st.push(node->m_left);
            }
        }
        return res;
    }
    void order_show(showType type)
    {
        std::vector<T> res;
        switch (type)
        {
        case showType::PreOrder :
            std::cout << "先序遍历 ";
            res = preorder();
            break;
        case showType::InOrder:
            std::cout << "中序遍历 ";
            res = inorder();
            break;
        case showType::PostOrder:
            std::cout << "后序遍历 ";
            res = postorder();
            break;
        case showType::LevelOrder:
            std::cout << "层序遍历 ";
            res = levelOrder();
            break;
        default:
            break;
        }
        for(T& val: res)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::vector<T> inorder()
    {
        std::vector<T> res;
        if(m_root == nullptr)
        {
            return res;
        }
        std::stack<Node*> st;
        Node* p = m_root;
        
        while(!st.empty() || p != nullptr)
        {
            if(p != nullptr)
            {
                st.push(p);
                p = p->m_left;
            }else
            {
                Node* node = st.top();
                st.pop();
                res.push_back(node->m_data);
                p = node->m_right;
            }
        }
        return res;
    }
    std::vector<T> postorder()
    {
        // 标记法
        std::vector<T> res;
        if(m_root == nullptr)
        {
            return res;
        }
        std::stack<Node*> st;
        Node* tlast = nullptr;
        Node* p = m_root;
        while(!st.empty() || p != nullptr)
        {
            if(p != nullptr)
            {
                st.push(p);
                p = p->m_left;
            }else
            {
                Node* node = st.top();
                if(node->m_right != nullptr && node->m_right != tlast)
                {
                    p = node->m_right;
                }else
                {
                    res.push_back(node->m_data);
                    st.pop();
                    tlast = node;
                }
            }
        }
        return res;
    }
    void postorder_t()
    {
        // 双栈法
        std::cout << "后序遍历 ";
        if (m_root == nullptr)
        {
            return;
        }
        std::stack<Node*> st;
        std::stack<Node*> res;
        st.push(m_root);
        while (!st.empty())
        {
            Node* node = st.top();
            st.pop();
            res.push(node);
            if (node->m_left != nullptr)
            {
                st.push(node->m_left);
            }
            if (node->m_right != nullptr)
            {
                st.push(node->m_right);
            }
        }
        while (!res.empty())
        {
            Node* node = res.top();
            res.pop();
            std::cout << node->m_data << " ";
        }
        std::cout << std::endl;
    }
    std::vector<T> levelOrder()
    {
        std::vector<T> res;
        if(m_root == nullptr)
        {
            return res;
        }
        std::queue<Node*> st;
        st.push(m_root);
        while (!st.empty())
        {
            Node* cur = st.front();
            st.pop();
            if(cur->m_left)
            {
                st.push(cur->m_left);
            }
            if(cur->m_right)
            {
                st.push(cur->m_right);
            }
            res.push_back(cur->m_data);
        }
        return res;
    }
    // 获取属性
    bool isEmpty()
    {
        return m_size == 0;
    }
    int getSize()
    {
        return m_size;
    }
    int getHeight()
    {
        if (m_root == nullptr)
        {
            return 0;
        }
        std::queue<Node*> st;
        st.push(m_root);
        int res = 0;
        while (!st.empty())
        {
            int n = st.size();
            for (int i = 0; i < n; ++i)
            {
                Node* node = st.front();
                st.pop();
                if (node->m_left)
                {
                    st.push(node->m_left);
                }
                if (node->m_right)
                {
                    st.push(node->m_right);
                }
            }
            res++;
        }
        return res;
    }
    int getLeafCount()
    {
        if (m_root == nullptr)
        {
            return 0;
        }
        std::queue<Node*> q;
        q.push(m_root);
        int res = 0;
        while (!q.empty())
        {
            Node* node = q.front();
            q.pop();
            if (node->m_left != nullptr)
            {
                q.push(node->m_left);
            }
            if (node->m_right != nullptr)
            {
                q.push(node->m_right);
            }
            if (node->m_left == nullptr && node->m_right == nullptr)
            {
                res++;
            }
        }
        return res;
    }
    
    // 求满足区间的元素值[i,j]实现
    void findValues(std::vector<T>& vec, const T& i, const T& j)
    {
        findValues(m_root, vec, i, j);
    }

private:
    void findValues(Node* node, std::vector<T>& vec, const T& i, const T& j)
    {
        if (node == nullptr)
        {
            return;
        }
        if (m_comp(node->m_data, i))
        {
            findValues(node->m_left, vec, i, j);
        }
        if (!m_comp(i, node->m_data) && !m_comp(node->m_data, j))
        {
            vec.push_back(node->m_data);
        }
        if (m_comp(j, node->m_data))
        {
            findValues(node->m_right, vec, i, j);
        }
    }
    
};
