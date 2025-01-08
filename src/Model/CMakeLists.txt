cmake_minimum_required(VERSION 3.10)
project(Model_lib)

set(LIB_SOURCES
    src/SubjectBase.cpp
    src/Combatant.cpp
    src/CommandBase.cpp
    src/EffectBase.cpp
    src/MediatorInterface.cpp
    src/CommandsCreator.cpp
    src/EffectDirector.cpp
    src/Mediator.cpp
    src/Model.cpp
    src/SimpleEffect.cpp
    src/TXTReader.cpp
    src/utility.cpp
    src/CommandsImplementation/HarmCommand.cpp
    src/CommandsImplementation/HealCommand.cpp
    src/CommandsImplementation/MassHarmCommand.cpp
    src/CommandsImplementation/MassHealCommand.cpp
    src/CommandsImplementation/DecreaseMaxHpCommand.cpp

    src/EffectExecutor.cpp
    src/SimpleEffectBuilder.cpp
)
set(LIB_HEADERS
    include/Combatant.h
    include/CommandBase.h
    include/CommandsCreator.h
    include/CommandsImplementation.h
    include/CommandsImplementation/HarmCommand.h
    include/CommandsImplementation/HealCommand.h
    include/CommandsImplementation/MassHarmCommand.h
    include/CommandsImplementation/MassHealCommand.h
    include/CommandsImplementation/DecreaseMaxHpCommand.h

    include/EffectBase.h
    include/EffectDirector.h
    include/EffectExecutor.h
    include/FileReaderBase.h
    include/Mediator.h
    include/MediatorInterface.h
    include/Model.h
    include/Controller.h
    include/SimpleEffect.h
    include/SimpleEffectBuilder.h
    include/SubjectBase.h
    include/TXTReader.h
    include/utility.h
)


# Создаем статическую библиотеку
add_library(Model_lib STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Указываем include-директорию
target_link_libraries(Model_lib PRIVATE
    Boost::log
    Boost::log_setup
    Boost::system
    Boost::serialization
    Boost::container
    Boost::filesystem
)
target_include_directories(Model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# if(NOT DEFINED _BOOST_SERIALIZATION_TXT_ AND NOT DEFINED _BOOST_SERIALIZATION_XML_)
# qt_add_resources(Model_lib textresources
#     PREFIX "/Saved_info"
#     FILES ../Saved_info/info.txt
# )
# endif()




