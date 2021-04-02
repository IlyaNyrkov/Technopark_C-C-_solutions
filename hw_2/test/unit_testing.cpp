#include "gtest/gtest.h"
#include "File_Work/work_with_bin.h"
#include "interface/interface.h"
#include "ERRORS/error_msg.h"
#include "CalculatePredicate/parallel_predicate.h"
#include "CalculatePredicate/sequential_predicate.h"

TEST(static_library_sequential_algorithm, test_10k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
    unsigned long result = 1591;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 10000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_100k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_100k.bin";
    unsigned long result = 15816;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 100000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_500k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_500k.bin";
    unsigned long result = 79081;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 500000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, test_1million_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1mil.bin";
    unsigned long result = 158499;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 1000000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(static_library_sequential_algorithm, NULL_PARAMETERS) {
    char* filename = NULL;
    unsigned long* count;
    *count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(count, 1000000, filename), INPUT_ERR);
    filename = "TestFilesBin/test_10k.bin";
    count = NULL;
    ASSERT_EQ(count_predicate_occurance_sequential(count, 1000000, filename), INPUT_ERR);
}

TEST(static_library_sequential_algorithm, wrong_file_name) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1trillion.bin";
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_sequential(&count, 1000000, filename), WRONG_DATA_ERR);
}

TEST(predicate, predicate_test) {
    {
    const int digit = 100;
    ASSERT_EQ(predicate(&digit), 1);
    }
    {
    const int digit = 157;
    ASSERT_EQ(predicate(&digit), 0);
    }
    {
    const int digit = 200;
    ASSERT_EQ(predicate(&digit), 0);
    }
    {
    const int* digit = NULL;
    ASSERT_EQ(predicate(digit), WRONG_DATA_ERR);
    }
}

//dynamic_lib

TEST(dynamic_library_parallel_algorithm, test_10k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
    unsigned long result = 1591;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 10000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_parallel_algorithm, test_100k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_100k.bin";
    unsigned long result = 15816;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 100000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_parallel_algorithm, test_500k_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_500k.bin";
    unsigned long result = 79081;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 500000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library_parallel_algorithm, test_1million_nums) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1mil.bin";
    unsigned long result = 158499;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 1000000, filename), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
}

TEST(dynamic_library, wrong_file_name) {
    char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1trillion.bin";
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance_parallel(&count, 1000000, filename), WRONG_DATA_ERR);
}

TEST(dynamic_library, GetNumberOfCPUcores) {
    int corecount = get_number_of_CPU_cores();
    ASSERT_EQ(corecount, 2);
}

TEST(dynamic_library, Initiate_threads) {
    {
        thread_arguments args[3];
        char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
        EXPECT_EQ(initiate_threads(args, 3, 1, filename), EVERYTHING_IS_OK);
    }
    {
        thread_arguments args[3];
        char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
        EXPECT_EQ(initiate_threads(args, 3, 0, filename), WRONG_DATA_ERR);
    }
    {
        thread_arguments args[3];
        char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
        EXPECT_EQ(initiate_threads(args, 0, 3, filename), WRONG_DATA_ERR);
    }
    {
        thread_arguments args[3];
        char* filename = NULL;
        EXPECT_EQ(initiate_threads(args, 3, 1, filename), WRONG_DATA_ERR);
    }
    {
        thread_arguments* args = NULL;
        char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_10k.bin";
        EXPECT_EQ(initiate_threads(args, 3, 3, filename), WRONG_DATA_ERR);
    }
    {
        thread_arguments args[3];
        char filename[FILE_NAME_LENGTH] = "TestFilesBin/test_1trillion.bin";
        EXPECT_EQ(initiate_threads(args, 3, 3, filename), WRONG_DATA_ERR);
    }
}

TEST(dynamic_library, Run_threads) {
    {
        thread_arguments args[3];
        pthread_t* threads = NULL;
        EXPECT_EQ(run_threads(threads, args, 3), WRONG_DATA_ERR);
    }
    {
        thread_arguments* args = NULL;
        pthread_t threads[3];
        EXPECT_EQ(run_threads(threads, args, 3), WRONG_DATA_ERR);
    }
    {
        thread_arguments args[3];
        pthread_t threads[3];
        EXPECT_EQ(run_threads(threads, args, 3), EVERYTHING_IS_OK);
    }
}

TEST(dynamic_library, get_result_predicate_occurance_threads) {
    {
        unsigned long count = 0;
        thread_arguments args[3];
        EXPECT_EQ(get_result_predicate_occurance_threads(&count, args, 0), WRONG_DATA_ERR);
    }
    {
        unsigned long* count = NULL;
        thread_arguments args[3];
        EXPECT_EQ(get_result_predicate_occurance_threads(count, args, 0), WRONG_DATA_ERR);
    }
    {
        {
        unsigned long count = 0;
        thread_arguments* args = NULL;
        EXPECT_EQ(get_result_predicate_occurance_threads(&count, args, 0), WRONG_DATA_ERR);
        }
    }
}

TEST(dynamic_library, wait_threads) {
    {
        pthread_t* threads = NULL;
        EXPECT_EQ(wait_threads(threads, 3), WRONG_DATA_ERR);
    }
    {
        pthread_t threads[3];
        EXPECT_EQ(wait_threads(threads, 0), WRONG_DATA_ERR);
    }
}



TEST(file_work_get_number_from_pos, NULL_PARAMS) {
    {
        int* number = NULL;
        FILE* file = fopen("TestFilesBin/test_10k.bin", "rb");
        EXPECT_EQ(get_number_from_pos(number, 0, file), WRONG_DATA_ERR);
        fclose(file);
    }
    {
        int number = 0;
        FILE* file = NULL;
        EXPECT_EQ(get_number_from_pos(&number, 0, file), WRONG_DATA_ERR);
    }
    {
        int number = 0;
        FILE* file = fopen("TestFilesBin/test_10k.bin", "rb");
        EXPECT_EQ(get_number_from_pos(&number, 0, file), EVERYTHING_IS_OK);
    }
}

TEST(Interface, interface_null_param) {
    request* new_request = NULL;
    EXPECT_EQ(interface(new_request), WRONG_DATA_ERR);
}

TEST(Interface, change_modes) {
    request new_request_sequential;
    strcpy(new_request_sequential.input, "TestFilesBin/test_10k.bin");
    new_request_sequential.arr_size = 10000;
    new_request_sequential.is_parallel = 0;
    EXPECT_EQ(interface(&new_request_sequential), EVERYTHING_IS_OK);

    request new_request_parallel;
    strcpy(new_request_parallel.input, "TestFilesBin/test_10k.bin");
    new_request_parallel.arr_size = 10000;
    new_request_parallel.is_parallel = 1;
    EXPECT_EQ(interface(&new_request_parallel), EVERYTHING_IS_OK);
}