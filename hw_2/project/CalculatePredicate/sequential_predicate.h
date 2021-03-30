#ifndef PROJECT_SEQUENTIAL_PREDICATE_H_
#define PROJECT_SEQUENTIAL_PREDICATE_H_

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "../ERRORS/error_msg.h"
#include "../File_Work/work_with_bin.h"

int count_predicate_occurance_sequential(uint *res_sum, size_t size, char stream_name[100]);

int predicate(const int* elem);

#endif