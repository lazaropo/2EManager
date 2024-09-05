cmake_minimum_required(VERSION 3.16)

project(ManagerPF2E VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_library(ManagerPF2E_static STATIC
    dragndropqwidget.cpp
    dragndropqwidget_commands.cpp
    managerwidget.cpp
)
target_link_libraries(ManagerPF2E_static
    PRIVATE
    Qt6::Core
   Qt6::Widgets
   Qt6::Gui
   model
    combatantdialog
    combatantwidget
    commanddialog
    commandicon
    EffectDialog
    valueinputdialog
    )

qt_add_executable(ManagerPF2E
    main.cpp)

target_link_libraries(ManagerPF2E
    PRIVATE Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    ManagerPF2E_static)

target_include_directories(ManagerPF2E_static
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties(ManagerPF2E PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)









