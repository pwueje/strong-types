# Copyright 2024 Philipp Jeske
# SPDX-License-Identifier: MIT

function(target_enable_coverage target)
    target_compile_options(${target} PRIVATE --coverage)
    target_link_options(${target} PRIVATE --coverage -lgcov)
endfunction()

function(target_generate_coverage_report target)
    message(CHECK_START "Looking for required tools")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    unset(COVERAGE_MISSING_TOOL)

    message(CHECK_START "Finding lcov")
    find_program(LCOV_PATH lcov)

    if (NOT LCOV_PATH)
        message(CHECK_FAIL "not found")
        list(APPEND COVERAGE_MISSING_TOOL "lcov")
    else()
        message(CHECK_PASS "found")
    endif()

    message(CHECK_START "Finding gcov")
    find_program(GCOV_PATH gcov)
    if (NOT GCOV_PATH)
        message(CHECK_FAIL "not found")
        list(APPEND COVERAGE_MISSING_TOOL "gcov")
    else()
        message(CHECK_PASS "found")
    endif()
    
    message(CHECK_START "Finding genhtml")
    find_program(GENHTML_PATH genhtml)
    if (NOT GENHTML_PATH)
        message(CHECK_FAIL "not found")
        list(APPEND COVERAGE_MISSING_TOOL "genhtml")
    else()
        message(CHECK_PASS "found")
    endif()

    list(POP_BACK CMAKE_MESSAGE_INDENT)

    if (COVERAGE_MISSING_TOOL)
        message(CHECK_FAIL "missing tools: ${COVERAGE_MISSING_TOOL}")
        return()
    else()
        message(CHECK_PASS "found")
    endif()

    add_custom_command(
        OUTPUT ${target}.base
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -c -i -d . -b ${CMAKE_CURRENT_LIST_DIR} --rc branch_coverage=1 --ignore-errors inconsistent -o ${target}.base
        DEPENDS ${target}
    )

    add_custom_command(
        OUTPUT
            ${target}.gcno
            ${target}.gcda
        COMMAND ${target}
        DEPENDS ${target}
    )

    add_custom_command(
        OUTPUT ${target}.capture
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -c -d . -b ${CMAKE_CURRENT_LIST_DIR} --rc branch_coverage=1 --ignore-errors inconsistent -o ${target}.capture
        DEPENDS
            ${target}.gcno
            ${target}.gcda
    )

    add_custom_command(
        OUTPUT ${target}.total
        COMMAND ${LCOV_PATH} --gcov-tool ${GCOV_PATH} -a ${target}.base -a ${target}.capture --ignore-errors inconsistent -o ${target}.total
        DEPENDS
            ${target}.base
            ${target}.capture
    )

    add_custom_target(${target}_coverage_report
        ${LCOV_PATH} --gcov-tool ${GCOV_PATH} --remove ${target}.total '/usr/include/*' 'gtest' 'test' --ignore-errors inconsistent -o ${target}.info
        DEPENDS ${target}.total
    )

    add_custom_command(TARGET ${target}_coverage_report
        POST_BUILD
        COMMAND ${GENHTML_PATH} --ignore-errors inconsistent -o ${target}_coverage ${target}.info
    )
endfunction()