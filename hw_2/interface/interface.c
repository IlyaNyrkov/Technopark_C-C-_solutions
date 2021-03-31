#include "interface.h"

int interface(const request* new_request) {
    if (!new_request) {
        return WRONG_DATA_ERR;
    }

    int error = EVERYTHING_IS_OK;

    unsigned long count = 0;

    struct timeb start, end;
    int64_t time = 0;

    if (new_request->is_parallel) {
        ftime(&start);
        error = count_predicate_occurance_parallel(&count, new_request->arr_size, new_request->input);
    } else {
        ftime(&start);
        error = count_predicate_occurance_sequential(&count, new_request->arr_size, new_request->input);
    }
    time += (end.time - start.time + 0.) + (end.millitm - start.millitm + 0.) / 1000;

    printf("predicate occurance = %u\n", count);
    printf("time = %" PRIu64 "\n", time);

    return error;
}