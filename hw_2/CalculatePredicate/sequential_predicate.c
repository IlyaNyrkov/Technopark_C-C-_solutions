#include "sequential_predicate.h"

int count_predicate_occurance_sequential(uint *res_sum, size_t size, char stream_name[100]) {
    if (!res_sum || !stream_name) {
        return INPUT_ERROR;
    }
    
    if (size == 0) {
        *res_sum = 0
        return 0;
    }

    FILE *stream = fopen(stream_name, "rd");
    
}