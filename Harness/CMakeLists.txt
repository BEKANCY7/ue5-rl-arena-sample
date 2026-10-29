cmake_minimum_required(VERSION 3.16)
project(ArenaSampleHarness LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(arena_logic_tests
  tests/test_arena_logic.cpp
  ../Source/ArenaSample/Private/Inventory/ArenaInventory.cpp
  ../Source/ArenaSample/Private/Combat/ArenaDamage.cpp
)

target_compile_definitions(arena_logic_tests PRIVATE ARENA_PORTABLE_BUILD=1)
target_include_directories(arena_logic_tests PRIVATE
  stubs
  ../Source/ArenaSample/Public
)

enable_testing()
add_test(NAME arena_logic_tests COMMAND arena_logic_tests)
