#include "sequential_predicate.h"

int predicate(const int* elem) {
    if (*elem < 157) {
        return 1;
    }
    return 0;
}

int count_predicate_occurance_sequential(uint *res_count, size_t size, char stream_name[100], (*predicate)(const int*)) {
    if (!res_sum || !stream_name) {
        return INPUT_ERROR;
    }
    
    if (size == 0) {
        *res_count = 0
        return 0;
    }
    
    FILE *stream = fopen(stream_name, "rd");
    if (!stream) {
        return WRONG_DATA_ERR;
    }
    *res_count = 0;
    int error = EVERYTHING_IS_OK;
    int buff_tmp = 0;
    for (size_t i = 0; i < size; ++i) {
        error = get_number_from_pos(&buff_tmp, i, stream);
        if (!error && predicate(&buff_tmp)) {
            (*res_count)++;
        }
    }
    fclose(stream);
    return error;
}