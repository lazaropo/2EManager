add_compile_definitions(model PRIVATE
    __CMAKE_IS_USED__="${PROJECT_SOURCE_DIR}/src/Saved_info/info.txt"
    _BOOST_SERIALIZATION_XML_
    _BOOST_SERIALIZATION_XML_FILEPATH_="record.xml"
)

add_library(model STATIC
    Combatant.h
    CommandBase.h
    CommandsCreator.h
    CommandsImplementation.h
    ComplexEffect.h
    ComplexEffectBuilder.h
    EffectBase.h
    EffectDirector.h
    EffectExecutor.h
    FileReaderBase.h
    Mediator.h
    MediatorInterface.h
    Model.h
    Controller.h
    SimpleEffect.h
    SimpleEffectBuilder.h
    SubjectBase.h
    TXTReader.h

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

target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(model PRIVATE
#    Boost::archieve
    Boost::serialization)

qt_add_resources(model textresources
    PREFIX "/Saved_info"
    FILES ../Saved_info/info.txt
)




