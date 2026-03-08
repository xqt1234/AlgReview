#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <vector>
/**
四种旋转（左旋、右旋、左右旋、右左旋）、插入自平衡、删除自平衡、验证AVL。
 */
template <typename T, typename Comp = std::greater<T>>
class AVLTree
{
public:
    struct Node
    {
        T m_data;
        Node* m_left;
        Node* m_right;
        int m_height;
        Node(T val)
            : m_data(val)
            , m_left(nullptr)
            , m_right(nullptr)
            , m_height(1)
        {
        }
    };
private:
    Node* m_root { nullptr };
    int m_size { 0 };
    Comp m_comp;

public:
    // 构造函数和析构函数
    AVLTree()
    {
    }
    ~AVLTree()
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
        m_root = insert(m_root,val);
    }
    void remove(const T& val)
    {
        m_root = remove(m_root,val);
    }
    Node* remove(Node* node,const T& val)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        if(node->m_data == val)
        {
            // 如果节点有左右子树
            if(node->m_left != nullptr && node->m_right != nullptr)
            {
                // 如果左子树比右子树高，就删除前驱，否则，删除后继
                if(height(node->m_left) > height(node->m_right))
                {
                    Node* pre = node->m_left;
                    while (pre->m_right)
                    {
                        pre = pre->m_right;
                    }
                    node->m_data = pre->m_data;
                    // 替换前驱节点的值之后，从前驱的这侧删除前驱节点值。
                    node->m_left = remove(node->m_left,pre->m_data);
                }else
                {
                    Node* post = node->m_right;
                    while (post->m_left)
                    {
                        post = post->m_left;
                    }
                    node->m_data = post->m_data;
                    node->m_right = remove(node->m_right,post->m_data);
                }
            }else
            {
                if(node->m_left != nullptr)
                {
                    Node* left = node->m_left;
                    delete node;
                    return left;
                }else if(node->m_right != nullptr)
                {
                    Node* right = node->m_right;
                    delete node;
                    return right;
                }else
                {
                    delete node;
                    return nullptr;
                }
            }
        }else if(m_comp(node->m_data,val))
        {
            node->m_left = remove(node->m_left,val);
            if(height(node->m_right) - height(node->m_left) > 1)
            {
                if(height(node->m_right->m_left) > height(node->m_right->m_right))
                {
                    node = rightBalance(node);
                }else
                {
                    node = leftRotate(node);
                }
            }
        }else
        {
            node->m_right = remove(node->m_right,val);
            if(height(node->m_left) - height(node->m_right) > 1)
            {
                if(height(node->m_left->m_left) > height(node->m_left->m_right))
                {
                    node = rightRotate(node);
                }else
                {
                    node = leftBalance(node);
                }
            }
        }
        node->m_height = std::max(height(node->m_left),height(node->m_right)) + 1;
        return node;
    }
    Node* insert(Node* node,const T& val)
    {
        if(node == nullptr)
        {
            return new Node(val);
        }
        if(node->m_data == val)
        {
        }
        else if(m_comp(node->m_data,val))
        {
            node->m_left = insert(node->m_left,val);
            if(height(node->m_left) - height(node->m_right) > 1)
            {
                if(height(node->m_left->m_left) > height(node->m_left->m_right))
                {
                    node = rightRotate(node);
                }else
                {
                    node = leftBalance(node);
                }
            }
        }else
        {
            node->m_right = insert(node->m_right,val);
            if(height(node->m_right) - height(node->m_left) > 1)
            {
                if(height(node->m_right->m_right) > height(node->m_right->m_left))
                {
                    node = leftRotate(node);
                }else
                {
                    node = rightBalance(node);
                }
            }
        }
        node->m_height = std::max(height(node->m_left),height(node->m_right)) + 1;
        return node;
    }
    // 左孩子太高了，右旋转操作，以node为轴旋转，返回根节点
    Node* rightRotate(Node* node)
    {
        Node* child = node->m_left;
        node->m_left = child->m_right;
        child->m_right = node;
        node->m_height = std::max(height(node->m_left),height(node->m_right)) + 1;
        child->m_height = std::max(height(child->m_left),height(child->m_right)) + 1;
        return child;
    }
    // 右孩子太高，左转操作
    Node* leftRotate(Node* node)
    {
        Node* child = node->m_right;
        node->m_right = child->m_left;
        child->m_left = node;
        node->m_height = std::max(height(node->m_right),height(node->m_left)) + 1;
        child->m_height = std::max(height(child->m_left),height(child->m_right))+1;
        return child;
    }
    // 左孩子的右子树太高了，
    Node* leftBalance(Node* node)
    {
        node->m_left = leftRotate(node->m_left);
        return rightRotate(node);
    }
    // 右孩子的左子树太高了
    Node* rightBalance(Node* node)
    {
        node->m_right = rightRotate(node->m_right);
        return leftRotate(node);
    }
    int height(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        return node->m_height;
    }
};
