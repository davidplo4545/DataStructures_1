cmake_minimum_required(VERSION 3.24)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 TreeNode.cpp AVLTree.cpp Player.cpp Player.h Tests/PlayerTests.cpp Tests/AVLTreeTests.cpp Team.cpp Team.h Exception.h worldcup23a1.cpp worldcup23a1.h main23a1.cpp)
