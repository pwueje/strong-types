# Copyright 2024 Philipp Jeske
# SPDX-License-Identifier: MIT

function(target_enable_clang_tidy target)
    find_program(CLANG-TIDY_PATH clang-tidy)

    if (CLANG-TIDY_PATH-NOTFOUND)
        message(WARNING "clang-tidy not found.")
    else()
        message(STATUS "Enabling clang-tidy for ${target}")
        set(CLANG_TIDY_CHECKS
            "bugprone-*"
            "clang-analyzer-*"
            "concurrency-*"
            "cppcoreguidelines-*"
            "modernize-*"
            "performance-*"
            "readability-*"
            "-modernize-use-trailing-return-type"
        )

        string(JOIN "," CLANG_TIDY_CHECK_STR ${CLANG_TIDY_CHECKS})
        set(CLANG_TIDY_COMMAND "${CLANG-TIDY_PATH}" "-checks=-*,--warnings-as-errors=*,${CLANG_TIDY_CHECK_STR}")

        set_target_properties(${target}
            PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
        )

        mark_as_advanced(CLANG-CLANG-TIDY_CHECK_STR)
    endif()
endfunction()