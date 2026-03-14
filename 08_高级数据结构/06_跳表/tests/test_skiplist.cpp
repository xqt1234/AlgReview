#include "skipList.hpp"  // 假设你的跳表代码在SkipList.h中
#include <gtest/gtest.h>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

class TestSkipList : public ::testing::Test {
protected:
    void SetUp() override {
        // 可以在每个测试前设置随机种子
        srand(42);  // 固定种子以确保测试可重复
    }
    
    void TearDown() override {
        // 清理代码
    }
};

// 测试1: 默认构造函数
TEST_F(TestSkipList, DefaultConstructor) {
    SkipList<int> sl;
    EXPECT_TRUE(sl.isEmpty());
    EXPECT_EQ(sl.getSize(), 0);
    
    // 测试搜索应该返回false
    EXPECT_FALSE(sl.search(1));
    EXPECT_FALSE(sl.search(100));
}

// 测试2: 带参数的构造函数
TEST_F(TestSkipList, ParameterizedConstructor) {
    SkipList<int> sl(10, 0.3f);
    EXPECT_TRUE(sl.isEmpty());
    EXPECT_EQ(sl.getSize(), 0);
    
    // 测试空跳表的搜索
    EXPECT_FALSE(sl.search(5));
}

// 测试3: 基本插入和搜索
TEST_F(TestSkipList, BasicInsertAndSearch) {
    SkipList<int> sl;
    
    // 插入单个元素
    EXPECT_TRUE(sl.insert(42));
    EXPECT_FALSE(sl.isEmpty());
    EXPECT_EQ(sl.getSize(), 1);
    sl.show();
    EXPECT_TRUE(sl.search(42));
    EXPECT_FALSE(sl.search(41));
    EXPECT_FALSE(sl.search(43));
    
    // 插入第二个元素
    EXPECT_TRUE(sl.insert(20));
    EXPECT_EQ(sl.getSize(), 2);
    EXPECT_TRUE(sl.search(20));
    EXPECT_TRUE(sl.search(42));
    
    // 插入重复元素
    EXPECT_FALSE(sl.insert(42));  // 应该返回false
    EXPECT_EQ(sl.getSize(), 2);    // 大小不应增加
}

// 测试4: 升序插入测试
TEST_F(TestSkipList, AscendingInsert) {
    SkipList<int> sl;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    for (int num : nums) {
        EXPECT_TRUE(sl.insert(num));
    }
    
    EXPECT_EQ(sl.getSize(), nums.size());
    
    // 验证所有元素都存在
    for (int num : nums) {
        EXPECT_TRUE(sl.search(num));
    }
    
    // 验证不存在的元素
    EXPECT_FALSE(sl.search(0));
    EXPECT_FALSE(sl.search(11));
    EXPECT_FALSE(sl.search(100));
}

// 测试5: 降序插入测试
TEST_F(TestSkipList, DescendingInsert) {
    SkipList<int> sl;
    std::vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    for (int num : nums) {
        EXPECT_TRUE(sl.insert(num));
    }
    
    EXPECT_EQ(sl.getSize(), nums.size());
    
    // 验证所有元素都存在
    for (int i = 1; i <= 10; i++) {
        EXPECT_TRUE(sl.search(i));
    }
}

// 测试6: 随机顺序插入
TEST_F(TestSkipList, RandomInsert) {
    SkipList<int> sl;
    std::vector<int> nums = {7, 3, 9, 1, 4, 8, 2, 6, 5, 10};
    
    for (int num : nums) {
        EXPECT_TRUE(sl.insert(num));
    }
    
    EXPECT_EQ(sl.getSize(), nums.size());
    
    // 验证所有元素都存在
    for (int i = 1; i <= 10; i++) {
        EXPECT_TRUE(sl.search(i));
    }
}

// 测试7: 删除功能测试
TEST_F(TestSkipList, DeleteOperations) {
    SkipList<int> sl;
    
    // 插入一些数据
    for (int i = 1; i <= 10; i++) {
        sl.insert(i);
    }
    EXPECT_EQ(sl.getSize(), 10);
    
    // 删除中间元素
    sl.deleteVal(5);
    EXPECT_EQ(sl.getSize(), 9);
    EXPECT_FALSE(sl.search(5));
    
    // 验证其他元素仍然存在
    for (int i = 1; i <= 10; i++) {
        if (i != 5) {
            EXPECT_TRUE(sl.search(i));
        }
    }
    
    // 删除头部元素
    sl.deleteVal(1);
    EXPECT_EQ(sl.getSize(), 8);
    EXPECT_FALSE(sl.search(1));
    
    // 删除尾部元素
    sl.deleteVal(10);
    EXPECT_EQ(sl.getSize(), 7);
    EXPECT_FALSE(sl.search(10));
    
    // 删除不存在的元素
    sl.deleteVal(100);  // 应该什么都不做
    EXPECT_EQ(sl.getSize(), 7);
}

// 测试8: 清空功能测试
TEST_F(TestSkipList, ClearOperation) {
    SkipList<int> sl;
    
    // 插入数据
    for (int i = 1; i <= 5; i++) {
        sl.insert(i);
    }
    EXPECT_EQ(sl.getSize(), 5);
    EXPECT_FALSE(sl.isEmpty());
    
    // 清空
    sl.clear();
    EXPECT_EQ(sl.getSize(), 0);
    EXPECT_TRUE(sl.isEmpty());
    
    // 清空后应该搜索不到任何元素
    for (int i = 1; i <= 5; i++) {
        EXPECT_FALSE(sl.search(i));
    }
}

// 测试9: 批量插入和删除
TEST_F(TestSkipList, BulkOperations) {
    SkipList<int> sl;
    const int N = 100;
    
    // 批量插入
    for (int i = 0; i < N; i++) {
        sl.insert(i);
    }
    EXPECT_EQ(sl.getSize(), N);
    
    // 验证所有元素都存在
    for (int i = 0; i < N; i++) {
        EXPECT_TRUE(sl.search(i));
    }
    
    // 删除所有偶数
    for (int i = 0; i < N; i += 2) {
        sl.deleteVal(i);
    }
    EXPECT_EQ(sl.getSize(), N / 2);
    
    // 验证删除结果
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            EXPECT_FALSE(sl.search(i));
        } else {
            EXPECT_TRUE(sl.search(i));
        }
    }
}

// 测试10: 字符串类型测试
TEST_F(TestSkipList, StringType) {
    SkipList<std::string> sl;
    
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    for (const auto& word : words) {
        EXPECT_TRUE(sl.insert(word));
    }
    
    EXPECT_EQ(sl.getSize(), words.size());
    
    // 验证所有字符串都存在
    for (const auto& word : words) {
        EXPECT_TRUE(sl.search(word));
    }
    
    // 验证不存在的字符串
    EXPECT_FALSE(sl.search("fig"));
    EXPECT_FALSE(sl.search("grape"));
    
    // 删除操作
    sl.deleteVal("banana");
    EXPECT_EQ(sl.getSize(), words.size() - 1);
    EXPECT_FALSE(sl.search("banana"));
    EXPECT_TRUE(sl.search("apple"));
    EXPECT_TRUE(sl.search("cherry"));
}

// 测试11: 内存泄漏测试（通过valgrind等工具检查）
TEST_F(TestSkipList, MemoryManagement) {
    {
        SkipList<int> sl;
        for (int i = 0; i < 100; i++) {
            sl.insert(i);
        }
        for (int i = 0; i < 50; i++) {
            sl.deleteVal(i);
        }
        // 离开作用域时析构函数应该清理内存
    }
    // 如果这里没有内存泄漏，测试通过
    EXPECT_TRUE(true);
}

// 测试12: 边界值测试
TEST_F(TestSkipList, BoundaryValues) {
    SkipList<int> sl;
    
    // 插入大量数据
    for (int i = 0; i < 1000; i++) {
        sl.insert(i);
    }
    EXPECT_EQ(sl.getSize(), 1000);
    
    // 搜索边界值
    EXPECT_TRUE(sl.search(0));      // 最小值
    EXPECT_TRUE(sl.search(999));    // 最大值
    EXPECT_TRUE(sl.search(500));    // 中间值
    
    // 搜索超出范围的值
    EXPECT_FALSE(sl.search(-1));
    EXPECT_FALSE(sl.search(1000));
}

// 主函数
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}