cmake_minimum_required(VERSION 3.16)

project(commanddialog LANGUAGES C CXX)

set(INCLUDE_DIR ../Model/include)

qt_add_library(commanddialog STATIC

    ../ReversePolishNotation/s21_calc.c
    ../ReversePolishNotation/s21_list_funcs.c
    ../ReversePolishNotation/s21_main_calc_function.c
    ../ReversePolishNotation/s21_parsers_definisions.c

    ../ReversePolishNotation/s21_calc.h

    commanddialog.h
    commanddialog.cpp
    commanddialog.ui
)

include_directories(../ReversePolishNotation)

target_link_libraries(commanddialog PRIVATE Model_lib Qt6::Core Qt6::Widgets Boost::serialization )
target_include_directories(commanddialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIR})






