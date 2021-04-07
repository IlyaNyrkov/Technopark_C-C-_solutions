#include "count_predicate.h"

typedef struct  {
    int* array;
    size_t count;
    size_t step;
    size_t size;
    size_t id;
    int (*predicate)(const int*);
    int buffer_tmp;
} thread_arguments;

int get_number_of_CPU_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

int initiate_threads(thread_arguments *args, size_t thread_count,
        size_t size, int* elements, int (*predicate)(const int*)) {
    if (args == NULL || elements == NULL || thread_count < 1 || size < 1) {
        return WRONG_DATA_ERR;
    }
   
    for (size_t i = 0; i < thread_count; ++i) {
        args[i].array = elements;
        args[i].count = 0;
        args[i].step = thread_count;
        args[i].size = size;
        args[i].id = i;
        args[i].buffer_tmp = 0;
        args[i].predicate = predicate;
    }
    return EVERYTHING_IS_OK;
}

void* count_partial_predicate_occurance(void *void_args) {
    int error = EVERYTHING_IS_OK;
    if (void_args == NULL) {
        error = WRONG_DATA_ERR;
        pthread_exit(&error);
    }

    thread_arguments *args = (thread_arguments*)void_args;

    args->count = 0;
    while ((args->id < ARRAY_SIZE) && (args->id < args->size) && !error) {
        args->buffer_tmp = args->array[args->id];
        if (!error) {
            if (args->predicate(&args->buffer_tmp)) {
                args->count++;
            }
        }
        args->id += args->step;
    }
    pthread_exit(&error);
}

int run_threads(pthread_t *threads, thread_arguments *args, size_t thread_count) {
    if (threads == NULL || args == NULL || thread_count < 1) {
        return WRONG_DATA_ERR;
    }

    int error_flag = 0;
    for (size_t i = 0; (i < thread_count) && (!error_flag); ++i) {
        error_flag = pthread_create(&threads[i], NULL, count_partial_predicate_occurance, &args[i]);
    }

    if (error_flag) {
        return JOIN_THREADS_ERR;
    }

    return EVERYTHING_IS_OK;
}

int get_result_predicate_occurance_threads(unsigned long *res_count, thread_arguments *args, size_t thread_count) {
    if (res_count == NULL || args == NULL|| thread_count < 1) {
        return WRONG_DATA_ERR;
    }
    // add predicate
    for (size_t i = 0; i < thread_count; ++i) {
        *res_count += args[i].count;
    }
    return EVERYTHING_IS_OK;
}

int wait_threads(const pthread_t *threads, size_t thread_count) {
    if (threads == NULL || thread_count < 1) {
        return WRONG_DATA_ERR;
    }
    int error_flag = EVERYTHING_IS_OK;
    for (size_t i = 0; (i < thread_count) && (!error_flag); ++i) {
        error_flag = pthread_join(threads[i], NULL);
    }

    if (error_flag) {
        return JOIN_THREADS_ERR;
    }
    return EVERYTHING_IS_OK;
}

int predicate(const int* elem) {
    if (elem == NULL) {
        return WRONG_DATA_ERR;
    }
    if (*elem < 157) {
        return 1;
    }
    return 0;
}

int count_predicate_occurance(unsigned long *res_sum, size_t size, int* elements, int (*predicate)(const int*)) {
    if (res_sum == NULL || elements == NULL) {
        return WRONG_DATA_ERR;
    }

    if (size == 0) {
        *res_sum = 0;
        return EVERYTHING_IS_OK;
    }

    int error = EVERYTHING_IS_OK;
    size_t thread_count = BASE_THREAD_CNT;

    thread_arguments args[thread_count];
    error = initiate_threads(args, thread_count, size, elements, predicate);
    if (error) {
        return error;
    }

    pthread_t threads[thread_count];
    int CPU_cores_count = get_number_of_CPU_cores();
    size_t active_threads;
    size_t i = 0;
    while ((i < thread_count) && (!error)) {
        active_threads = (thread_count - i >= CPU_cores_count) ? CPU_cores_count : thread_count - i;
        error = run_threads(&threads[i], &args[i], active_threads);
        if (!error) {
            error = wait_threads(&threads[i], active_threads);
            i += active_threads;
        }
    }
    if (error) {
        return error;
    }
    error = get_result_predicate_occurance_threads(res_sum, args, thread_count);

    return error;
}