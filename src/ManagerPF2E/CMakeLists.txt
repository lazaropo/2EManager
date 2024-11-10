cmake_minimum_required(VERSION 3.16)

project(ManagerPF2E VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_GENERATOR_PLATFORM "x64")
# set(VCPKG_TARGET_TRIPLET "x64-windows")

# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME    OFF)
# set(Boost_NO_SYSTEM_PATHS ON)


# set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

# set(Boost_DEBUG ON)

# set(BOOST_LOG_DYN_LINK)
# set(BOOST_LOG_SETUP_DYN_LINK)
# include( "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

# set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-windows-static/include)


# find_package(Boost COMPONENTS log log_setup system REQUIRED)


#find_package(Boost COMPONENTS log  REQUIRED ) #)OMPONENTS boost_log)


# if(WIN32)
#     include(Windeployqt)
#     windeployqt(nitroshare-cli ${INSTALL_BIN_PATH})
# endif()

qt_add_library(ManagerPF2E_static STATIC
    managerwidget.h
    dragndropqwidget.h
    dragndropqwidget_commands.h
    dragndropqwidget.cpp
    dragndropqwidget_commands.cpp
    managerwidget.cpp
    managerwidget.ui
)

#target_compile_definitions(ManagerPF2E_static PRIVATE BOOST_LOG_DYN_LINK BOOST_LOG_SETUP_DYN_LINK)


target_link_libraries(ManagerPF2E_static
     PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    model
#    ReversePolishNotation
    combatantdialog
    combatantwidget
    commanddialog
    commandicon
    EffectDialog
    valueinputdialog

#    fmt::fmt
    Boost::log
#    Boost::stacktrace_from_exception
    Boost::log_setup
    Boost::system
    )

# include(GenerateExportHeader)
# generate_export_header(ManagerPF2E_static)

target_include_directories(ManagerPF2E_static
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )

qt_add_executable(ManagerPF2E
    main.cpp)

target_link_libraries(ManagerPF2E
    PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    ManagerPF2E_static

    Boost::log
    Boost::log_setup
    Boost::system
)

set_target_properties(ManagerPF2E PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)









