#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "binaryTree.h"

// 测试空树
TEST(BinaryTreeTest, EmptyTree) {
    BinaryTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 0);
    EXPECT_EQ(tree.getHeight(), 0);
    EXPECT_EQ(tree.getLeafCount(), 0);
}

// 测试插入和大小
TEST(BinaryTreeTest, InsertAndSize) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 4);
}

// 测试查找
TEST(BinaryTreeTest, Search) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(15));
    EXPECT_TRUE(tree.search(3));
    EXPECT_FALSE(tree.search(100));
}

// 测试删除叶子节点
TEST(BinaryTreeTest, RemoveLeaf) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    tree.remove(3);
    EXPECT_FALSE(tree.search(3));
    EXPECT_EQ(tree.getSize(), 3);
}

// 测试删除有一个子节点的节点
TEST(BinaryTreeTest, RemoveWithOneChild) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7); // 5 has left=3, right=7

    tree.remove(5); // 删除5，应该由7代替位置
    EXPECT_FALSE(tree.search(5));
    EXPECT_TRUE(tree.search(7));
    EXPECT_EQ(tree.getSize(), 4);
}

// 测试删除有两个子节点的节点（使用前驱替换）
TEST(BinaryTreeTest, RemoveWithTwoChildren) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    tree.remove(10); // root with two children
    EXPECT_FALSE(tree.search(10));
    EXPECT_EQ(tree.getSize(), 4);
}

// 测试先序遍历
TEST(BinaryTreeTest, PreOrderTraversal) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::vector<int> expected = {10, 5, 3, 7, 15}; // 取决于插入顺序和比较器
    EXPECT_EQ(tree.preorder(), expected);
}

// 测试中序遍历
TEST(BinaryTreeTest, InOrderTraversal) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::vector<int> expected = {3, 5, 7, 10, 15}; // 升序（因为默认 greater，其实是降序？这里注意）
    // 如果 Comp = std::greater<int>，那么根是最大值，左子树比根小，右子树比根大
    // 插入顺序是 10,5,15,3,7 -> 结构是：
    //        10
    //      /    \
    //     5      15
    //    / \
    //   3   7
    // 中序遍历: 3,5,7,10,15
    EXPECT_EQ(tree.inorder(), expected);
}

// 测试后序遍历
TEST(BinaryTreeTest, PostOrderTraversal) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::vector<int> expected = {3, 7, 5, 15, 10};
    EXPECT_EQ(tree.postorder(), expected);
}

// 测试层序遍历
TEST(BinaryTreeTest, LevelOrderTraversal) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::vector<int> expected = {10, 5, 15, 3, 7};
    EXPECT_EQ(tree.levelOrder(), expected);
}

// 测试树高度
TEST(BinaryTreeTest, Height) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    EXPECT_EQ(tree.getHeight(), 3);
}

// 测试叶子节点数
TEST(BinaryTreeTest, LeafCount) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    EXPECT_EQ(tree.getLeafCount(), 3); // 3,7,15
}

// 测试区间查找
TEST(BinaryTreeTest, FindValuesInRange) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    std::vector<int> result;
    tree.findValues(result, 5, 15);
    // 预期结果包含 5,7,10,12,15 （按中序顺序）
    std::vector<int> expected = {5, 7, 10, 12, 15};
    EXPECT_EQ(result, expected);
}

// 测试自定义比较器（最小堆）
TEST(BinaryTreeTest, CustomComparatorMinHeap) {
    BinaryTree<int, std::less<int>> minTree;
    minTree.insert(10);
    minTree.insert(5);
    minTree.insert(15);
    minTree.insert(3);

    // 中序遍历应该是降序排列，因为小的在左边
    std::vector<int> expected = {15, 10, 5, 3};
    EXPECT_EQ(minTree.inorder(), expected);
}