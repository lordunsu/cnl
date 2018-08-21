project(MullersRecurrence)

cmake_minimum_required(VERSION 3.0)

add_executable(MullersRecurrence main.cpp)
target_compile_options(MullersRecurrence
        PRIVATE "-std=c++17" "-fsanitize=undefined" "-fsanitize-undefined-trap-on-error" "-fsanitize=address")
target_link_libraries(MullersRecurrence "-fsanitize=address")
if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    target_link_libraries(MullersRecurrence "--rtlib=compiler-rt" "-lgcc_eh")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    target_link_libraries(MullersRecurrence "-static-libasan")
else ()
    message(FATAL_ERROR "Compiler, ${CMAKE_CXX_COMPILER_ID}, is not supported.")
endif ()
target_compile_definitions(MullersRecurrence PRIVATE "CNL_USE_INT128")

find_package(Cnl REQUIRED)
include(${Cnl_DIR}/CnlConfig.cmake)

target_link_libraries(MullersRecurrence Cnl::Cnl)
get_target_property(Cnl_INCLUDE_DIR Cnl::Cnl INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(MullersRecurrence PRIVATE ${Cnl_INCLUDE_DIR})
