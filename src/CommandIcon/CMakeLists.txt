qt_add_library(commandicon STATIC
    commandicon.cpp
    commandicon.ui
)
target_link_libraries(commandicon PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(commandicon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


qt_add_resources(commandicon imageresources
    PREFIX "/images"
    FILES images/harm.png images/harm_small.png images/heal.png images/heal_small.png
    images/massharm.png images/massharm_small.png images/massheal.png images/massheal_small.png
)
