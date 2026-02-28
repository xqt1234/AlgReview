#include "binary_tree_problems.h"
#include <iostream>
void showAndDelete(BinaryTreeI<int>::Node* root)
{
    std::queue<BinaryTreeI<int>::Node*> que;
    que.push(root);
    std::cout << "层序遍历生成的二叉树" << std::endl;
    while(!que.empty())
    {
        BinaryTreeI<int>::Node* node = que.front();
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
    BinaryTreeI<int> ta;
    BinaryTreeI<int> tb;
    ta.insert(10);
    ta.insert(12);
    ta.insert(6);
    ta.insert(3);
    tb.insert(10);
    tb.insert(12);
    tb.insert(6);
    tb.insert(6);
    std::cout << "hello world" << std::endl;
    if(isSameTree<int>(ta.getRoot(),tb.getRoot()))
    {
        std::cout << "两颗树相同" << std::endl;
    }else
    {
        std::cout << "两棵树不同" << std::endl;
    }

    BinaryTreeI<int> tc;
    BinaryTreeI<int> td;
    tc.insert(10);
    tc.insert(12);
    tc.insert(6);
    tc.insert(3);
    tc.insert(5);
    tc.insert(4);
    tc.insert(8);
    td.insert(10);
    td.insert(6);
    td.insert(12);
    td.insert(8);
    td.insert(4);
    td.insert(5);
    td.insert(3);
    if(isMirrorTree<int>(tc.getRoot(),td.getRoot()))
    {
        std::cout << "两颗树是镜像" << std::endl;
    }else
    {
        std::cout << "两棵树不是镜像" << std::endl;
    }

    BinaryTreeI<int> te;
    te.insert(20);
    BinaryTreeI<int>::Node* t_root = te.getRoot();
    t_root->m_left = new BinaryTreeI<int>::Node(20);
    if(isComplateTree<int>(t_root))
    {
        std::cout << "是完全二叉树" << std::endl;
    }else
    {
        std::cout << "不是完全二叉树" << std::endl;
    }
    t_root->m_left->m_left = new BinaryTreeI<int>::Node(20);
    if(isComplateTree<int>(t_root))
    {
        std::cout << "是完全二叉树" << std::endl;
    }else
    {
        std::cout << "不是完全二叉树" << std::endl;
    }
    BinaryTreeI<int> tf;
    tf.insert(20);
    tf.insert(10);
    tf.insert(25);
    tf.insert(6);
    tf.insert(15);
    tf.insert(22);
    tf.insert(28);
    tf.order_show(BinaryTreeI<int>::showType::PreOrder);
    tf.order_show(BinaryTreeI<int>::showType::InOrder);
    tf.order_show(BinaryTreeI<int>::showType::PostOrder);
    tf.order_show(BinaryTreeI<int>::showType::LevelOrder);
    std::vector<int> prevec = tf.preorder();
    std::vector<int> invec = tf.inorder();
    std::vector<int> postvec = tf.postorder();
    BinaryTreeI<int>::Node* r_root = buildTreeFromPreIn(prevec,invec,0,prevec.size() - 1,0,invec.size()-1);
    showAndDelete(r_root);
    BinaryTreeI<int>::Node* p_root = buildTreeFromInPost(invec,postvec,0,prevec.size() - 1,0,invec.size()-1);
    showAndDelete(p_root);
    return 0;
}