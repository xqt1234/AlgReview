#include "queue.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>

class TestQueue : public testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// 测试1: 默认构造函数
TEST_F(TestQueue, DefaultConstructor) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_GE(q.capacity(), 4);
}

// 测试2: 指定容量构造函数
TEST_F(TestQueue, CapacityConstructor) {
    Queue<int> q(10);
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_GE(q.capacity(), 10);
}

// 测试3: 基本入队出队测试
TEST_F(TestQueue, BasicEnqueueDequeue) {
    Queue<int> q;
    
    q.enqueue(1);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 1);
    
    q.enqueue(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 2);
    
    q.enqueue(3);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
    
    q.dequeue();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 3);
    
    q.dequeue();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 3);
    EXPECT_EQ(q.back(), 3);
    
    q.dequeue();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

// 测试4: 环形特性测试
TEST_F(TestQueue, CircularBehavior) {
    Queue<int> q(3);
    
    // 填满队列
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQ(q.size(), 3);
    EXPECT_TRUE(q.isFull());
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
    
    // 出队一个，制造空间
    q.dequeue();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 3);
    
    // 入队一个新元素，应该重用位置0
    q.enqueue(4);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 4);
    
    // 验证顺序
    EXPECT_EQ(q.front(), 2); q.dequeue();
    EXPECT_EQ(q.front(), 3); q.dequeue();
    EXPECT_EQ(q.front(), 4); q.dequeue();
    EXPECT_TRUE(q.empty());
}

// 测试5: 扩容测试
TEST_F(TestQueue, ExpandTest) {
    Queue<int> q(3);
    
    // 添加4个元素触发扩容
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    
    EXPECT_EQ(q.size(), 4);
    EXPECT_GE(q.capacity(), 4);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 4);
    
    // 继续添加更多元素
    for (int i = 5; i <= 10; ++i) {
        q.enqueue(i);
    }
    EXPECT_EQ(q.size(), 10);
    EXPECT_GE(q.capacity(), 10);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 10);
}

// 测试6: 扩容后保持顺序
TEST_F(TestQueue, ExpandMaintainsOrder) {
    Queue<int> q(3);
    
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();  // 移除1
    q.enqueue(3);
    q.enqueue(4);  // 触发扩容
    
    // 验证顺序
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 4);
    
    std::vector<int> expected = {2, 3, 4};
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(q.front(), expected[i]);
        q.dequeue();
    }
    EXPECT_TRUE(q.empty());
}

// 测试7: 异常测试
TEST_F(TestQueue, ExceptionTest) {
    Queue<int> q;
    
    // 空队列出队应该抛出异常
    EXPECT_THROW(q.dequeue(), std::out_of_range);
    
    // 空队列获取front应该抛出异常
    EXPECT_THROW(q.front(), std::out_of_range);
    
    // 空队列获取back应该抛出异常
    EXPECT_THROW(q.back(), std::out_of_range);
    
    // 非空队列正常操作
    q.enqueue(1);
    EXPECT_NO_THROW(q.front());
    EXPECT_NO_THROW(q.back());
    EXPECT_NO_THROW(q.dequeue());
    EXPECT_THROW(q.dequeue(), std::out_of_range);
}

// 测试8: 复杂类型测试
TEST_F(TestQueue, ComplexTypeTest) {
    Queue<std::string> q;
    
    q.enqueue("Hello");
    q.enqueue("World");
    q.enqueue("!");
    
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), "Hello");
    EXPECT_EQ(q.back(), "!");
    
    q.dequeue();
    EXPECT_EQ(q.front(), "World");
    EXPECT_EQ(q.back(), "!");
    
    q.dequeue();
    EXPECT_EQ(q.front(), "!");
    EXPECT_EQ(q.back(), "!");
}

// 测试9: 输出流运算符测试
TEST_F(TestQueue, OutputOperatorTest) {
    Queue<int> q;
    
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    std::ostringstream oss;
    oss << q;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("show Queue") != std::string::npos);
    EXPECT_TRUE(output.find("1") != std::string::npos);
    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    
    // 测试空队列输出
    Queue<int> emptyQ;
    std::ostringstream oss2;
    oss2 << emptyQ;
    EXPECT_TRUE(oss2.str().find("show Queue[]") != std::string::npos);
}

// 测试10: 混合操作测试
TEST_F(TestQueue, MixedOperations) {
    Queue<int> q(3);
    
    // 混合操作
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();  // 移除1
    q.enqueue(3);
    q.enqueue(4);  // 触发扩容
    q.enqueue(5);
    q.dequeue();  // 移除2
    q.enqueue(6);
    
    // 验证最终状态
    EXPECT_EQ(q.size(), 4);
    
    // 验证顺序: 3, 4, 5, 6
    EXPECT_EQ(q.front(), 3);
    EXPECT_EQ(q.back(), 6);
    
    q.dequeue();
    EXPECT_EQ(q.front(), 4);
    EXPECT_EQ(q.back(), 6);
    
    q.dequeue();
    EXPECT_EQ(q.front(), 5);
    EXPECT_EQ(q.back(), 6);
    
    q.dequeue();
    EXPECT_EQ(q.front(), 6);
    EXPECT_EQ(q.back(), 6);
    
    q.dequeue();
    EXPECT_TRUE(q.empty());
}

// 测试11: 大量元素测试
TEST_F(TestQueue, LargeScaleTest) {
    Queue<int> q;
    
    // 添加大量元素
    for (int i = 0; i < 1000; ++i) {
        q.enqueue(i);
    }
    
    EXPECT_EQ(q.size(), 1000);
    EXPECT_EQ(q.front(), 0);
    EXPECT_EQ(q.back(), 999);
    
    // 验证顺序
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(q.front(), i);
        q.dequeue();
    }
    
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

// 测试12: 边界条件测试
TEST_F(TestQueue, EdgeCases) {
    // 最小容量测试
    Queue<int> q(1);
    q.enqueue(1);
    EXPECT_TRUE(q.isFull());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 1);
    
    // 扩容测试
    q.enqueue(2);
    EXPECT_GE(q.capacity(), 2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 2);
    
    // 清空后重新使用
    while (!q.empty()) {
        q.dequeue();
    }
    
    q.enqueue(3);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 3);
    EXPECT_EQ(q.back(), 3);
}

// 测试13: 清空队列测试
TEST_F(TestQueue, ClearByDequeue) {
    Queue<int> q;
    
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    
    EXPECT_EQ(q.size(), 5);
    EXPECT_EQ(q.front(), 0);
    EXPECT_EQ(q.back(), 4);
    
    // 手动清空
    while (!q.empty()) {
        q.dequeue();
    }
    
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    
    // 清空后可以继续使用
    q.enqueue(10);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);
}

// 测试14: 空队列满队列判断
TEST_F(TestQueue, EmptyAndFullTest) {
    Queue<int> q(3);
    
    EXPECT_TRUE(q.empty());
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(1);
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(2);
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(3);
    EXPECT_FALSE(q.empty());
    EXPECT_TRUE(q.isFull());
    
    q.dequeue();
    EXPECT_FALSE(q.empty());
    EXPECT_FALSE(q.isFull());
}

// 测试15: 容量变化测试
TEST_F(TestQueue, CapacityChanges) {
    Queue<int> q(2);
    
    EXPECT_EQ(q.capacity(), 2);
    
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);  // 触发扩容
    
    EXPECT_GE(q.capacity(), 3);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
    
    // 验证扩容后数据正确
    q.dequeue();
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 3);
    
    q.dequeue();
    EXPECT_EQ(q.front(), 3);
    EXPECT_EQ(q.back(), 3);
}

// 测试16: isFull 正确性测试
TEST_F(TestQueue, IsFullCorrectness) {
    Queue<int> q(3);
    
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(1);
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(2);
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(3);
    EXPECT_TRUE(q.isFull());
    
    q.dequeue();
    EXPECT_FALSE(q.isFull());
    
    q.enqueue(4);
    EXPECT_TRUE(q.isFull());
}

// 测试17: 连续扩容测试
TEST_F(TestQueue, ContinuousExpand) {
    Queue<int> q(2);
    
    for (int i = 1; i <= 100; ++i) {
        q.enqueue(i);
    }
    
    EXPECT_EQ(q.size(), 100);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 100);
    
    // 验证所有元素
    for (int i = 1; i <= 100; ++i) {
        EXPECT_EQ(q.front(), i);
        q.dequeue();
    }
    EXPECT_TRUE(q.empty());
}

// int main(int argc, char** argv) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }