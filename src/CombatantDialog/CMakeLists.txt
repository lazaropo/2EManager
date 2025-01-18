# qt_add_library(combatantdialog STATIC
#     combatantdialog.h
#     combatantdialog.cpp
#     combatantdialog.ui
# )

set(LIB_SOURCES
    src/combatantdialog.cpp
    src/combatantdialog.ui
)

set(LIB_HEADERS include/combatantdialog.h)

set(INCLUDE_DIR ../Model/include)

# Создаем статическую библиотеку
add_library(combatantdialog STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Указываем include-директорию
target_link_libraries(combatantdialog PRIVATE Model_lib Qt6::Core Qt6::Widgets  Boost::serialization)
target_include_directories(combatantdialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${INCLUDE_DIR})

