#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/timeb.h>

#include "../ERRORS/error_msg.h"
#include "../configuration/config.h"
#include "../CalculatePredicate/sequential_predicate.h"
#include "../CalculatePredicate/parallel_predicate.h"

struct request {
    char input[FILE_NAME_LENGTH];
    size_t arr_size;
    int is_parallel;
}
typedef struct request request

int interface(const request* new_request);

#endif // INTERFACE_H_