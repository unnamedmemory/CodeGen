cmake_minimum_required(VERSION 3.20)

project(helloworld)

# Find CMake file for Clang
find_package(Clang REQUIRED)

# Add path to LLVM modules
#set(CMAKE_MODULE_PATH
#  ${CMAKE_MODULE_PATH}
#  "${LLVM_CMAKE_DIR}"
#  )

# import LLVM CMake functions
#include(AddLLVM)

#set(LLVM_LINK_COMPONENTS
#  Support
#  )

add_executable(helloworld main.cpp)

target_link_libraries(helloworld
    LLVMSupport
    clang
    clangAST
    clangBasic
    clangDriver
    clangFormat
    clangLex
    clangParse
    clangSema
    clangFrontend
    clangTooling
    clangToolingCore
    clangRewrite
    clangRewriteFrontend
    clangASTMatchers
    )

include_directories("C:\\msys64\\clang64\\lib\\clang\\14.0.3\\include")

add_executable(test test.cpp)
