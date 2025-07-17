find_package(GTest REQUIRED)
include_directories(
  ${GTEST_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(test_sniffer
  test_sniffer.cpp
)

target_link_libraries(test_sniffer
  PRIVATE sniffer_lib
          GTest::GTest
          GTest::Main
)

add_test(NAME SnifferTest COMMAND test_sniffer)
