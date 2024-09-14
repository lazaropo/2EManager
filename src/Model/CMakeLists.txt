add_compile_definitions(model PRIVATE _USE_BOOST_SERIALIZE_=1 BOOST_ALL_NO_LIB=1   #// do not auto link, instead you link manually to your import libraries.
    BOOST_ALL_DYN_LINK=1 #// tells you will link to shared libraries
    BOOST_LOG_DYN_LINK=1 )#// explicitly says to link boost::log symbols to shared libraries)
# Define these macro to use saves
# _USE_BOOST_SERIALIZE_ macro
# _USE_TXT_READER_ macro

# set (BOOST_ROOT "C:/boost/") # Путь к библиотеке Boost

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

set (BOOST_INCLUDE_LIBRARIES serialize)

# include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package (Boost 1.82)

# SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/boost/boost_1_72_0")
# SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/boost/boost_1_72_0/lib")

#find_package(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${BOOST_INCLUDEDIR})
ENDIF()

# set(BOOST_INCLUDE_DIRS "C:/boost_1_82_0/boost_mingw_530/include/boost-1_82")
# set(Boost_LIBRARY_DIRS "C:/Program Files/boost/boost_1_82_0/lib/")

# include_directories("C:/Program Files/boost/boost_1_82_0")
# include_directories("C:/Program Files/boost/boost_1_82_0/libs/")
# link_directories("C:/Program Files/boost/boost_1_82_0/libs/")
# link_directories("C:/Program Files/boost/boost_1_82_0")

include_directories (SYSTEM ${BOOST_INCLUDEDIR})

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

target_link_libraries(model PRIVATE  ${Boost_LIBRARIES})#${Boost_LIBRARY_DIRS})# boost_serialization boost_system)

qt_add_resources(model textresources
    PREFIX "/Saved_info"
    FILES ../Saved_info/info.txt
)

#find_library(Boost_serialization "C:/boost/include/boost-1_82/boost/serialization/*.hpp")

# include_directories(SYSTEM
#     "C:/boost/include/boost-1_82/boost/"
#     "C:/boost/include/boost-1_82/boost/serialization/"
#     "C:/boost/include/boost-1_82/boost/serialization/detail/"
#     "C:/boost/include/boost-1_82/boost/archive/"
#     "C:/boost/include/boost-1_82/boost/archive/detail/"
#     "C:/boost/include/boost-1_82/boost/archive/impl/"
#     "C:/boost/include/boost-1_82/boost/archive/iterators/"
# )

#target_link_libraries (model PRIVATE ${Boost_LIBRARIES})# boost_iostreams boost_serialization) # подключаем библиотеку
#target_link_libraries (model PRIVATE ${Boost_serialization})

target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})






