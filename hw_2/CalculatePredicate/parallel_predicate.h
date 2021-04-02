#ifndef PROJECT_PARALLEL_PREDICATE_H_
#define PROJECT_PARALLEL_PREDICATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


#include "configuration/config.h"
#include "File_Work/work_with_bin.h"
#include "ERRORS/error_msg.h"
struct thread_arguments {
    FILE* stream;
    unsigned long count;
    size_t step;
    size_t size;
    size_t id;
    int buffer_tmp;
};

typedef struct thread_arguments thread_arguments;

int get_number_of_CPU_cores();

int count_predicate_occurance_parallel(unsigned long *res_sum, size_t size, char stream_name[FILE_NAME_LENGTH]);

int initiate_threads(thread_arguments *args, size_t thread_count, size_t size, char stream_name[FILE_NAME_LENGTH]);

int run_threads(pthread_t *threads, thread_arguments *args, size_t thread_count);

void count_partial_predicate_occurance(void *void_args);

int get_result_predicate_occurance_threads(unsigned long *res_count, thread_arguments *args, size_t thread_count);

int wait_threads(const pthread_t *threads, size_t thread_count);

int predicate(const int* elem);

#ifdef __cplusplus
}
#endif

#endif