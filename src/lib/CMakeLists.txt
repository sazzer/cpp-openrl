PROJECT (OPENRL_LIB)

FILE(GLOB_RECURSE Sources "main/*.cpp")
FILE(GLOB_RECURSE Tests "test/*.cpp")
FILE(GLOB_RECURSE Integrations "integration/*.cpp")

ADD_LIBRARY(openrl_lib STATIC ${Sources})
add_cppcheck(openrl_lib)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/main/")
INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(openrl_lib ${CURSES_LIBRARIES})
TARGET_LINK_LIBRARIES(openrl_lib ${LIBPNG_LIBRARIES})

STRING(REPLACE ";" " " TestsAsString "${Tests}")
IF (NOT "${TestsAsString}" STREQUAL "")
    ADD_EXECUTABLE(lib_test ${Tests})
    TARGET_LINK_LIBRARIES(lib_test openrl_lib)

    ENABLE_TESTING()
    ADD_TEST(OPENRL_LIB lib_test)
ENDIF()

STRING(REPLACE ";" " " IntegrationsAsString "${Integrations}")
IF (NOT "${IntegrationsAsString}" STREQUAL "")
    FOREACH(file ${Integrations})
        GET_FILENAME_COMPONENT(integration "${file}" NAME_WE)
        ADD_EXECUTABLE(lib_integration_${integration} ${file})
        TARGET_LINK_LIBRARIES(lib_integration_${integration} openrl_lib)
    ENDFOREACH()
ENDIF()
