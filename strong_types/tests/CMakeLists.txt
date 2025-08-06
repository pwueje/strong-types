set(component "${component}-test")

add_executable(${component}
    test_strong_types.cpp
)

target_add_common_build_properties(${component})
target_enable_clang_tidy(${component})

find_package(Catch2 REQUIRED)

target_link_libraries(${component}
    PRIVATE
        strong_types::strong_types
        Catch2::Catch2WithMain
)

catch_discover_tests(${component})