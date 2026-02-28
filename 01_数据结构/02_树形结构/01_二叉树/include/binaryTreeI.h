#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <functional>
#include <stack>
#include <queue>
/**
 * 简单复习，表达原理即可，不详细实现每个功能,迭代版本
 * 一、普通二叉树（Binary Tree）应该实现的功能
普通二叉树的核心是结构 + 遍历，不要求节点值有序，所以功能围绕“树形”和“访问顺序”展开。
1. 结构相关
节点定义：Node包含 data、left、right。
构造与析构：
构造函数初始化空树。
析构函数用层序或递归释放所有节点（防止内存泄漏）。
2. 插入方式（普通二叉树特有）
层序插入（自动找第一个空位）：
从左到右、从上到下填满树，构造完全二叉树或近似完全二叉树。
（可选）按位置插入：手动指定父节点和左右方向，但要检查位置是否为空。
3. 遍历（核心考点）
递归遍历：
前序（根 → 左 → 右）
中序（左 → 根 → 右）
后序（左 → 右 → 根）
迭代遍历：
前序（栈）
中序（栈）
后序（双栈法或标记法）
层序遍历（队列）
4. 属性计算
判空 isEmpty()
节点数 getSize()
高度 getHeight()（递归或层序）
叶子节点数 getLeafCount()
（可选）第 k 层节点数
5. 其他辅助
根据前序+中序 / 中序+后序 重建树（经典面试题）
判断两棵树是否相同、是否镜像
判断是否为完全二叉树
 */
//grep -n "^\s*\(void\|bool\|int\|T\|Node\*\)\s\+\w\+.*)" your_file.cpp | grep -v "^\s*//"

template <typename T,typename Comp = std::greater<T>>
class BinaryTreeI
{
public:
    struct Node
    {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node(T val):m_data(val),m_left(nullptr),m_right(nullptr)
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
    Node* m_root{nullptr};
    int m_size{0};
public:
    // 构造函数和析构函数
    BinaryTreeI()
    {
    }
    ~BinaryTreeI()
    {
        if(m_root == nullptr)
        {
            return;
        }
        std::queue<Node*> st;
        st.push(m_root);
        while(!st.empty())
        {
            Node* node = st.front();
            st.pop();
            if(node->m_left)
            {
                st.push(node->m_left);
            }
            if(node->m_right)
            {
                st.push(node->m_right);
            }
            delete node;
        }
    }
    Node* getRoot() const { return m_root; }
    void insert(const T& val)
    {
        if(m_root == nullptr)
        {
            m_root = new Node(val);
            m_size++;
            return;
        }
        std::queue<Node*> st;
        st.push(m_root);
        while(!st.empty())
        {
            Node* node = st.front();
            st.pop();
            if(node->m_left == nullptr)
            {
                node->m_left = new Node(val);
                m_size++;
                return;
            }else
            {
                st.push(node->m_left);
            }
            if(node->m_right == nullptr)
            {
                node->m_right = new Node(val);
                m_size++;
                return;
            }else
            {
                st.push(node->m_right);
            }
        }
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
        if(m_root == nullptr)
        {
            return;
        }
        std::stack<Node*> st;
        std::stack<Node*> res;
        st.push(m_root);
        while(!st.empty())
        {
            Node* node = st.top();
            st.pop();
            res.push(node);
            if(node->m_left != nullptr)
            {
                st.push(node->m_left);
            }
            if(node->m_right != nullptr)
            {
                st.push(node->m_right);
            }
        }
        while(!res.empty())
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
        return m_size== 0;
    }
    int getSize()
    {
        return m_size;
    }
    int getHeight()
    {
        if(m_root == nullptr)
        {
            return 0;
        }
        std::queue<Node*> st;
        st.push(m_root);
        int res = 0;
        while(!st.empty())
        {
            int n = st.size();
            for(int i = 0;i < n;++i)
            {
                Node* node = st.front();
                st.pop();
                if(node->m_left)
                {
                    st.push(node->m_left);
                }
                if(node->m_right)
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
        if(m_root == nullptr)
        {
            return 0;
        }
        std::queue<Node*> q;
        q.push(m_root);
        int res = 0;
        while(!q.empty())
        {
            Node* node = q.front();
            q.pop();
            if(node->m_left != nullptr)
            {
                q.push(node->m_left);
            }
            if(node->m_right != nullptr)
            {
                q.push(node->m_right);
            }
            if(node->m_left == nullptr && node->m_right == nullptr)
            {
                res ++;
            }
        }
        return res;
    }
    void preorder_r()
    {
        std::cout << "先序遍历 ";
        preorder_r(m_root);
        std::cout << std::endl;
    }
    void inorder_r()
    {
        std::cout << "中序遍历 ";
        inorder_r(m_root);
        std::cout << std::endl;
    }
    void postorder_r()
    {
        std::cout << "后序遍历 ";
        postorder_r(m_root);
        std::cout << std::endl;
    }
    
private:
    void inorder_r(Node* node)
    {
        if(node != nullptr)
        {
            inorder_r(node->m_left);
            std::cout << node->m_data << " ";
            inorder_r(node->m_right);
        }
    }
    void preorder_r(Node* node)
    {
        if(node != nullptr)
        {
            std::cout << node->m_data << " ";
            preorder_r(node->m_left);
            preorder_r(node->m_right);
        }
    }
    void postorder_r(Node* node)
    {
        if(node != nullptr)
        {
            postorder_r(node->m_left);
            postorder_r(node->m_right);
            std::cout << node->m_data << " ";
        }
    }
};
// // ------------二叉树经典题目
// int main()
// {
//     BinaryTreeI<int> mytree;
//     mytree.insert(20);
//     mytree.insert(10);
//     mytree.insert(25);
//     mytree.insert(6);
//     mytree.insert(15);
//     mytree.insert(22);
//     mytree.insert(28);
//     mytree.preorder();
//     mytree.preorder_r();
//     mytree.inorder();
//     mytree.inorder_r();
//     mytree.postorder();
//     mytree.postorder_t();
//     mytree.postorder_r();
//     mytree.levelOrder();
//     std::cout << std::endl;
//     return 0;
// }
