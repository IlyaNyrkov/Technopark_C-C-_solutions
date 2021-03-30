#include <gtest/gtest.h>
#include "../ERRORS/error_msg.h"
#include "../CalculatePredicate/sequential_predicate.h"
#include "../CalculatePredicate/parallel_predicate.h"
#include "../interface/interface.h"
#include "../File_Work/work_with_bin.h"
#include "../configuration/config.h"

TEST(static_library_sequential_algorithm, test_10k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
    uint result = 1591;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 10000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_100k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_100k.bin";
    uint result = 15816;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 100000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_500k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_500k.bin";
    uint result = 79081;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 500000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_100million_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1mil.bin";
    uint result = 158499;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 1000000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

//

TEST(dynamic_library_sequential_algorithm, test_10k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
    uint result = 1591;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 10000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_sequential_algorithm, test_100k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_100k.bin";
    uint result = 15816;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 100000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_sequential_algorithm, test_500k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_500k.bin";
    uint result = 79081;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 500000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_sequential_algorithm, test_100million_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1mil.bin";
    uint result = 158499;
    uint count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 1000000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}