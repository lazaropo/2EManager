add_compile_definitions(model PRIVATE __CMAKE_IS_USED__="${PROJECT_SOURCE_DIR}/src/Saved_info/info.txt")

add_library(model STATIC
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
    Combatant.h
    CommandBase.h
    CommandsCreator.h
    CommandsImplementation.h
    ComplexEffect.h
    ComplexEffectBuilder.h
    Controller.h
    EffectBase.h
    EffectDirector.h
    EffectExecutor.h
    FileReaderBase.h
    Mediator.h
    MediatorInterface.h
    Model.h
    SimpleEffect.h
    SimpleEffectBuilder.h
    SubjectBase.h
    TXTReader.h

)

target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_resources(model textresources
    PREFIX "/Saved_info"
    FILES ../Saved_info/info.txt
)




