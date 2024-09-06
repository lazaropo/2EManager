#add_compile_definitions(__PATH_REVERSE_POLISH_NOTATION__="${__PATH_REVERSE_POLISH_NOTATION__}")

qt_add_library(commanddialog STATIC
#    commanddialog.h
    commanddialog.cpp
    commanddialog.ui
)
# target_include_directories(commanddialog PUBLIC __PATH_REVERSE_POLISH_NOTATION__)
#include(GNUInstallDirs)
#add_library(ReversePolishNotation SHARED IMPORTED)
#include(${INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/ReversePolishNotation/ReversePolishNotationTargets.cmake)


target_sources(combatantdialog PUBLIC commanddialog.h)

target_link_libraries(commanddialog PRIVATE Qt6::Core Qt6::Widgets ReversePolishNotation)
target_include_directories(commanddialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(commanddialog PRIVATE ReversePolishNotation)




