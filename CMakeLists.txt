cmake_minimum_required(VERSION 3.16)

project(Manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_GENERATOR_PLATFORM "x64")
set(VCPKG_TARGET_TRIPLET "x64-windows")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
#set(Boost_NO_SYSTEM_PATHS ON)


set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(Boost_DEBUG ON)

set(BOOST_LOG_DYN_LINK ON)
set(BOOST_LOG_SETUP_DYN_LINK ON)
set(BOOST_STACKTRACE_DYN_LINK ON)
set(BOOST_SERIALIZATION_DYN_LINK ON)


set(BOOST_STACKTRACE_ENABLE_BACKTRACE OFF)
set(BOOST_STACKTRACE_USE_WINDBG ON)
set(boost_stacktrace_from_exception  ON)

include( "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-windows-static/include)

#stacktrace
find_package(Boost COMPONENTS  log log_setup  system serialization REQUIRED)

# add warnings
# add_compile_options(
#         -Wall
#         -Wpedantic
#         -Wextra
#         -Wshadow
#         -Wformat=2
#         -Wstrict-overflow
#         -fvisibility=hidden
#         -fno-strict-aliasing
#         -Werror
#         -static
#         -static-libgcc
#         -static-libstdc++
# )


# add_compile_options(
#     /std:clatest
#     /std:c++17
# )



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

#set(CMAKE_STAGING_PREFIX  CMAKE_PREFIX_PATH)

set(CMAKE_INSTALL_PREFIX "C:/Users/roman/Desktop/2EManager/bin")

install(TARGETS ManagerPF2E
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

qt_generate_deploy_app_script(
    TARGET ManagerPF2E
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/ManagerPF2E.cmake")
file(GENERATE OUTPUT ${deploy_script} CONTENT "
include(\"${QT_DEPLOY_SUPPORT}\")

qt_deploy_runtime_dependencies(
    EXECUTABLE \"\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:ManagerPF2E>\"
    GENERATE_QT_CONF
)")

#install(EXPORT ReversePolishNotationTargets DESTINATION src/CommandDialog/)


