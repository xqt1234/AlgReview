#include "binary_tree_problems.h"
#include <iostream>
void showAndDelete(BinaryTree<int>::Node* root)
{
    std::queue<BinaryTree<int>::Node*> que;
    que.push(root);
    std::cout << "层序遍历生成的二叉树" << std::endl;
    while(!que.empty())
    {
        BinaryTree<int>::Node* node = que.front();
        que.pop();
        if(node->m_left)
        {
            que.push(node->m_left);
        }
        if(node->m_right)
        {
            que.push(node->m_right);
        }
        std::cout << node->m_data << " ";
        delete node;
    }
    std::cout << std::endl;
}
int main()
{
    BinaryTree<int> ta;
    ta.insert(20);
    ta.insert(10);
    ta.insert(25);
    ta.insert(6);
    ta.insert(15);
    ta.insert(22);
    ta.insert(28);
    ta.order_show(BinaryTree<int>::showType::PreOrder);
    std::vector<int> res;
    findValues(ta.getRoot(),res,10,22);
    for(int val : res)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    BinaryTree<int>::Node* root = new BinaryTree<int>::Node(20);
    root->m_left = new BinaryTree<int>::Node(10);
    root->m_right = new BinaryTree<int>::Node(21);
    root->m_left->m_left = new BinaryTree<int>::Node(6);
    root->m_left->m_right = new BinaryTree<int>::Node(15);
    root->m_right->m_left = new BinaryTree<int>::Node(22);
    root->m_right->m_right = new BinaryTree<int>::Node(28);
    if(isBSTree<int>(root))
    {
        std::cout << "是二叉搜索树" << std::endl;
    }else
    {
        std::cout << "不是二叉搜索树" << std::endl;
    }
    BinaryTree<int>::Node* commonroot = lowestCommonAncestorb<int>(root,root->m_left->m_left,root->m_left->m_right);
    std::cout << "公共节点的值是：" << commonroot->m_data << std::endl;
    int k = 3;
    
    int kminval = kthSmallest<int>(root,k);
    std::cout << "第" << k << "小的元素是:" << kminval << std::endl;
    showAndDelete(root);
    return 0;
}