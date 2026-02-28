#pragma once
#include "binaryTreeI.h"

// 完全二叉树判断、重建树、相同树、镜像树。
// 判断两棵树是否相同 功能：判断两棵二叉树结构和节点值是否完全相同。
template <typename T>
bool isSameTree(typename BinaryTreeI<T>::Node* p, typename BinaryTreeI<T>::Node* q)
{
    if (p == nullptr && q == nullptr)
    {
        return true;
    }
    if (p == nullptr || q == nullptr)
    {
        return false;
    }
    if (p->m_data != q->m_data)
    {
        return false;
    }
    return isSameTree<T>(p->m_left, q->m_left) && isSameTree<T>(p->m_right, q->m_right);
}
// 判断两棵树是否镜像 功能：判断两棵树是否互为镜像（左右对称）。
template <typename T>
bool isMirrorTree(typename BinaryTreeI<T>::Node* p, typename BinaryTreeI<T>::Node* q)
{
    if (p == nullptr && q == nullptr)
    {
        return true;
    }
    if (p == nullptr || q == nullptr)
    {
        return false;
    }
    return (p->m_data == q->m_data) && isMirrorTree<T>(p->m_left, q->m_right)
        && isMirrorTree<T>(p->m_right, q->m_left);
}
// 判断是否为完全二叉树 功能：用层序遍历判断，遇到空节点后不能再有非空节点。
template <typename T>
bool isComplateTree(typename BinaryTreeI<T>::Node* root)
{
    if (root == nullptr)
    {
        return true;
    }
    std::queue<typename BinaryTreeI<T>::Node*> que;
    que.push(root);
    bool noChild = false;
    while (!que.empty())
    {
        typename BinaryTreeI<T>::Node* node = que.front();
        que.pop();
        if (noChild && (node->m_left != nullptr || node->m_right != nullptr))
        {
            return false;
        }
        if (node->m_left != nullptr)
        {
            que.push(node->m_left);
        }
        else
        {
            noChild = true;
        }
        if (node->m_right != nullptr)
        {
            if (noChild)
            {
                return false;
            }
            que.push(node->m_right);
        }
        else
        {
            noChild = true;
        }
    }
    return true;
}
// 根据前序+中序重建二叉树 功能：返回重建后的树根节点。
template <typename T>
BinaryTreeI<T>::Node* buildTreeFromPreIn(const std::vector<T>& preorder,
    const std::vector<T>& inorder,
    int preStart, int preEnd,
    int inStart, int inEnd
)
{
    if(preStart > preEnd || inStart > inEnd)
    {
        return nullptr;
    }
    // 左侧
    typename BinaryTreeI<T>::Node* root = new BinaryTreeI<T>::Node(preorder[preStart]);
    // 找到根节点在中序遍历中的位置
    for(int i = inStart;i <= inEnd;++i)
    {
        if(preorder[preStart] == inorder[i])
        {
            root->m_left = buildTreeFromPreIn(preorder,inorder,preStart + 1,preStart + i - inStart,inStart,i - 1);
            root->m_right = buildTreeFromPreIn(preorder,inorder,preStart + i - inStart + 1,preEnd,i + 1,inEnd);
            return root;
        }
    }
    return root;
}

// 根据中序+后序重建二叉树 功能：返回重建后的树根节点。
template <typename T>
BinaryTreeI<T>::Node* buildTreeFromInPost(
    const std::vector<T>& inorder,
    const std::vector<T>& postorder,
    int inStart, int inEnd,
    int postStart, int postEnd)
{
    if(inStart > inEnd || postStart > postEnd)
    {
        return nullptr;
    }
    typename BinaryTreeI<T>::Node* root = new BinaryTreeI<T>::Node(postorder[postEnd]);
    // 找到根节点在中序中的位置，前面为左子树，后面为右子树
    for(int i = inStart;i < inEnd;++i)
    {
        if(postorder[postEnd] == inorder[i])
        {
            root->m_left = buildTreeFromInPost(inorder,postorder,inStart,i - 1,postStart,postStart + i - inStart - 1);
            root->m_right = buildTreeFromInPost(inorder,postorder,i+1,inEnd,postStart + i - inStart,postEnd - 1);
            return root;
        }
    }
    return root;
}