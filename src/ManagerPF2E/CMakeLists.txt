cmake_minimum_required(VERSION 3.16)

project(ManagerPF2E VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SOURCES
    src/dragndropqwidget.cpp
    src/dragndropqwidget_commands.cpp
    src/managerwidget.cpp
    src/managerwidget.ui
    src/closebletextbrowser.cpp
)
set(LIB_HEADERS
    include/managerwidget.h
    include/dragndropqwidget.h
    include/dragndropqwidget_commands.h
    include/closebletextbrowser.h)
set(INCLUDE_DIR ../Model/include ../CombatantWidget/include ../CombatantDialog/include ../EffectDialog/include)


# Создаем статическую библиотеку
add_library(ManagerPF2E_static STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Указываем include-директорию
#target_link_libraries(combatantdialog PRIVATE Model_lib Qt6::Core Qt6::Widgets  Boost::serialization)
#target_include_directories(combatantdialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${INCLUDE_DIR})
# qt_add_library(ManagerPF2E_static STATIC
#     managerwidget.h
#     dragndropqwidget.h
#     dragndropqwidget_commands.h
#     dragndropqwidget.cpp
#     dragndropqwidget_commands.cpp
#     managerwidget.cpp
#     managerwidget.ui
# )

target_link_libraries(ManagerPF2E_static
    PRIVATE
    # Boost non-header-only libs
    Boost::log
    Boost::log_setup
    Boost::system
    Boost::serialization
    Boost::container
    Boost::filesystem
# QT moduls
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    # Custom libs
    Model_lib
#   ReversePolishNotation
    combatantdialog
    combatantwidget
    commanddialog
    commandicon
    EffectDialog
    valueinputdialog
    )

target_include_directories(ManagerPF2E_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${INCLUDE_DIR} )

qt_add_executable(ManagerPF2E
    main.cpp
    )

target_link_libraries(ManagerPF2E
PUBLIC
Boost::log
Boost::log_setup
Boost::system
Boost::serialization
Boost::container
Boost::filesystem

     Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Model_lib
    ManagerPF2E_static
)

target_include_directories(ManagerPF2E
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${INCLUDE_DIR})

set_target_properties(ManagerPF2E PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)









