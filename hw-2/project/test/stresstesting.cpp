#include "gtest/gtest.h"
#include "dlfcn.h"
#include "count_predicate.h"
#include "error_msg.h"
#include "work_with_bin.h"

int less157(const int* elem)  {
    return *elem < 157;
}

TEST(stress_test, testing_10k_numbers) {

    void* library = dlopen("libcount_predicate_occur_parallel.so", RTLD_LAZY);
    if (library == NULL) {
        std::cout << "\n dlib problem" << std::endl;
    }
    int (*count_predicate_occur)(unsigned long *res_sum, size_t size,
    int* stream, int (*predicate)(const int*));
    *(void **)(&count_predicate_occur) = dlsym(library, "count_predicate_occurance");
    FILE* stream = fopen("project/TestFilesBin/test_10k.bin", "rb");
    int* elements = (int *)malloc(10000 * sizeof(int));
    fillArr(10000, elements, stream);

    unsigned long predicate_count_parallel = 0;
    unsigned long predicate_count_sequential = 0;
    
    EXPECT_EQ((*count_predicate_occur)(&predicate_count_parallel,
     10000, elements, less157), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance(&predicate_count_sequential,
     10000, elements, less157), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);

     dlclose(library);
     free(elements);
     fclose(stream);
}

TEST(stress_test, testing_100k_numbers) {
    void* library = dlopen("libcount_predicate_occur_parallel.so", RTLD_LAZY);
    int (*count_predicate_occur)(unsigned long *res_sum, size_t size,
    int* stream, int (*predicate)(const int*));
    *(void **)(&count_predicate_occur) = dlsym(library, "count_predicate_occurance");
    FILE* stream = fopen("project/TestFilesBin/test_10k.bin", "rb");
    int* elements = (int *)malloc(100000 * sizeof(int));
    fillArr(100000, elements, stream);

    unsigned long predicate_count_parallel = 0;
    unsigned long predicate_count_sequential = 0;

    EXPECT_EQ((*count_predicate_occur)(&predicate_count_parallel,
     100000, elements, less157), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance(&predicate_count_sequential,
     100000, elements, less157), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);

     dlclose(library);
     free(elements);
     fclose(stream);
}

TEST(stress_test, testing_500k_numbers) {
    void* library = dlopen("libcount_predicate_occur_parallel.so", RTLD_LAZY);
    int (*count_predicate_occur)(unsigned long *res_sum, size_t size,
    int* stream, int (*predicate)(const int*));
    *(void **)(&count_predicate_occur) = dlsym(library, "count_predicate_occurance");
    FILE* stream = fopen("project/TestFilesBin/test_500k.bin", "rb");
    int* elements = (int *)malloc(500000 * sizeof(int));
    fillArr(500000, elements, stream);
    
    unsigned long predicate_count_parallel = 0;
    unsigned long predicate_count_sequential = 0;

    EXPECT_EQ((*count_predicate_occur)(&predicate_count_parallel,
     500000, elements, less157), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance(&predicate_count_sequential,
     500000, elements, less157), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);

     dlclose(library);
     free(elements);
     fclose(stream);
}

TEST(stress_test, testing_1mil_numbers) {
    void* library = dlopen("libcount_predicate_occur_parallel.so", RTLD_LAZY);
    int (*count_predicate_occur)(unsigned long *res_sum, size_t size,
    int* stream, int (*predicate)(const int*));
    *(void **)(&count_predicate_occur) = dlsym(library, "count_predicate_occurance");
    FILE* stream = fopen("project/TestFilesBin/test_1mil.bin", "rb");
    int* elements = (int *)malloc(1000000 * sizeof(int));
    fillArr(1000000, elements, stream);

    unsigned long predicate_count_parallel = 0;
    unsigned long predicate_count_sequential = 0;

    EXPECT_EQ((*count_predicate_occur)(&predicate_count_parallel,
     1000000, elements, less157), EVERYTHING_IS_OK);
    EXPECT_EQ(count_predicate_occurance(&predicate_count_sequential,
     1000000, elements, less157), EVERYTHING_IS_OK);
     EXPECT_EQ(predicate_count_parallel, predicate_count_sequential);

     dlclose(library);
     free(elements);
     fclose(stream);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int error = RUN_ALL_TESTS();
    return error;
}