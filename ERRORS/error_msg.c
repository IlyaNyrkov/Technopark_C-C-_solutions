#include "error_msg.h"

void print_error_msg(int error_code) {
    switch (error_code)
    {
    case INPUT_ERR:
        fprintf(stderr, "Input error!");
        break;
    case WRONG_DATA_ERR:
        fprinf(stderr, "Wrong data error!");
        break;
    case JOIN_THREADS_ERR:
        fprintf(stderr, "Finishing threads error!");
        break;
    case RUN_THREADS_ERR:
        fprintf(stderr, "Running threads error!")
    default:
        fprintf(stderr, "Unknown error!");
        break;
    }
}