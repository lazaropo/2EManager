# qt_add_library(combatantwidget STATIC
#     combatantwidget.cpp
#     MyMenuWidget.cpp
#     combatantwidget.h
#     MyMenuWidget.h
#     EffectListWidgetItem.h
#     combatantwidget.ui
# )

set(LIB_SOURCES
    src/combatantwidget.cpp
    src/MyMenuWidget.cpp
    src/combatantwidget.ui
)

set(LIB_HEADERS include/combatantwidget.h
    include/MyMenuWidget.h
    include/EffectListWidgetItem.h)

set(INCLUDE_DIR ../Model/include)

# Создаем статическую библиотеку
add_library(combatantwidget STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Указываем include-директорию

target_link_libraries(combatantwidget PRIVATE
    Model_lib
    Qt6::Core Qt6::Widgets Qt6::Gui
    Boost::log
    Boost::log_setup
    Boost::system
    Boost::serialization)
target_include_directories(combatantwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${INCLUDE_DIR})

#target_include_directories(combatantwidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIR})


