qt_add_library(combatantdialog STATIC
    combatantdialog.h
    combatantdialog.cpp
    combatantdialog.ui
)
target_link_libraries(combatantdialog PRIVATE Qt6::Core Qt6::Widgets model Boost::serialization)
target_include_directories(combatantdialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

