add_compile_definitions(model PRIVATE _USE_BOOST_SERIALIZE_=1)
# Define these macro to use saves
# _USE_BOOST_SERIALIZE_ macro
# _USE_TXT_READER_ macro

set (BOOST_ROOT "C:/boost/") # Путь к библиотеке Boost


set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost 1.82)

include_directories (SYSTEM ${Boost_INCLUDE_DIR})

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


target_link_libraries (model ${Boost_LIBRARIES}) # подключаем библиотеку

target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_resources(model textresources
    PREFIX "/Saved_info"
    FILES ../Saved_info/info.txt
)




