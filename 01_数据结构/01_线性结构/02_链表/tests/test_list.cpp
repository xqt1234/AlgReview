#include "list.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

class TestList : public testing::Test {
protected:
    void SetUp() override {
        // 在每个测试前执行
    }
    
    void TearDown() override {
        // 在每个测试后执行
    }
};

// 测试1: 默认构造函数
TEST_F(TestList, DefaultConstructor) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

// 测试2: 初始化列表构造函数
TEST_F(TestList, InitializerListConstructor) {
    List<int> list = {1, 2, 3, 4, 5};
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
    
    // 验证顺序
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 3);
    EXPECT_EQ(list.at(3), 4);
    EXPECT_EQ(list.at(4), 5);
}

// 测试3: 复制构造函数
TEST_F(TestList, CopyConstructor) {
    List<int> list1 = {1, 2, 3};
    List<int> list2(list1);
    
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);
    
    // 验证内容
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(list1.at(i), list2.at(i));
    }
    
    // 验证是深拷贝
    list1.push_back(4);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 3);
}

// 测试4: 移动构造函数
TEST_F(TestList, MoveConstructor) {
    List<int> list1 = {1, 2, 3};
    List<int> list2(std::move(list1));
    
    EXPECT_EQ(list1.size(), 0);
    EXPECT_TRUE(list1.empty());
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

// 测试5: push_back
TEST_F(TestList, PushBack) {
    List<int> list;
    
    list.push_back(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
    
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
}

// 测试6: push_front
TEST_F(TestList, PushFront) {
    List<int> list = {2, 3};
    
    list.push_front(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.at(1), 2);
    
    list.push_front(0);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.at(1), 1);
}

// 测试7: insert
TEST_F(TestList, Insert) {
    List<int> list = {1, 3, 4};
    
    // 在位置1插入
    list.insert(1, 2);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 3);
    EXPECT_EQ(list.at(3), 4);
    
    // 在开头插入
    list.insert(0, 0);
    EXPECT_EQ(list.front(), 0);
    
    // 在末尾插入
    list.insert(list.size(), 5);
    EXPECT_EQ(list.back(), 5);
}

// 测试8: pop_back
TEST_F(TestList, PopBack) {
    List<int> list = {1, 2, 3};
    
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);
    
    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

// 测试9: pop_front
TEST_F(TestList, PopFront) {
    List<int> list = {1, 2, 3};
    
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

// 测试10: erase
TEST_F(TestList, Erase) {
    List<int> list = {1, 2, 3, 4, 5};
    
    // 删除中间元素
    list.erase(2);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 4);
    EXPECT_EQ(list.at(3), 5);
    
    // 删除头部
    list.erase(0);
    EXPECT_EQ(list.front(), 2);
    
    // 删除尾部
    list.erase(list.size() - 1);
    EXPECT_EQ(list.back(), 4);
}

// 测试11: removeVal
TEST_F(TestList, RemoveVal) {
    List<int> list = {1, 2, 2, 3, 2, 4};
    
    list.removeVal(2);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 3);
    EXPECT_EQ(list.at(2), 4);
    
    // 删除不存在的值
    list.removeVal(99);
    EXPECT_EQ(list.size(), 3);
}

// 测试12: reverse
TEST_F(TestList, Reverse) {
    // 测试空链表
    {
        List<int> list;
        list.reverse();
        EXPECT_TRUE(list.empty());
    }
    
    // 测试单元素链表
    {
        List<int> list = {1};
        list.reverse();
        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list.front(), 1);
    }
    
    // 测试多元素链表
    {
        List<int> list = {1, 2, 3, 4, 5};
        std::vector<int> original = {1, 2, 3, 4, 5};
        
        // 验证原始顺序
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(list.at(i), original[i]);
        }
        
        // 反转
        list.reverse();
        
        // 验证反转后顺序
        EXPECT_EQ(list.size(), 5);
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(list.at(i), original[4 - i]);
        }
        
        // 再反转一次应该恢复原状
        list.reverse();
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(list.at(i), original[i]);
        }
        
        // 验证头尾指针
        EXPECT_EQ(list.front(), 1);
        EXPECT_EQ(list.back(), 5);
    }
    
    // 测试偶数个元素
    {
        List<int> list = {1, 2, 3, 4};
        list.reverse();
        EXPECT_EQ(list.front(), 4);
        EXPECT_EQ(list.back(), 1);
        EXPECT_EQ(list.at(1), 3);
        EXPECT_EQ(list.at(2), 2);
    }
}

// 测试13: 边界情况下的reverse
TEST_F(TestList, ReverseEdgeCases) {
    // 测试两个元素
    {
        List<int> list = {1, 2};
        list.reverse();
        EXPECT_EQ(list.front(), 2);
        EXPECT_EQ(list.back(), 1);
    }
    
    // 测试大链表
    {
        List<int> list;
        for (int i = 0; i < 100; ++i) {
            list.push_back(i);
        }
        
        list.reverse();
        
        EXPECT_EQ(list.size(), 100);
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(list.at(i), 99 - i);
        }
    }
}

// 测试14: 复制赋值运算符
TEST_F(TestList, CopyAssignment) {
    List<int> list1 = {1, 2, 3};
    List<int> list2 = {4, 5};
    
    list2 = list1;
    
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);
    
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(list1.at(i), list2.at(i));
    }
    
    // 自赋值测试
    list1 = list1;
    EXPECT_EQ(list1.size(), 3);
}

// 测试15: 移动赋值运算符
TEST_F(TestList, MoveAssignment) {
    List<int> list1 = {1, 2, 3};
    List<int> list2 = {4, 5};
    
    list2 = std::move(list1);
    
    EXPECT_EQ(list1.size(), 0);
    EXPECT_TRUE(list1.empty());
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

// 测试16: clear
TEST_F(TestList, Clear) {
    List<int> list = {1, 2, 3, 4, 5};
    EXPECT_EQ(list.size(), 5);
    
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    
    // 清空后可以继续使用
    list.push_back(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
}

// 测试17: contain
TEST_F(TestList, Contain) {
    List<int> list = {1, 2, 3, 4, 5};
    
    EXPECT_TRUE(list.contain(1));
    EXPECT_TRUE(list.contain(3));
    EXPECT_TRUE(list.contain(5));
    EXPECT_FALSE(list.contain(0));
    EXPECT_FALSE(list.contain(6));
    EXPECT_FALSE(list.contain(999));
}

// 测试18: find
TEST_F(TestList, Find) {
    List<int> list = {10, 20, 30, 20, 40};
    
    EXPECT_EQ(list.find(10), 0);
    EXPECT_EQ(list.find(20), 1);  // 第一个出现的20
    EXPECT_EQ(list.find(30), 2);
    EXPECT_EQ(list.find(40), 4);
    EXPECT_EQ(list.find(50), -1);  // 不存在的元素
    EXPECT_EQ(list.find(999), -1);
}

// 测试19: 异常处理
TEST_F(TestList, ExceptionHandling) {
    List<int> list = {1, 2, 3};
    
    // 测试空链表的访问
    List<int> emptyList;
    EXPECT_THROW(emptyList.front(), std::out_of_range);
    EXPECT_THROW(emptyList.back(), std::out_of_range);
    EXPECT_THROW(emptyList.at(0), std::out_of_range);
    
    // 测试越界访问
    EXPECT_THROW(list.at(-1), std::out_of_range);
    EXPECT_THROW(list.at(3), std::out_of_range);
    EXPECT_THROW(list.at(100), std::out_of_range);
    
    // 测试越界插入
    EXPECT_THROW(list.insert(-1, 0), std::out_of_range);
    EXPECT_THROW(list.insert(4, 4), std::out_of_range);  // 允许在size位置插入
    
    // 测试越界删除
    EXPECT_THROW(list.erase(-1), std::out_of_range);
    EXPECT_THROW(list.erase(3), std::out_of_range);
    
    // 测试空链表的pop
    EXPECT_THROW(emptyList.pop_back(), std::out_of_range);
    EXPECT_THROW(emptyList.pop_front(), std::out_of_range);
}

// 测试20: 复杂类型
TEST_F(TestList, ComplexType) {
    List<std::string> list;
    
    list.push_back("Hello");
    list.push_back("World");
    list.push_back("!");
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), "Hello");
    EXPECT_EQ(list.back(), "!");
    EXPECT_TRUE(list.contain("World"));
    EXPECT_EQ(list.find("!"), 2);
    
    list.reverse();
    EXPECT_EQ(list.front(), "!");
    EXPECT_EQ(list.back(), "Hello");
}

// 测试21: 链表的连贯性测试
TEST_F(TestList, ConsistencyTest) {
    List<int> list = {1, 2, 3, 4, 5};
    
    // 记录操作顺序
    // 初始: {1, 2, 3, 4, 5}
    
    list.push_back(6);     // {1, 2, 3, 4, 5, 6}
    list.push_front(0);    // {0, 1, 2, 3, 4, 5, 6}
    list.insert(3, 99);    // 在索引3插入99 → {0, 1, 2, 99, 3, 4, 5, 6}
    list.pop_back();       // 删除6 → {0, 1, 2, 99, 3, 4, 5}
    list.pop_front();      // 删除0 → {1, 2, 99, 3, 4, 5}
    list.erase(2);         // 删除索引2(99) → {1, 2, 3, 4, 5}
    
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 3);
    EXPECT_EQ(list.at(3), 4);
    EXPECT_EQ(list.at(4), 5);
    
    // 反转后再操作
    list.reverse();        // {5, 4, 3, 2, 1}
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 1);
    
    list.push_back(100);   // {5, 4, 3, 2, 1, 100}
    list.push_front(-1);   // {-1, 5, 4, 3, 2, 1, 100}
    
    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list.front(), -1);
    EXPECT_EQ(list.back(), 100);
    
    // 验证具体顺序
    EXPECT_EQ(list.at(0), -1);
    EXPECT_EQ(list.at(1), 5);
    EXPECT_EQ(list.at(2), 4);
    EXPECT_EQ(list.at(3), 3);
    EXPECT_EQ(list.at(4), 2);
    EXPECT_EQ(list.at(5), 1);
    EXPECT_EQ(list.at(6), 100);
}

// int main(int argc, char** argv) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }