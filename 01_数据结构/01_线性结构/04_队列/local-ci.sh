#!/bin/bash
set -e  # 任何命令失败就退出

# 子项目配置
export BUILD_DIR="build"
export BIN_DIR="bin"
export TEST_BIN="tests.bin"
export CMAKE_ARGS="-DCMAKE_BUILD_TYPE=Debug"

# 查找通用脚本
current="$PWD"
while [[ "$current" != "/" ]]; do
    [[ -f "$current/run-ci.sh" ]] && {
        exec "$current/run-ci.sh"
    }
    current="$(dirname "$current")"
done

echo "错误: 未找到 run-ci.sh" >&2
exit 1