#include "queue.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>

class TestDeque : public testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// 测试1: 默认构造函数
TEST_F(TestDeque, DefaultConstructor) {
    Deque<int> dq;
    EXPECT_TRUE(dq.empty());
    EXPECT_EQ(dq.size(), 0);
}

// 测试2: 基本push_front
TEST_F(TestDeque, BasicPushFront) {
    Deque<int> dq;
    
    dq.push_front(1);
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 1);
    
    dq.push_front(2);
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 1);
    
    dq.push_front(3);
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq.front(), 3);
    EXPECT_EQ(dq.back(), 1);
}

// 测试3: 基本push_back
TEST_F(TestDeque, BasicPushBack) {
    Deque<int> dq;
    
    dq.push_back(1);
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 1);
    
    dq.push_back(2);
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 2);
    
    dq.push_back(3);
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 3);
}

// 测试4: 混合push
TEST_F(TestDeque, MixedPush) {
    Deque<int> dq;
    
    dq.push_back(1);
    dq.push_front(2);
    dq.push_back(3);
    dq.push_front(4);
    
    EXPECT_EQ(dq.size(), 4);
    EXPECT_EQ(dq.front(), 4);
    EXPECT_EQ(dq.back(), 3);
}

// 测试5: pop_front
TEST_F(TestDeque, PopFront) {
    Deque<int> dq = {1, 2, 3};
    
    dq.pop_front();
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 3);
    
    dq.pop_front();
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 3);
    EXPECT_EQ(dq.back(), 3);
    
    dq.pop_front();
    EXPECT_TRUE(dq.empty());
    EXPECT_EQ(dq.size(), 0);
}

// 测试6: pop_back
TEST_F(TestDeque, PopBack) {
    Deque<int> dq = {1, 2, 3};
    
    dq.pop_back();
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 2);
    
    dq.pop_back();
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 1);
    
    dq.pop_back();
    EXPECT_TRUE(dq.empty());
    EXPECT_EQ(dq.size(), 0);
}

// 测试7: 混合pop
TEST_F(TestDeque, MixedPop) {
    Deque<int> dq = {1, 2, 3, 4};
    
    dq.pop_front();
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 4);
    
    dq.pop_back();
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 3);
    
    dq.pop_front();
    EXPECT_EQ(dq.front(), 3);
    EXPECT_EQ(dq.back(), 3);
    
    dq.pop_back();
    EXPECT_TRUE(dq.empty());
}

// 测试8: 空队列异常
TEST_F(TestDeque, EmptyException) {
    Deque<int> dq;
    
    EXPECT_THROW(dq.front(), std::out_of_range);
    EXPECT_THROW(dq.back(), std::out_of_range);
    EXPECT_THROW(dq.pop_front(), std::out_of_range);
    EXPECT_THROW(dq.pop_back(), std::out_of_range);
    
    dq.push_front(1);
    dq.pop_front();
    EXPECT_THROW(dq.front(), std::out_of_range);
}

// 测试9: 单元素队列
TEST_F(TestDeque, SingleElement) {
    Deque<int> dq;
    
    dq.push_front(42);
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 42);
    EXPECT_EQ(dq.back(), 42);
    
    dq.pop_front();
    EXPECT_TRUE(dq.empty());
    
    dq.push_back(100);
    EXPECT_EQ(dq.size(), 1);
    EXPECT_EQ(dq.front(), 100);
    EXPECT_EQ(dq.back(), 100);
    
    dq.pop_back();
    EXPECT_TRUE(dq.empty());
}

// 测试10: 复杂类型
TEST_F(TestDeque, ComplexType) {
    Deque<std::string> dq;
    
    dq.push_back("Hello");
    dq.push_back("World");
    dq.push_front("Start");
    
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq.front(), "Start");
    EXPECT_EQ(dq.back(), "World");
    
    dq.pop_front();
    EXPECT_EQ(dq.front(), "Hello");
    EXPECT_EQ(dq.back(), "World");
}

// 测试11: 大量元素
TEST_F(TestDeque, LargeScale) {
    Deque<int> dq;
    
    // 头部插入1000个
    for (int i = 0; i < 1000; ++i) {
        dq.push_front(i);
    }
    EXPECT_EQ(dq.size(), 1000);
    EXPECT_EQ(dq.front(), 999);
    EXPECT_EQ(dq.back(), 0);
    
    // 清空
    while (!dq.empty()) {
        dq.pop_front();
    }
    EXPECT_TRUE(dq.empty());
    
    // 尾部插入1000个
    for (int i = 0; i < 1000; ++i) {
        dq.push_back(i);
    }
    EXPECT_EQ(dq.size(), 1000);
    EXPECT_EQ(dq.front(), 0);
    EXPECT_EQ(dq.back(), 999);
}

// 测试12: 边界情况
TEST_F(TestDeque, EdgeCases) {
    Deque<int> dq;
    
    // 交替前后操作
    dq.push_front(1);
    dq.push_back(2);
    dq.pop_front();
    dq.push_front(3);
    dq.pop_back();
    dq.push_back(4);
    
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 3);
    EXPECT_EQ(dq.back(), 4);
}

// 测试13: 析构函数测试
TEST_F(TestDeque, Destructor) {
    {
        Deque<int> dq;
        for (int i = 0; i < 100; ++i) {
            dq.push_back(i);
        }
        // 退出作用域，应该正确析构
    }
    // 没有内存泄漏
    EXPECT_TRUE(true);
}

// 测试14: 输出流测试
TEST_F(TestDeque, OutputStream) {
    Deque<int> dq;
    
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    
    std::ostringstream oss;
    oss << dq;
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("Deque[") != std::string::npos);
    EXPECT_TRUE(output.find("1") != std::string::npos);
    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
    
    // 测试空队列输出
    Deque<int> emptyDq;
    std::ostringstream oss2;
    oss2 << emptyDq;
    EXPECT_TRUE(oss2.str().find("Deque[]") != std::string::npos);
}

// 测试15: 顺序验证
TEST_F(TestDeque, OrderVerification) {
    Deque<int> dq;
    
    // 测试顺序
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);
    dq.push_front(-1);
    
    // 顺序应该是: -1, 0, 1, 2, 3
    std::vector<int> expected = {-1, 0, 1, 2, 3};
    
    for (int i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(dq.front(), expected[i]);
        dq.pop_front();
    }
    EXPECT_TRUE(dq.empty());
}

// 测试16: 前后同时操作
TEST_F(TestDeque, BothEndsSimultaneous) {
    Deque<int> dq;
    
    // 同时从两端添加
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);
    
    EXPECT_EQ(dq.size(), 4);
    
    // 同时从两端删除
    dq.pop_front();
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 3);
    
    dq.pop_back();
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 2);
    
    dq.pop_front();
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 2);
    
    dq.pop_back();
    EXPECT_TRUE(dq.empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}