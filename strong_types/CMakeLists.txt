# Copyright 2025 Philipp Jeske
# SPDX-License-Identifier: MIT

set(component "strong_types")
add_library(${component} INTERFACE)
add_library(strong_types::strong_types ALIAS ${component})

add_subdirectory(include/pjexx)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

target_include_directories(${component}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
