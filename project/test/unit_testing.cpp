#include "gtest/gtest.h"
#include <stdio.h>
#include "count_predicate.h"

int less157(const int* elem) {
    return *elem < 157;
}

void fillArr(size_t size, int* elements, FILE* stream) {
    int buffer;
    for (size_t i = 0; i < size; i++) {
    fread(&buffer, sizeof(int), 1, stream);
    elements[i] = buffer;
    }
}

TEST(test_predecate_count, test_10k_nums) {
    FILE* stream = fopen("../project/TestFilesBin/test_10k.bin", "rd");
    int* elements = (int*)malloc(10000 * sizeof(int));
    fillArr(10000, elements, stream);
    unsigned long result = 1591;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance(&count, 10000, elements, less157), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
    fclose(stream);
    free(elements);
}

TEST(test_predecate_count, test_100k_nums) {
    FILE* stream = fopen("../project/TestFilesBin/test_100k.bin", "rd");
    int* elements = NULL;
    elements = (int*)malloc(100000 * sizeof(int));
    fillArr(100000, elements, stream);
    unsigned long result = 15816;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance(&count, 100000, elements, less157), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
    fclose(stream);
    free(elements);
}

TEST(test_predecate_count, test_500k_nums) {
    FILE* stream = fopen("../project/TestFilesBin/test_500k.bin", "rd");
    int* elements = NULL;
    elements = (int*)malloc(500000 * sizeof(int));
    fillArr(500000, elements, stream);
    unsigned long result = 79081;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance(&count, 500000, elements, less157), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
    fclose(stream);
    free(elements);
}

TEST(test_predecate_count, test_1million_nums) {
    FILE* stream = fopen("../project/TestFilesBin/test_1mil.bin", "rd");
    int* elements = NULL;
    elements = (int*)malloc(1000000 * sizeof(int));
    fillArr(1000000, elements, stream);
    unsigned long result = 158499;
    unsigned long count = 0;
    ASSERT_EQ(count_predicate_occurance(&count, 1000000, elements, less157), EVERYTHING_IS_OK);
    ASSERT_EQ(count, result);
    fclose(stream);
    free(elements);
}

TEST(test_predecate_count, NULL_PARAMETERS) {
    int* elements = NULL;
    unsigned long digit = 0;
    unsigned long* count = &digit;
    ASSERT_EQ(count_predicate_occurance(count, 1000000, elements, less157), WRONG_DATA_ERR);
    count = NULL;
    ASSERT_EQ(count_predicate_occurance(count, 1000000, elements, less157), WRONG_DATA_ERR);
}



int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int error = RUN_ALL_TESTS();
    return error;
}