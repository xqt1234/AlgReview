#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <vector>
/**
颜色规则 + 五条性质 + 插入/删除自平衡 + 旋转
 */
template <typename T, typename Comp = std::greater<T>>
class RBTree
{
public:
    enum class Color
    {
        Red,
        Black,
    };
    struct Node
    {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node* m_parent;
        Color m_color;
        Node(T val = T(),Node* parent = nullptr,Color color = Color::Red)
            : m_data(val)
            , m_left(nullptr)
            , m_right(nullptr)
            , m_parent(parent)
            , m_color(color)
        {
        }
    };
private:
    Node* m_root { nullptr };
    int m_size { 0 };
    Comp m_comp;

public:
    // 构造函数和析构函数
    RBTree()
    {
    }
    ~RBTree()
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
        if(m_root == nullptr)
        {
            m_root = new Node(val);
            m_root->m_color = Color::Black;
            return;
        }
        Node* node = m_root;
        Node* p = nullptr;
        while(node != nullptr)
        {
            if(m_comp(node->m_data,val))
            {
                p = node;
                node = node->m_left;
            }else if(m_comp(val,node->m_data))
            {
                p = node;
                node = node->m_right;
            }else
            {
                return;
            }
        }
        node = new Node(val,p);
        if(m_comp(p->m_data,val))
        {
            p->m_left = node;
        }else
        {
            p->m_right = node;
        }
        // 新节点一定是红色节点，如果父节点是红色，就需要调整，父节点是根节点，一定不为红
        // 所以node一定有爷爷节点
        if(p->m_color == node->m_color)
        {
            setColorAfterInsert(node);
        }
    }
    void setColorAfterInsert(Node* node)
    {
        while(color(node->m_parent) == Color::Red)
        {
            // 在左边，则叔叔节点是右边
            if(node->m_parent->m_parent->m_left == node->m_parent)
            {
                Node* uncle = node->m_parent->m_parent->m_right;
                if(color(uncle) == Color::Red)
                {
                    node->m_parent->m_parent->m_color = Color::Red;
                    node->m_parent->m_color = Color::Black;
                    uncle->m_color = Color::Black;
                    node = node->m_parent->m_parent;
                }else
                {
                    // 如果节点在右侧，先旋转到和父节点同一侧，
                    if(node->m_parent->m_right == node)
                    {
                        node = node->m_parent;
                        leftRotate(node);
                    }
                    node->m_parent->m_parent->m_color = Color::Red;
                    node->m_parent->m_color = Color::Black;
                    rightRotate(node->m_parent->m_parent);
                    break;
                }
            }else
            {
                Node* uncle = node->m_parent->m_parent->m_left;
                if(color(uncle) == Color::Red)
                {
                    node->m_parent->m_parent->m_color = Color::Red;
                    node->m_parent->m_color = Color::Black;
                    uncle->m_color = Color::Black;
                    node = node->m_parent->m_parent;
                }else
                {
                    // 如果节点在右侧，先旋转到和父节点同一侧，
                    if(node->m_parent->m_left == node)
                    {
                        node = node->m_parent;
                        rightRotate(node);
                    }
                    node->m_parent->m_parent->m_color = Color::Red;
                    node->m_parent->m_color = Color::Black;
                    leftRotate(node->m_parent->m_parent);
                    break;
                }
            }
        }
        m_root->m_color = Color::Black;
    }
    Color color(Node* node)
    {
        return node == nullptr ? Color::Black : node->m_color;
    }
    void remove(const T& val)
    {
        Node* node = m_root;
        while(node != nullptr)
        {
            if(m_comp(node->m_data,val))
            {
                node = node->m_left;
            }else if(m_comp(val,node->m_data))
            {
                node = node->m_right;
            }else
            {
                break;
            }
        }
        if(node == nullptr)
        {
            return;
        }
        if(node->m_left != nullptr && node->m_right != nullptr)
        {
            Node* cur = node->m_left;
            while(cur->m_right != nullptr)
            {
                cur = cur->m_right;
            }
            node->m_data = cur->m_data;
            node = cur;
        }
        Node* child = node->m_left;
        if(child == nullptr)
        {
            child = node->m_right;
        }
        // node有子节点的时候
        if(child != nullptr)
        {
            child->m_parent = node->m_parent;
            if(child->m_parent == nullptr)
            {
                m_root = child;
            }else
            {
                if(node->m_parent->m_left == node)
                {
                    node->m_parent->m_left = child;
                }else
                {
                    node->m_parent->m_right = child;
                }
            }
            if(color(node) == Color::Black)
            {
                setColorAfterRemove(child);
            }
            
            delete node;
        }else
        {
            if(node->m_parent == nullptr)
            {
                m_root = nullptr;
                delete node;
                return;
            }else
            {
                if(color(node) == Color::Black)
                {
                    setColorAfterRemove(node);
                }
                if(node->m_parent->m_left == node)
                {
                    node->m_parent->m_left = nullptr;
                }else
                {
                    node->m_parent->m_right = nullptr;
                }
                delete node;
            }
        }
    }
    
    void setColorAfterRemove(Node* node)
    {
        while(color(node) == Color::Black && node != m_root)
        {
            if(node->m_parent->m_left == node)
            {
                Node* uncle = node->m_parent->m_right;
                if(color(uncle) == Color::Red)
                {
                    uncle->m_color = Color::Black;
                    node->m_parent->m_color = Color::Red;
                    leftRotate(node->m_parent);
                    uncle = node->m_parent->m_right;
                }
                if(color(uncle->m_right) == Color::Red)
                {
                    uncle->m_color = node->m_parent->m_color;
                    node->m_parent->m_color = Color::Black;
                    uncle->m_right->m_color = Color::Black;
                    leftRotate(node->m_parent);
                    break;
                }else if(color(uncle->m_left) == Color::Red)
                {
                    uncle->m_left->m_color = Color::Black;
                    uncle->m_color = Color::Red;
                    rightRotate(uncle);
                }else
                {
                    uncle->m_color = Color::Red;
                    node = node->m_parent;
                }
            }else
            {
                Node* uncle = node->m_parent->m_left;
                if(color(uncle) == Color::Red)
                {
                    uncle->m_color = Color::Black;
                    node->m_parent->m_color = Color::Red;
                    rightRotate(node->m_parent);
                    uncle = node->m_parent->m_left;
                }
                if(color(uncle->m_left) == Color::Red)
                {
                    uncle->m_color = node->m_parent->m_color;
                    node->m_parent->m_color = Color::Black;
                    uncle->m_left->m_color = Color::Black;
                    rightRotate(node->m_parent);
                    break;
                }else if(color(uncle->m_right) == Color::Red)
                {
                    uncle->m_right->m_color = Color::Black;
                    uncle->m_color = Color::Red;
                    leftRotate(uncle);
                }else
                {
                    uncle->m_color = Color::Red;
                    node = node->m_parent;
                }
            }
        }
        node->m_color = Color::Black;
    }
    
    Color getcolor(Node* node)
    {
        return node == nullptr ? Color::Black : node->m_color;
    }
    
    // 左侧
    void leftRotate(Node* node)
    {
        Node* child = node->m_right;
        if(node->m_parent == nullptr)
        {
            m_root = child;
        }else
        {
            if(node->m_parent->m_left == node)
            {
                node->m_parent->m_left = child;
            }else
            {
                node->m_parent->m_right = child;
            }
        }
        child->m_parent = node->m_parent;
        node->m_right = child->m_left;
        if(node->m_right != nullptr)
        {
            node->m_right->m_parent = node;
        }
        node->m_parent = child;
        child->m_left = node;
    }
    void rightRotate(Node* node)
    {
        Node* child = node->m_left;
        if(node->m_parent == nullptr)
        {
            m_root = child;
        }else
        {
            if(node->m_parent->m_left == node)
            {
                node->m_parent->m_left = child;
            }else
            {
                node->m_parent->m_right = child;
            }
        }
        child->m_parent = node->m_parent;
        node->m_left = child->m_right;
        if(node->m_left != nullptr)
        {
            node->m_left->m_parent = node;
        }
        child->m_right = node;
        node->m_parent = child;
    }
};
