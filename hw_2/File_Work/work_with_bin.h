#ifndef FILE_WORK_WORK_WITH_BIN_H
#define FILE_WORK_WORK_WITH_BIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "ERRORS/error_msg.h"
int get_number_from_pos(int* number, size_t id, FILE* stream);


#ifdef __cplusplus
}
#endif

#endif