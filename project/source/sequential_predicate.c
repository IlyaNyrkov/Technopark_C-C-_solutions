#include "count_predicate.h"
#include <stdio.h>

int count_predicate_occurance(unsigned long *res_sum, size_t size, int* elements, int (*predicate)(const int*)) {
    if (elements == NULL) {
        printf("stream issue\n\n");
    }
    if (res_sum == NULL || elements == NULL || predicate == NULL) {
        return INPUT_ERR;
    }
    
    if (size == 0) {
        *res_sum = 0;
        return EVERYTHING_IS_OK;
    }

    int error = EVERYTHING_IS_OK;
    for (size_t i = 0; i < size; ++i) {
        if (predicate(&elements[i])) {
            (*res_sum)++;
        }
    }
    return error;
}