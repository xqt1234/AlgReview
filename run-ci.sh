# #!/bin/bash
# set -e  # 任何命令失败就退出

# # 向上查找.clang-format文件
# find_clang_config() {
#     local dir="$PWD"
#     while [[ "$dir" != "/" ]]; do
#         if [[ -f "$dir/.clang-format" ]]; then
#             echo "$dir/.clang-format"
#             return 0
#         fi
#         dir="$(dirname "$dir")"
#     done
#     return 1
# }

# CLANG_FORMAT_CONFIG=$(find_clang_config)
# CLANG_TIDY_CONFIG="${CLANG_FORMAT_CONFIG%.clang-format}.clang-tidy"
# cd ..

# echo "🔧 开始本地CI检查..."

# # 1. 编译检查
# echo "📦 编译检查..."
# mkdir -p build
# cd build
# cmake .. -DCMAKE_BUILD_TYPE=Debug
# make -j4
# cd ..

# # 2. 运行测试
# echo "🧪 运行单元测试..."
# ./bin/tests.bin --gtest_output=xml:test_results.xml

# # 3. 检查内存泄漏（Valgrind）
# echo "🛡️  内存泄漏检查..."
# if command -v valgrind &> /dev/null; then
#     valgrind --leak-check=full ./bin/tests.bin || true
#     echo "✅ 内存检查完成"
# else
#     echo "⚠️  Valgrind未安装，跳过内存检查"
#     echo "    Ubuntu安装: sudo apt-get install valgrind"
#     echo "    macOS安装: brew install valgrind"
# fi
# echo "✅ 内存检查完成"
# # 4. 代码风格检查
# echo "🎨 代码风格检查..."
# if command -v clang-format &> /dev/null; then
#     if [[ -n "$CLANG_FORMAT_CONFIG" ]]; then
#         echo "使用配置: $CLANG_FORMAT_CONFIG"
#         find include tests -name "*.hpp" -o -name "*.cpp" \
#             | xargs clang-format --dry-run -n --Werror --style=file:"$CLANG_FORMAT_CONFIG"
#     else
#         echo "⚠️  未找到.clang-format配置文件，使用默认规则"
#         find include tests -name "*.hpp" -o -name "*.cpp" \
#             | xargs clang-format --dry-run -n --Werror
#     fi
# else
#     echo "⚠️  clang-format未安装，跳过代码检查"
# fi


# # 5. 静态分析
# echo "🔍 静态分析..."
# if command -v clang-tidy &> /dev/null; then
#     if [[ -f "$CLANG_TIDY_CONFIG" ]]; then
#         echo "使用配置: $CLANG_TIDY_CONFIG"
#         find include tests \( -name "*.cpp" -o -name "*.hpp" \) \
#             | xargs -I {} clang-tidy --config-file="$CLANG_TIDY_CONFIG" {} -- -Iinclude -std=c++20
#     else
#         echo "⚠️  未找到.clang-tidy配置文件，跳过静态分析"
#     fi
# else
#     echo "⚠️  clang-tidy未安装，跳过静态分析"
# fi
# echo "✅ 本地CI检查完成！"

#!/bin/bash
set -e

# 配置默认值
: ${PROJECT_ROOT:="."}
: ${BUILD_DIR:="build"}
: ${BIN_DIR:="bin"}
: ${TEST_BIN:="tests.bin"}
: ${CMAKE_ARGS:="-DCMAKE_BUILD_TYPE=Debug"}
: ${INCLUDE_DIRS:="include tests"}

echo "🔧 开始本地CI检查 [项目: $(basename $PWD)]..."

# 1. 编译检查
echo "📦 编译检查..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake "$PROJECT_ROOT" $CMAKE_ARGS
make -j$(nproc)
cd ..

# 2. 运行测试
echo "🧪 运行单元测试..."
"$BIN_DIR/$TEST_BIN" --gtest_output=xml:test_results.xml

# 3. 内存检查
echo "🛡️  内存泄漏检查..."
if command -v valgrind &> /dev/null; then
    valgrind --leak-check=full "$BIN_DIR/$TEST_BIN" || true
    echo "✅ 内存检查完成"
else
    echo "⚠️  Valgrind未安装，跳过内存检查"
fi

# 4. 代码风格检查
echo "🎨 代码风格检查..."
if command -v clang-format &> /dev/null; then
    find_clang_config() {
        local dir="$PWD"
        while [[ "$dir" != "/" ]]; do
            [[ -f "$dir/.clang-format" ]] && echo "$dir/.clang-format" && return 0
            dir="$(dirname "$dir")"
        done
        return 1
    }
    
    CLANG_FORMAT_CONFIG=$(find_clang_config)
    if [[ -n "$CLANG_FORMAT_CONFIG" ]]; then
        echo "使用配置: $CLANG_FORMAT_CONFIG"
        find $INCLUDE_DIRS -name "*.hpp" -o -name "*.cpp" 2>/dev/null | \
            xargs -r clang-format --dry-run -n --Werror --style=file:"$CLANG_FORMAT_CONFIG"
    else
        echo "⚠️  未找到.clang-format配置文件"
    fi
fi

# 5. 静态分析
echo "🔍 静态分析..."
if command -v clang-tidy &> /dev/null; then
    if [[ -n "$CLANG_FORMAT_CONFIG" ]]; then
        CLANG_TIDY_CONFIG="${CLANG_FORMAT_CONFIG%.clang-format}.clang-tidy"
        if [[ -f "$CLANG_TIDY_CONFIG" ]]; then
            echo "使用配置: $CLANG_TIDY_CONFIG"
            find $INCLUDE_DIRS \( -name "*.cpp" -o -name "*.hpp" \) 2>/dev/null | \
                xargs -r -I {} clang-tidy --config-file="$CLANG_TIDY_CONFIG" {} -- -Iinclude -std=c++20
        fi
    fi
fi

echo "✅ 本地CI检查完成！"