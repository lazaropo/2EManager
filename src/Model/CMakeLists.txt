add_library(model STATIC
    Combatant.h
    CommandBase.h
    CommandsCreator.h
    CommandsImplementation.h
    CommandsImplementation/HarmCommand.h
    CommandsImplementation/HealCommand.h
    CommandsImplementation/MassHarmCommand.h
    CommandsImplementation/MassHealCommand.h
    CommandsImplementation/DecreaseMaxHpCommand.h


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

    SubjectBase.cpp
    Combatant.cpp
    CommandBase.cpp
    EffectBase.cpp
    MediatorInterface.cpp
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
    CommandsImplementation/DecreaseMaxHpCommand.cpp

    EffectExecutor.cpp
    SimpleEffectBuilder.cpp

)

target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(model PRIVATE
#    Boost::archieve
    Boost::serialization
   Boost::container
)

# if(NOT DEFINED _BOOST_SERIALIZATION_TXT_ AND NOT DEFINED _BOOST_SERIALIZATION_XML_)
# qt_add_resources(model textresources
#     PREFIX "/Saved_info"
#     FILES ../Saved_info/info.txt
# )
# endif()




