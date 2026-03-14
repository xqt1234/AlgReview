#include <gtest/gtest.h>
#include <vector>
#include <queue>
#include "RBTree.h"

// 测试空树
TEST(RBTreeTest, EmptyTree) {
    RBTree<int> tree;
    EXPECT_EQ(tree.getRoot(), nullptr);
}

// 测试单节点插入（根必须是黑色）
TEST(RBTreeTest, SingleInsert) {
    RBTree<int> tree;
    tree.insert(10);
    auto* root = tree.getRoot();
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->m_data, 10);
    EXPECT_EQ(root->m_color, RBTree<int>::Color::Black);
    EXPECT_EQ(root->m_left, nullptr);
    EXPECT_EQ(root->m_right, nullptr);
}

// 测试插入两个节点（父红子红，需要变色）
TEST(RBTreeTest, InsertTwoNodes) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    auto* root = tree.getRoot();
    auto* left = root->m_left;
    EXPECT_EQ(root->m_color, RBTree<int>::Color::Black);
    EXPECT_EQ(left->m_color, RBTree<int>::Color::Red);
    EXPECT_EQ(left->m_data, 5);
}

// 测试插入三个节点触发左旋
TEST(RBTreeTest, InsertThreeNodesLeftRotate) {
    RBTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);  // 应该触发左旋
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_color, RBTree<int>::Color::Black);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_left->m_color, RBTree<int>::Color::Red);
    EXPECT_EQ(root->m_right->m_color, RBTree<int>::Color::Red);
}

// 测试插入三个节点触发右旋
TEST(RBTreeTest, InsertThreeNodesRightRotate) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // 应该触发右旋
    auto* root = tree.getRoot();
    EXPECT_EQ(root->m_data, 20);
    EXPECT_EQ(root->m_color, RBTree<int>::Color::Black);
    EXPECT_EQ(root->m_left->m_data, 10);
    EXPECT_EQ(root->m_right->m_data, 30);
    EXPECT_EQ(root->m_left->m_color, RBTree<int>::Color::Red);
    EXPECT_EQ(root->m_right->m_color, RBTree<int>::Color::Red);
}

// 测试插入多个节点保持红黑树性质
TEST(RBTreeTest, MultipleInsertionsMaintainProperties) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 65};
    for (int v : values) {
        tree.insert(v);
    }
    // 验证根节点是黑色
    EXPECT_EQ(tree.getRoot()->m_color, RBTree<int>::Color::Black);
    // 验证没有连续红节点
    std::function<bool(typename RBTree<int>::Node*)> checkNoDoubleRed;
    checkNoDoubleRed = [&checkNoDoubleRed](typename RBTree<int>::Node* n) -> bool {
        if (!n) return true;
        if (n->m_color == RBTree<int>::Color::Red) {
            if (n->m_left && n->m_left->m_color == RBTree<int>::Color::Red) return false;
            if (n->m_right && n->m_right->m_color == RBTree<int>::Color::Red) return false;
        }
        return checkNoDoubleRed(n->m_left) && checkNoDoubleRed(n->m_right);
    };
    EXPECT_TRUE(checkNoDoubleRed(tree.getRoot()));
    // 验证黑高一致（简化检查：所有叶子路径黑节点数相同）
    std::function<int(typename RBTree<int>::Node*)> getBlackHeight;
    getBlackHeight = [&getBlackHeight](typename RBTree<int>::Node* n) -> int {
        if (!n) return 1;
        int leftBH = getBlackHeight(n->m_left);
        int rightBH = getBlackHeight(n->m_right);
        EXPECT_EQ(leftBH, rightBH) << "Black height mismatch at node: " << n->m_data;
        return leftBH + (n->m_color == RBTree<int>::Color::Black ? 1 : 0);
    };
    getBlackHeight(tree.getRoot());
}

// 测试中序遍历结果有序（升序）
TEST(RBTreeTest, InorderTraversalSorted) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    std::vector<int> result;
    std::function<void(typename RBTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](typename RBTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    std::vector<int> expected = {10, 25, 30, 50, 60, 75, 80};
    EXPECT_EQ(result, expected);
}

// 测试删除叶子节点
TEST(RBTreeTest, RemoveLeafNode) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(10);
    std::vector<int> result;
    std::function<void(typename RBTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](typename RBTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    EXPECT_TRUE(std::find(result.begin(), result.end(), 10) == result.end());
}

// 测试删除根节点
TEST(RBTreeTest, RemoveRootNode) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(50);
    auto* root = tree.getRoot();
    EXPECT_NE(root->m_data, 50);
    // 验证红黑树性质
    EXPECT_EQ(root->m_color, RBTree<int>::Color::Black);
}

// 测试删除后保持有序
TEST(RBTreeTest, RemoveMaintainsSortedOrder) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    tree.remove(25);
    std::vector<int> result;
    std::function<void(typename RBTree<int>::Node*)> inorder;
    inorder = [&inorder, &result](typename RBTree<int>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(tree.getRoot());
    std::vector<int> expected = {10, 30, 50, 60, 75, 80};
    EXPECT_EQ(result, expected);
}

// 测试删除所有节点
TEST(RBTreeTest, RemoveAllNodes) {
    RBTree<int> tree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }
    for (int v : values) {
        std::cout << "移除节点：" << v << std::endl;
        tree.remove(v);
    }
    EXPECT_EQ(tree.getRoot(), nullptr);
}

// 测试自定义比较器（最小堆红黑树）
TEST(RBTreeTest, CustomComparatorMinHeap) {
    RBTree<int, std::less<int>> minTree;
    std::vector<int> values = {50, 25, 75, 10, 30, 60, 80};
    for (int v : values) {
        minTree.insert(v);
    }
    std::vector<int> result;
    std::function<void(typename RBTree<int, std::less<int>>::Node*)> inorder;
    inorder = [&inorder, &result](typename RBTree<int, std::less<int>>::Node* n) {
        if (!n) return;
        inorder(n->m_left);
        result.push_back(n->m_data);
        inorder(n->m_right);
    };
    inorder(minTree.getRoot());
    // std::less 中序是降序
    std::vector<int> expected = {80, 75, 60, 50, 30, 25, 10};
    EXPECT_EQ(result, expected);
}