cmake_minimum_required(VERSION 3.16)

project(ManagerPF2E VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_GENERATOR_PLATFORM "x64")
set(VCPKG_TARGET_TRIPLET "x64-windows")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

set(Boost_NO_SYSTEM_PATHS ON)


set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

# set(boost_log_DIR "C:/boost_1_86_0_b1/lib64-msvc-14.3/cmake/boost_log-1.86.0/")
# set(boost_log_setup_DIR "C:/boost_1_86_0_b1/lib64-msvc-14.3/cmake/boost_log_setup-1.86.0/")

# set(BOOST_INCLUDE_LIBRARIES log)
# aux_source_directory(${BOOST_ROOT}/  EXCLUDE_FROM_ALL)
# aux_source_directory(C:/boost_1_82_0/stage/lib/ EXCLUDE_FROM_ALL)

# set(B_LIB "C:/boost_1_86_0_b1/lib64-msvc-14.3/cmake/boost_log-1.86.0/")

# if(__compiler_msvc)
#     add_compile_options(
#         /I "C:/boost_1_86_0_b1/lib64-msvc-14.3/cmake/boost_log-1.86.0/"
#     )
# endif()

set(Boost_DEBUG ON)

# if(Boost_FOUND)
#     include_directories(${BOOST_ROOT})
#     target_include_directories(ManagerPF2E_static PRIVATE ${BOOST_ROOT})
# endif()


## __NEW_START__

#set(Boost_USE_STATIC_LIBS ON)
set(BOOST_LOG_DYN_LINK)
set(BOOST_LOG_SETUP_DYN_LINK)
include( "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
#find_package(fmt CONFIG REQUIRED)

set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-windows-static/include)



## __NEW_END__


find_package(Boost COMPONENTS log log_setup REQUIRED)


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
    Boost::log_setup
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
)

set_target_properties(ManagerPF2E PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)









