#set(__PATH_REVERSE_POLISH_NOTATION__ = "${CMAKE_CURRENT_SOURCE_DIR}/h")

add_library(ReversePolishNotation STATIC
#    s21_calc.h
    s21_list_funcs.c
    s21_parsers_definisions.c
    s21_calc.c
    s21_main_calc_function.c
)


include(GNUInstallDirs)
target_sources(ReversePolishNotation PUBLIC s21_calc.h)

target_link_directories(ReversePolishNotation INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# target_include_directories(ReversePolishNotation PUBLIC
#     "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
#     "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# install(TARGETS ReversePolishNotation
#         EXPORT ReversePolishNotationTargets
#         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#         INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# install(FILES s21_calc.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install(EXPORT ReversePolishNotationTargets
#         FILE ReversePolishNotationTargets.cmake
#         NAMESPACE ::
#         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ReversePolishNotation
# )

# install(EXPORT ReversePolishNotationTargets DESTINATION ../CommandDialog/)

# include(GenerateExportHeader)
# set(reverse_polish_notation_file_name "ReversePolishNotation_shared.h")

# if(NOT BUILD_SHARED_LIBS)
#     set(reverse_polish_notation_file_name "ReversePolishNotation_static.h")
# endif()

#generate_export_header(ReversePolishNotation REVERSE_POLISH_NOTATION_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/${reverse_polish_notation_file_name})

# target_compile_definitions(ReversePolishNotation
#     PUBLIC
#         "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:MYLIB_STATIC_DEFINE")
