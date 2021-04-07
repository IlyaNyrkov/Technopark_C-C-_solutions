
#include "work_with_bin.h"

int get_number_from_pos(int* number, size_t id, FILE* stream) {
    if (number == NULL || stream == NULL) {
        return WRONG_DATA_ERR;
    }

    if (fseek(stream, id * sizeof(int), SEEK_SET)) {
        return FUNC_ERR;
    }

    if (fread(number, sizeof(int), 1, stream) != 1) {
        return INPUT_ERR;
    }

    return EVERYTHING_IS_OK; 
}
