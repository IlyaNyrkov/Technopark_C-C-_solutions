#ifndef PROJECT_SEQUENTIAL_PREDICATE_H_
#define PROJECT_SEQUENTIAL_PREDICATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "ERRORS/error_msg.h"

int count_predicate_occurance_sequential(unsigned long *res_sum, size_t size, char* stream_name);

int predicate(const int* elem);

#ifdef __cplusplus
}
#endif

#endif