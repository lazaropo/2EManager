PROJECT_ROOT_PATH = $${PWD}/

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG (debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/
INC_PATH = $${PROJECT_ROOT_PATH}/Model/
BUILD_PATH = $${PROJECT_ROOT_PATH}/build/

INCLUDEPATH += $${INC_PATH}/


linux-g++: QMAKE_CXXFLAGS += -std=c++17
