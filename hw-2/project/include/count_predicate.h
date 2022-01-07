
#ifndef PROJECT_COUNT_PREDICATE_H_
#define PROJECT_COUNT_PREDICATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "error_msg.h"
#include "config.h"
#include "work_with_bin.h"

int count_predicate_occurance(unsigned long *res_sum, size_t size, int* elements, int (*predicate)(const int*));

#ifdef __cplusplus
}
#endif

#endif