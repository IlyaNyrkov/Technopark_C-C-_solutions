#include "sequential_predicate.h"
int predicate(const int* elem) {
    if (elem == NULL) {
        return WRONG_DATA_ERR;
    }
    if (*elem < 157) {
        return 1;
    }
    return 0;
}

int count_predicate_occurance_sequential(unsigned long *res_sum, size_t size, char* stream_name) {
    if (!res_sum || !stream_name) {
        return INPUT_ERR;
    }
    
    if (size == 0) {
        *res_sum = 0;
        return EVERYTHING_IS_OK;
    }

    FILE *stream = fopen(stream_name, "rd");
    if (stream == NULL) {
        return WRONG_DATA_ERR;
    }
    int error = EVERYTHING_IS_OK;
    int buffer = 0;
    for (size_t i = 0; i < size; ++i) {
        error = get_number_from_pos(&buffer, i, stream);
        if (!error && predicate(&buffer)) {
            (*res_sum)++;
        }
    }
    fclose(stream);
    return error;
}