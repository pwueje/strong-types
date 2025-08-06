# Copyright 2025 Philipp Jeske
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LINKER_TYPE LLD)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("StrongTypes"
		VERSION 0.1
		DESCRIPTION "Experiments for strong types in C++"
		LANGUAGES CXX
)

option(BUILD_TESTING "Build the testing tree" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_cmake")
include(ClangTidy)
include(BuildProperties)
include(Coverage)

if (BUILD_TESTING)
	include(CTest)
	include(Catch)
endif()

add_subdirectory(strong_types)
