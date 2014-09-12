PROJECT (OPENRL_OPENRL)

FILE(GLOB_RECURSE Sources "main/*.cpp")
FILE(GLOB_RECURSE Tests "test/*.cpp")

ADD_EXECUTABLE(openrl ${Sources})
TARGET_LINK_LIBRARIES(openrl openrl_lib)

STRING(REPLACE ";" " " TestsAsString "${Tests}")
IF (NOT "${TestsAsString}" STREQUAL "")
    ADD_EXECUTABLE(openrl_test ${Tests})

    ENABLE_TESTING()
    ADD_TEST(OPENRL_OPENRL openrl_test)
ENDIF()
