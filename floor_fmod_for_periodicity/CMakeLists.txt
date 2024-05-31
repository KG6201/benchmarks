cmake_minimum_required(VERSION 3.12)

# プロジェクト名と使用するC++のバージョンを設定
project(PiPeriodicityBenchmark)

# C++20を指定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# コンパイラごとの警告フラグと最適化フラグを設定
if(MSVC)
    # MSVC用の警告フラグと最適化フラグ
    add_compile_options(/W4 /O2)
else()
    # GCC/Clang用の警告フラグと最適化フラグ
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

# 実行ファイルを指定
add_executable(PiPeriodicityBenchmark main.cpp)
