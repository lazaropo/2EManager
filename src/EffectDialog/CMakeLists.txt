qt_add_library(EffectDialog STATIC
    EffectDialog.cpp
    EffectDialog.ui
)
target_link_libraries(EffectDialog PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(EffectDialog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

