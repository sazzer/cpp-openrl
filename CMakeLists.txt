CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
PROJECT (OPENRL)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
INCLUDE("cmake/CXX11.cmake")
INCLUDE("cmake/CppcheckTargets.cmake")

SET (OPENRL_VERSION_MAJOR 1)
SET (OPENRL_VERSION_MINOR 0)
SET (OPENRL_VERSION_MICRO 0)

#------------------------------------------------------------------------------
# Ensure that we are using a C++11 Compliant Compiler
#------------------------------------------------------------------------------
check_for_cxx11_compiler(CXX11_COMPILER)
IF (CXX11_COMPILER)
    enable_cxx11()
ENDIF()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pedantic-errors -Wextra -Werror -Wno-unused-parameter")
endif()

#------------------------------------------------------------------------------
# Required CPM Setup - no need to modify - See: https://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm_packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
  message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
    RESULT_VARIABLE error_code
    OUTPUT_QUIET ERROR_QUIET)
  if(error_code)
    message(FATAL_ERROR "CPM failed to get the hash for HEAD")
  endif()
endif()
include(${CPM_DIR}/CPM.cmake)

#------------------------------------------------------------------------------
# Set up any library dependencies that we are going to need
#------------------------------------------------------------------------------
FIND_PACKAGE(cppcheck)

CPM_Finish()

#------------------------------------------------------------------------------
# Actually set up the rest of the build
#------------------------------------------------------------------------------
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/include/config.h.in" "${PROJECT_BINARY_DIR}/include/config.h")

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/deps/bandit")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")

ENABLE_TESTING()

ADD_SUBDIRECTORY("src/lib")
ADD_SUBDIRECTORY("src/main")
