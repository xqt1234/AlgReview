#!/bin/bash
# 初始化学习环境脚本

echo "初始化算法学习环境..."

# 创建今日学习目录
TODAY=$(date +%Y%m%d)
mkdir -p "daily_practice/$TODAY"
cd "daily_practice/$TODAY"

# 创建今日学习文件
cat > plan.md << 'PLAN'
# 今日学习计划 $(date +%Y-%m-%d)

## 学习目标
1. 
2. 
3. 

## 时间安排
- 上午(9:00-12:00): 
- 下午(14:00-18:00): 
- 晚上(20:00-22:00): 

## 题目列表
1. 
2. 
3. 

## 总结与反思
- 收获：
- 不足：
- 改进：
PLAN

echo "今日学习目录已创建：daily_practice/$TODAY"
echo "请编辑 plan.md 文件制定今日计划"
