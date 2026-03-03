#pragma once
#include "binaryTree.h"
#include <iostream>
// 区间查找、验证 BST、找第 K 小
// 区间查找
template <typename T>
void findValues(typename BinaryTree<T>::Node* node, std::vector<T>& vec, const T& i, const T& j)
{
    if(node == nullptr)
    {
        return;
    }
    if(node->m_data > i)
    {
        findValues(node->m_left,vec,i,j);
    }
    if(node->m_data < j)
    {
        findValues(node->m_right,vec,i,j);
    }
    if(node->m_data >= i && node->m_data <=j)
    {
        vec.push_back(node->m_data);
    }
}
// 验证是否为bs树，中序遍历是严格升序的，
template<typename T>
bool isBSTree(typename BinaryTree<T>::Node* root)
{
    std::stack<typename BinaryTree<T>::Node*> st;
    typename BinaryTree<T>::Node* cur = root;
    typename BinaryTree<T>::Node* pre = nullptr;
    while(!st.empty() || cur != nullptr)
    {
        if(cur != nullptr)
        {
            st.push(cur);
            cur = cur->m_left;
        }else
        {
            typename BinaryTree<T>::Node* node = st.top();
            st.pop();
            if(pre != nullptr && node->m_data <= pre->m_data)
            {
                return false;
            }
            pre = node;
            cur = node->m_right;
            
        }
    }
    return true;
}
struct TreeNode {
    int m_data;
    TreeNode *m_left;
    TreeNode *m_right;
    TreeNode *m_parent; // 指向父节点的指针
    TreeNode(int x) : m_data(x), m_left(nullptr), m_right(nullptr), m_parent(nullptr) {}
};
// 最近公共祖先
TreeNode* lowestCommonAncestor(TreeNode* p, TreeNode* q)
{
    TreeNode* pn = p;
    TreeNode* qn = q;
    while(pn != qn)
    {
        pn = (pn == nullptr) ? qn : pn->m_parent;
        qn = (qn == nullptr) ? pn : qn->m_parent;
    }
    return pn;
}
// 普通二叉树最近公共祖先
template<typename T>
typename BinaryTree<T>::Node* lowestCommonAncestorb(typename BinaryTree<T>::Node* root,typename BinaryTree<T>::Node* p,typename BinaryTree<T>::Node* q)
{
    if(root == nullptr || root == p || root == q)
    {
        return root;
    }
    typename BinaryTree<T>::Node* left = lowestCommonAncestorb<T>(root->m_left,p,q);
    typename BinaryTree<T>::Node* right = lowestCommonAncestorb<T>(root->m_right,p,q);
    if(left != nullptr && right != nullptr)
    {
        return root;
    }else if(left != nullptr)
    {
        return left;
    }else if(right != nullptr)
    {
        return right;
    }else
    {
        return nullptr;
    }
}

// 找第k小的元素
template<typename T>
T kthSmallest(typename BinaryTree<T>::Node* m_root,int k)
{
    std::stack<typename BinaryTree<T>::Node*> st;
    typename BinaryTree<T>::Node* cur = m_root;
    int size = 0;
    while(!st.empty() || cur != nullptr)
    {
        if(cur != nullptr)
        {
            st.push(cur);
            cur = cur->m_left;
        }else
        {
            typename BinaryTree<T>::Node* node = st.top();
            st.pop();
            size++;
            if(size == k)
            {
                return node->m_data;
            }
            cur = node->m_right;
        }
    }
    return m_root->m_data;
}

