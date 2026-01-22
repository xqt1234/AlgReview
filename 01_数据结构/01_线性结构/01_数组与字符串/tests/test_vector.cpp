#include "Vector.hpp"
#include <gtest/gtest.h>
#include <iostream>
class vectorTest : public ::testing::Test
{
public:
private:
};

/** 测试构造 */
TEST_F(vectorTest, 测试默认构造)
{
    Vector<int> v1;
    EXPECT_EQ(v1.size(), 0);
}

TEST_F(vectorTest, 测试列表构造)
{
    Vector<int> v2({ 1, 2, 3, 4 });
    EXPECT_EQ(v2.size(), 4);
    EXPECT_EQ(v2[3], 4);
}

TEST_F(vectorTest, 测试拷贝构造)
{
    Vector<int> v2 { 1, 2, 3, 4 };
    Vector<int> v3(v2);
    EXPECT_EQ(v3.size(), 4);
    EXPECT_EQ(v3[3], 4);

    Vector<int> v4(Vector<int>({ 1, 2, 3, 4, 5 }));
    EXPECT_EQ(v4.size(), 5);
    EXPECT_EQ(v4[4], 5);
}

TEST_F(vectorTest, 测试移动构造)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    Vector<int> v4(std::move(v1));
    EXPECT_EQ(v4.size(), 5);
    EXPECT_EQ(v4[4], 5);
}

/** 测试属性 */
TEST_F(vectorTest, 测试属性)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.capacity(), 5);
}

/** 测试功能 */

TEST_F(vectorTest, 测试修改预设空间大小reserve)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    EXPECT_EQ(v1.capacity(), 5);
    v1.reserve(10);
    EXPECT_EQ(v1.capacity(), 10);
}

TEST_F(vectorTest, 测试修改元素个数resize)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    EXPECT_EQ(v1.capacity(), 5);
    v1.resize(10);
    EXPECT_EQ(v1.size(), 10);
}

TEST_F(vectorTest, 添加元素)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    v1.push_back(6);
    EXPECT_EQ(v1[5], 6);
}

TEST_F(vectorTest, 移除某个位置元素)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    v1.erase(1);
    EXPECT_EQ(v1[1], 3);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1[2], 4);
    EXPECT_EQ(v1[3], 5);
}

TEST_F(vectorTest, 获取元素)
{
    Vector<int> v1({ 1, 2, 3, 4, 5 });
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 5);
}
