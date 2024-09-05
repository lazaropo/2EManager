qt_add_library(commanddialog STATIC
    commanddialog.cpp
    commanddialog.ui
)
target_link_libraries(commanddialog PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(commanddialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
