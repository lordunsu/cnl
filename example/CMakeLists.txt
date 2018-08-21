# This file is only here to develop the example code.
# If you want to use the examples to learn how to use CNL,
# use the files in the individual sub-folders.

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
if (COMPILER_SUPPORTS_CXX17)
    add_executable(MullersRecurrence "mullers_recurrence/main.cpp")
    target_compile_features(MullersRecurrence PUBLIC cxx_variable_templates)
    target_compile_options(MullersRecurrence PRIVATE "-std=c++17")
    target_compile_definitions(MullersRecurrence PRIVATE "CNL_USE_INT128")
    target_link_libraries(MullersRecurrence Cnl "${linker_flags}")
    target_include_directories(MullersRecurrence PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
    add_test(Test-MullersRecurrence MullersRecurrence)

    add_executable(Tau "tau/main.cpp")
    target_compile_options(Tau PRIVATE "-std=c++17")
    target_link_libraries(Tau Cnl "${linker_flags}")
    target_include_directories(Tau PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
    add_test(Test-Tau Tau)
endif (COMPILER_SUPPORTS_CXX17)