cmake_minimum_required(VERSION 3.12)

# プロジェクト名と使用するC++のバージョンを設定
project(ForcesBenchmark)

# C++17またはC++20を指定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 実行ファイルを指定
add_executable(ForcesBenchmark main.cpp)

