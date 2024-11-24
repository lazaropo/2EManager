cmake_minimum_required(VERSION 3.16)

project(commanddialog LANGUAGES C CXX)

qt_add_library(commanddialog STATIC
    commanddialog.h
    commanddialog.cpp
    commanddialog.ui
    # ../ReversePolishNotation/s21_calc.h
    # ../ReversePolishNotation/s21_calc.c
    # ../ReversePolishNotation/s21_list_funcs.c
    # ../ReversePolishNotation/s21_main_calc_function.c
    # ../ReversePolishNotation/s21_parsers_definisions.c
)

target_link_libraries(commanddialog PRIVATE Qt6::Core Qt6::Widgets Boost::serialization ReversePolishNotation)
target_include_directories(commanddialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






