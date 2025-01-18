# qt_add_library(EffectDialog STATIC
#     EffectDialog.cpp
#     effectdialog.ui
# )

set(LIB_SOURCES
    src/EffectDialog.cpp
    src/effectdialog.ui
)

set(LIB_HEADERS
    include/EffectDialog.h
)

set(INCLUDE_DIR ../Model/include)

add_library(EffectDialog STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_link_libraries(EffectDialog PRIVATE Model_lib Qt6::Core Qt6::Widgets Boost::serialization)
target_include_directories(EffectDialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${INCLUDE_DIR})

