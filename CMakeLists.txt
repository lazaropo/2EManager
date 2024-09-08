cmake_minimum_required(VERSION 3.16)

project(Manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
qt_standard_project_setup()

add_subdirectory(src/Model)
#add_subdirectory(src/ReversePolishNotation)
add_subdirectory(src/CombatantDialog)
add_subdirectory(src/CombatantWidget)
add_subdirectory(src/CommandDialog)
add_subdirectory(src/EffectDialog)
add_subdirectory(src/ValueInputDialog)
add_subdirectory(src/CommandIcon)
add_subdirectory(src/ManagerPF2E)

#install(EXPORT ReversePolishNotationTargets DESTINATION src/CommandDialog/)


