#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "avlTree.h"

// 测试空树
TEST(AVLTreeTest, EmptyTree) {
    AVLTree<int> tree;
    EXPECT_EQ(tree.getRoot(), nullptr);
}

// 测试单节点插入
TEST(AVLTreeTest, SingleInsert) {
    AVLTree<int> tree;
    tree.insert(10);
    auto* root = tree.getRoot();
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->m_data, 10);
    EXPECT_EQ(root->m_height, 1);
    EXPECT_EQ(root->m_left, nullptr);
    EXPECT_EQ(root->m_right, nullptr);
}

// 测试插入多个节点触发右旋转（LL情况）
TEST(AVLTreeTest, RightRotation_LL) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);  // 触发右旋转
    
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_height, 2);
}

// 测试插入多个节点触发左旋转（RR情况）
TEST(AVLTreeTest, LeftRotation_RR) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // 触发左旋转
    
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_height, 2);
}

// 测试插入多个节点触发左右旋（LR情况）
TEST(AVLTreeTest, LeftRightRotation_LR) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);  // 触发左右旋
    
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_height, 2);
}

// 测试插入多个节点触发右左旋（RL情况）
TEST(AVLTreeTest, RightLeftRotation_RL) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);  // 触发右左旋
    
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_height, 2);
}

// 测试连续插入保持平衡
TEST(AVLTreeTest, MultipleInsertionsMaintainBalance) {
    AVLTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 65};
    for (int v : values) {
        tree.insert(v);
    }
    
    // 用 std::function 实现递归检查平衡
    std::function<int(AVLTree<int>::Node*)> checkBalance;
    checkBalance = [&checkBalance](AVLTree<int>::Node* node) -> int {
        if (!node) return 0;
        int lh = checkBalance(node->m_left);
        int rh = checkBalance(node->m_right);
        EXPECT_LE(std::abs(lh - rh), 1) << "Unbalanced at node: " << node->m_data;
        return std::max(lh, rh) + 1;
    };
    
    checkBalance(tree.getRoot());
}

// 测试中序遍历结果（手动收集）- 修正：std::greater 中序是升序
TEST(AVLTreeTest, InorderTraversalSortedAscending) {
    AVLTree<int> tree;  // 默认 std::greater<int>
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    
    // 手动中序遍历
    std::vector<int> result;
    std::function<void(AVLTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](AVLTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    
    // 对于 std::greater，中序遍历是升序（从小到大）
    std::vector<int> expected = {10, 25, 30, 50, 60, 75, 80};
    EXPECT_EQ(result, expected);
}

// 测试删除叶子节点
TEST(AVLTreeTest, RemoveLeafNode) {
    AVLTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(10);
    
    std::vector<int> result;
    std::function<void(AVLTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](AVLTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    
    EXPECT_TRUE(std::find(result.begin(), result.end(), 10) == result.end());
}

// 测试删除根节点
TEST(AVLTreeTest, RemoveRootNode) {
    AVLTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(50);
    auto* root = tree.getRoot();
    EXPECT_NE(root->m_data, 50);
}

// 测试删除后保持有序
TEST(AVLTreeTest, RemoveMaintainsSortedOrder) {
    AVLTree<int> tree;  // 默认 std::greater<int>
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(25);
    
    std::vector<int> result;
    std::function<void(AVLTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](AVLTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    
    // 对于 std::greater，中序遍历是升序（从小到大）
    std::vector<int> expected = {10, 30, 50, 60, 75, 80};
    EXPECT_EQ(result, expected);
}
// 测试删除所有节点
TEST(AVLTreeTest, RemoveAllNodes) {
    AVLTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    for (int v : values) {
        tree.remove(v);
    }
    EXPECT_EQ(tree.getRoot(), nullptr);
}

// 测试自定义比较器（最小堆AVL）- std::less 中序是降序
TEST(AVLTreeTest, CustomComparatorMinHeap_InorderDescending) {
    AVLTree<int, std::less<int>> minTree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        minTree.insert(v);
    }
    
    std::vector<int> result;
    std::function<void(AVLTree<int, std::less<int>>::Node*)> inorder;
    inorder = [&inorder, &result](AVLTree<int, std::less<int>>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(minTree.getRoot());
    
    // 对于 std::less，中序遍历是降序（从大到小）
    std::vector<int> expected = {80, 75, 60, 50, 30, 25, 10};
    EXPECT_EQ(result, expected);
}