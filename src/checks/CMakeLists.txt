add_executable(match_check1 match_check1.cpp)
add_executable(match_check2a match_check2a.cpp)
add_executable(match_check2b match_check2b.cpp)
add_executable(match_check3a match_check3a.cpp)
add_executable(match_check3b match_check3b.cpp)
add_executable(match_check4a match_check4a.cpp)
add_executable(match_check4b match_check4b.cpp)

add_test(NAME test_match_check1 COMMAND match_check1)
set_property(TEST test_match_check1 PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check2a COMMAND match_check2a)
set_property(TEST test_match_check2a PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check2b COMMAND match_check2b)
set_property(TEST test_match_check2b PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check3a COMMAND match_check3a)
set_property(TEST test_match_check3a PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check3b COMMAND match_check3b)
set_property(TEST test_match_check3b PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check4a COMMAND match_check4a)
set_property(TEST test_match_check4a PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")

add_test(NAME test_match_check4b COMMAND match_check4b)
set_property(TEST test_match_check4b PROPERTY FAIL_REGULAR_EXPRESSION "FAIL:")
