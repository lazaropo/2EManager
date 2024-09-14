cmake_minimum_required(VERSION 3.16)



project(ManagerPF2E VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


qt_add_library(ManagerPF2E_static STATIC
    managerwidget.h
    dragndropqwidget.h
    dragndropqwidget_commands.h
    dragndropqwidget.cpp
    dragndropqwidget_commands.cpp
    managerwidget.cpp
    managerwidget.ui
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

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost 1.82)
#find_package(Boost COMPONENTS serialization REQUIRED)
# set(BOOST_INCLUDE_DIRS "C:/boost_1_82_0/boost_mingw_530/include/boost-1_82")
# set(Boost_LIBRARY_DIRS "C:/boost_1_82_0/boost_mingw_530/lib")

# include_directories("C:/Program Files/boost/boost_1_82_0")
# include_directories("C:/Program Files/boost/boost_1_82_0/libs/")
# link_directories("C:/Program Files/boost/boost_1_82_0/libs/")
# link_directories("C:/Program Files/boost/boost_1_82_0")

# ${BOOST_DIR}


# include_directories("C:/boost_1_82_0/boost_mingw_530/include/boost-1_82")
# link_directories("C:/boost_1_82_0/boost_mingw_530/lib")

# include_directories (SYSTEM ${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    ManagerPF2E_static)
#    ${Boost_LIBRARIES})

target_include_directories(ManagerPF2E_static
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

set_target_properties(ManagerPF2E PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)









