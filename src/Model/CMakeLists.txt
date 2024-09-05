add_compile_definitions(model PRIVATE __CMAKE_IS_USED__="${PROJECT_SOURCE_DIR}/src/Saved_info/info.txt")

qt_add_library(model STATIC
    Combatant.cpp
    CommandsCreator.cpp
    EffectDirector.cpp
    Mediator.cpp
    Model.cpp
    SimpleEffect.cpp
    TXTReader.cpp
    CommandsImplementation/HarmCommand.cpp
    CommandsImplementation/HealCommand.cpp
    CommandsImplementation/MassHarmCommand.cpp
    CommandsImplementation/MassHealCommand.cpp
)
#target_link_libraries(model PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_resources(model textresources
    PREFIX "/Saved_info"
    FILES ../Saved_info/info.txt
)




