#add_compile_definitions(__PATH_REVERSE_POLISH_NOTATION__="${__PATH_REVERSE_POLISH_NOTATION__}")
cmake_minimum_required(VERSION 3.16)

project(${project} LANGUAGES C CXX)


qt_add_library(commanddialog STATIC
#    commanddialog.h
    commanddialog.cpp
    commanddialog.ui
    ../ReversePolishNotation/s21_calc.c
    ../ReversePolishNotation/s21_list_funcs.c
    ../ReversePolishNotation/s21_main_calc_function.c
    ../ReversePolishNotation/s21_parsers_definisions.c
)


#target_sources(combatantdialog PUBLIC commanddialog.h)

#target_include_directories(commanddialog PRIVATE ReversePolishNotation)

target_link_libraries(commanddialog PRIVATE Qt6::Core Qt6::Widgets Boost::serialization)# ReversePolishNotation)
target_include_directories(commanddialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






