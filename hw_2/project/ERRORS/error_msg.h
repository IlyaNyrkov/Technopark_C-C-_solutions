#ifndef ERRORS_ERROR_MSG_H
#define ERRORS_ERROR_MSH_H

#include <stdio.h>

#define EVERYTHING_IS_OK 0
#define INPUT_ERR 101
#define WRONG_DATA_ERR 102
#define RUN_THREADS_ERR 201
#define JOIN_THREADS_ERR 202
#define FUNC_ERR 301

void print_error_msg(int error_code);

#endif