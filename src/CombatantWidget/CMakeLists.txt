qt_add_library(combatantwidget STATIC
    combatantwidget.cpp
    MyMenuWidget.cpp
    combatantwidget.ui
)
target_link_libraries(combatantwidget PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(combatantwidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


