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
"$BIN_DIR/$TEST_BIN"

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