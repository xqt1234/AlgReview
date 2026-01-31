#include "stack.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

class TestStack : public testing::Test {
protected:
    void SetUp() override {
        // 在每个测试前执行
    }
    
    void TearDown() override {
        // 在每个测试后执行
    }
};

// 测试1: 默认构造函数
TEST_F(TestStack, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_GE(stack.capacity(), 2);
}

// 测试2: 指定容量构造函数
TEST_F(TestStack, CapacityConstructor) {
    Stack<int> stack(10);
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_GE(stack.capacity(), 10);
}

// 测试3: 初始化列表构造
TEST_F(TestStack, InitializerListConstructor) {
    Stack<int> stack = {1, 2, 3, 4, 5};
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}

// 测试4: 复制构造函数
TEST_F(TestStack, CopyConstructor) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2(stack1);
    
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack1.top(), stack2.top());
    
    // 修改 stack1 不影响 stack2
    stack1.pop();
    EXPECT_EQ(stack1.size(), 2);
    EXPECT_EQ(stack2.size(), 3);
}

// 测试5: 移动构造函数
TEST_F(TestStack, MoveConstructor) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2(std::move(stack1));
    
    EXPECT_TRUE(stack1.empty());
    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
}

// 测试6: push 和 pop
TEST_F(TestStack, PushAndPop) {
    Stack<int> stack;
    
    stack.push(1);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);
    
    stack.push(2);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
    
    stack.push(3);
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);
    
    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
    
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);
    
    stack.pop();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

// 测试7: 移动版本的 push
TEST_F(TestStack, PushMove) {
    Stack<std::string> stack;
    
    std::string str1 = "Hello";
    stack.push(std::move(str1));
    EXPECT_TRUE(str1.empty());  // 已被移动
    EXPECT_EQ(stack.top(), "Hello");
    
    stack.push("World");
    EXPECT_EQ(stack.top(), "World");
}

// 测试8: 扩容测试
TEST_F(TestStack, ExpandTest) {
    Stack<int> stack(2);  // 初始容量2
    
    // 添加多个元素触发扩容
    for (int i = 1; i <= 10; ++i) {
        stack.push(i);
    }
    
    EXPECT_EQ(stack.size(), 10);
    EXPECT_EQ(stack.top(), 10);
    EXPECT_GE(stack.capacity(), 16);
}

// 测试9: 清空测试
TEST_F(TestStack, ClearTest) {
    Stack<int> stack = {1, 2, 3, 4, 5};
    
    EXPECT_EQ(stack.size(), 5);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    // 清空后可以继续使用
    stack.push(10);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);
}

// 测试10: 交换测试
TEST_F(TestStack, SwapTest) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2 = {4, 5, 6, 7};
    
    int size1 = stack1.size();
    int size2 = stack2.size();
    int top1 = stack1.top();
    int top2 = stack2.top();
    
    stack1.swap(stack2);
    
    EXPECT_EQ(stack1.size(), size2);
    EXPECT_EQ(stack2.size(), size1);
    EXPECT_EQ(stack1.top(), top2);
    EXPECT_EQ(stack2.top(), top1);
}

// 测试11: 反转测试
TEST_F(TestStack, ReverseTest) {
    // 测试空栈反转
    {
        Stack<int> emptyStack;
        emptyStack.reverse();
        EXPECT_TRUE(emptyStack.empty());
    }
    
    // 测试单元素栈
    {
        Stack<int> singleStack = {42};
        singleStack.reverse();
        EXPECT_EQ(singleStack.size(), 1);
        EXPECT_EQ(singleStack.top(), 42);
    }
    
    // 测试多元素栈
    {
        Stack<int> stack = {1, 2, 3, 4, 5};
        stack.reverse();
        
        EXPECT_EQ(stack.size(), 5);
        EXPECT_EQ(stack.top(), 1);  // 原来栈底的1现在在栈顶
        
        // 验证顺序
        std::vector<int> expected = {1, 2, 3, 4, 5};  // 从栈顶到底
        std::vector<int> actual;
        while (!stack.empty()) {
            actual.push_back(stack.top());
            stack.pop();
        }
        EXPECT_EQ(actual, expected);
    }
    
    // 测试反转两次恢复原状
    {
        Stack<int> stack = {1, 2, 3};
        std::vector<int> original;
        Stack<int> copy = stack;
        while (!copy.empty()) {
            original.push_back(copy.top());
            copy.pop();
        }
        
        stack.reverse();
        stack.reverse();
        
        std::vector<int> after;
        while (!stack.empty()) {
            after.push_back(stack.top());
            stack.pop();
        }
        EXPECT_EQ(after, original);
    }
}

// 测试12: 相等运算符
TEST_F(TestStack, EqualityOperator) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2 = {1, 2, 3};
    Stack<int> stack3 = {1, 2};
    Stack<int> stack4 = {1, 2, 4};
    
    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 == stack4);
    EXPECT_TRUE(stack1 != stack3);
    EXPECT_TRUE(stack1 != stack4);
}

// 测试13: 赋值运算符
TEST_F(TestStack, AssignmentOperator) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2 = {4, 5};
    
    stack2 = stack1;
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_TRUE(stack1 == stack2);
    
    // 自赋值测试
    stack1 = stack1;
    EXPECT_EQ(stack1.size(), 3);
}

// 测试14: 移动赋值运算符
TEST_F(TestStack, MoveAssignmentOperator) {
    Stack<int> stack1 = {1, 2, 3};
    Stack<int> stack2 = {4, 5};
    
    stack2 = std::move(stack1);
    EXPECT_TRUE(stack1.empty());
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
}

// 测试15: 异常测试
TEST_F(TestStack, ExceptionTest) {
    Stack<int> emptyStack;
    
    // 空栈pop应该抛出异常
    EXPECT_THROW(emptyStack.pop(), std::out_of_range);
    
    // 空栈top应该抛出异常
    EXPECT_THROW(emptyStack.top(), std::out_of_range);
    
    // 非空栈正常操作
    Stack<int> stack = {1};
    EXPECT_NO_THROW(stack.top());
    EXPECT_NO_THROW(stack.pop());
    EXPECT_THROW(stack.top(), std::out_of_range);
}

// 测试16: 复杂类型测试
TEST_F(TestStack, ComplexTypeTest) {
    Stack<std::string> stack;
    
    stack.push("Hello");
    stack.push("World");
    stack.push("!");
    
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), "!");
    
    stack.pop();
    EXPECT_EQ(stack.top(), "World");
    
    stack.reverse();
    EXPECT_EQ(stack.top(), "Hello");
}

// 测试17: 输出流运算符
TEST_F(TestStack, OutputOperator) {
    Stack<int> stack = {1, 2, 3};
    
    std::ostringstream oss;
    oss << stack;
    
    // 根据你的实现，输出可能是 "Stack[1, 2, 3]"
    // 或者 "Stack[3, 2, 1]" 取决于遍历顺序
    std::string output = oss.str();
    
    // 检查包含关键信息
    EXPECT_TRUE(output.find("Stack") != std::string::npos);
    EXPECT_TRUE(output.find("1") != std::string::npos);
    EXPECT_TRUE(output.find("2") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
}

// 测试18: 混合操作测试
TEST_F(TestStack, MixedOperations) {
    Stack<int> stack;
    
    // 混合各种操作
    for (int i = 1; i <= 5; ++i) {
        stack.push(i);
    }
    
    stack.pop();
    stack.reverse();
    stack.push(99);
    stack.reverse();
    
    EXPECT_EQ(stack.size(), 5);
    std::cout << stack << std::endl;
    // 验证最终顺序
    std::vector<int> expected = {4,3,2,1,99};
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(stack.top(), expected[i]);
        stack.pop();
    }
    EXPECT_TRUE(stack.empty());
}

// 测试19: 边界条件测试
TEST_F(TestStack, EdgeCaseTest) {
    // 最小容量测试
    Stack<int> stack1(2);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);  // 触发扩容
    EXPECT_EQ(stack1.size(), 3);
    
    // 大量元素测试
    Stack<int> stack2;
    for (int i = 0; i < 1000; ++i) {
        stack2.push(i);
    }
    EXPECT_EQ(stack2.size(), 1000);
    EXPECT_EQ(stack2.top(), 999);
    
    // 清空后再添加
    stack2.clear();
    stack2.push(42);
    EXPECT_EQ(stack2.size(), 1);
    EXPECT_EQ(stack2.top(), 42);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}