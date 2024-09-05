qt_add_library(valueinputdialog STATIC
    valueinputdialog.cpp
    valueinputdialog.ui
)
target_link_libraries(valueinputdialog PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(valueinputdialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

