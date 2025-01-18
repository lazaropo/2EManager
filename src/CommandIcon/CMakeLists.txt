qt_add_library(commandicon STATIC
    commandicon.cpp
    commandicon.ui
)

set(INCLUDE_DIR ../Model/include)

set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)

#add_custom_command(AUTORCC 1)

qt_add_resources(GENERATED_RESOURCES ${RESOURCES} )

target_sources(commandicon PUBLIC ${GENERATED_RESOURCES})

target_link_libraries(commandicon PRIVATE Model_lib Qt6::Core Qt6::Widgets Qt6::Gui Boost::serialization)
target_include_directories(commandicon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIR})

# qt_add_resources(commandicon "images"
#     PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/"../../misc/"
#     FILES images/harm.png images/harm_small.png images/heal.png images/heal_small.png
#     images/massharm.png images/massharm_small.png images/massheal.png images/massheal_small.png
#     images/decreasemaxhp.png images/decreasemaxhp_small.png
# )
