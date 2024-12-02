cmake_minimum_required(VERSION 3.15)   # 设置 CMake 最低版本要求
project(EXPERIMENT)                      # 设置项目名称
set(CMAKE_TOOLCHAIN_FILE "/home/luster/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找并链接外部依赖（CURL 和 nlohmann_json）
find_package(CURL REQUIRED)             # 查找 CURL 库
find_package(nlohmann_json REQUIRED)  # 查找 nlohmann_json 库
# 创建可执行文件
add_executable(experiment homework.cpp)
target_link_libraries(experiment PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)