#include <gtest/gtest.h>
#include "../CalculatePredicate/parallel_predicate.h"
#include "../CalculatePredicate/sequential_predicate.h"

TEST(stress_test, testing_10k_numbers) {
    uint predicate_count_parallel = 0;
    uint predicate_count_sequential = 0;
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
    EXPECT_EQ(count_predicate_occurance_parallel(&predicate_count_parallel,
     10000, filename), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance_sequential(&predicate_count_sequential,
     10000, filename), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);
}

TEST(stress_test, testing_100k_numbers) {
    uint predicate_count_parallel = 0;
    uint predicate_count_sequential = 0;
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_100k.bin";
    EXPECT_EQ(count_predicate_occurance_parallel(&predicate_count_parallel,
     100000, filename), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance_sequential(&predicate_count_sequential,
     100000, filename), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);
}

TEST(stress_test, testing_100k_numbers) {
    uint predicate_count_parallel = 0;
    uint predicate_count_sequential = 0;
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_500k.bin";
    EXPECT_EQ(count_predicate_occurance_parallel(&predicate_count_parallel,
     500000, filename), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance_sequential(&predicate_count_sequential,
     500000, filename), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);
}

TEST(stress_test, testing_1mil_numbers) {
    uint predicate_count_parallel = 0;
    uint predicate_count_sequential = 0;
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1mil.bin";
    EXPECT_EQ(count_predicate_occurance_parallel(&predicate_count_parallel,
     1000000, filename), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance_sequential(&predicate_count_sequential,
     1000000, filename), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);
}