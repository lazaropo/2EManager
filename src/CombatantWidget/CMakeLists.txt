qt_add_library(combatantwidget STATIC
    # ${PROJECT_SOURCE_DIR}/src/Model/Combatant.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/CommandsCreator.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/EffectDirector.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/Mediator.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/Model.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/SimpleEffect.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/TXTReader.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/CommandsImplementation/HarmCommand.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/CommandsImplementation/HealCommand.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/CommandsImplementation/MassHarmCommand.cpp
    # ${PROJECT_SOURCE_DIR}/src/Model/CommandsImplementation/MassHealCommand.cpp
    combatantwidget.cpp
    MyMenuWidget.cpp
    combatantwidget.ui
)
target_link_libraries(combatantwidget PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(combatantwidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


