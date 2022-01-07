#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "config.h"
#include "error_msg.h"
#include "count_predicate.h"
#include "work_with_bin.h"

int less157(const int* elem)  {
    return *elem < 157;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid arguments");
        exit(0);
    }
    int (*predicate)(const int*) = less157;
    FILE* arr_bin_file = fopen(argv[1], "r");
    if (arr_bin_file == NULL) {
        fprintf(stderr, "Wrong file or file name");
        exit(0);
    }
    size_t size = 0;
    if (fscanf(arr_bin_file, "%zu", &size) != 1) {
        fprintf(stderr, "Wrong array size");
        fclose(arr_bin_file);
        exit(0);
    }

    int* array = (int*)malloc(size * sizeof(size));
    if (fillArr(size, array, arr_bin_file) != EVERYTHING_IS_OK) {
        fprintf(stderr, "Array fill error");
        if (array != NULL) {
            free(array);
        }
        fclose(arr_bin_file);
        exit(0);
    }

    unsigned long result = 0;
    if (count_predicate_occurance(&result, size, array, predicate) != EVERYTHING_IS_OK) {
        fprintf(stderr, "predicate count error");
        free(array);
        fclose(arr_bin_file);
        exit(0);
    }
    printf("predicate occurance = %lu\n", result);
    free(array);
    
    return 0;
}
