#include "avl_tree_problems.h"
#include <iostream>
#include <stack>
template <typename T>
void show(AVLTree<T>& pTree)
{
    typename AVLTree<T>::Node* root = pTree.getRoot();
    std::queue<typename AVLTree<T>::Node*> que;
    que.push(root);
    while (!que.empty())
    {
        int n = que.size();
        for (int i = 0; i < n; ++i)
        {
            typename AVLTree<T>::Node* node = que.front();
            que.pop();
            std::cout << node->m_data << " ";
            if (node->m_left)
            {
                que.push(node->m_left);
            }
            if (node->m_right)
            {
                que.push(node->m_right);
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    AVLTree<int> avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.insert(5);
    avl.insert(6);
    avl.insert(7);
    avl.insert(8);
    avl.insert(9);
    avl.insert(10);
    show(avl);
    avl.remove(10);
    avl.remove(9);
    show(avl);
    return 0;
}