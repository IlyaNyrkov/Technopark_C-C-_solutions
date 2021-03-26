#include <stdio.h>
#define ARRAY_SIZE 1000000000

#define MEM_ALLOC_ERR 10
size_t count_predicate(int* array, int (*predicate)(const int*)) {
    size_t result = 0;
    if (array == NULL) {
        return MEM_ALLOC_ERR;
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (predicate(array[i])) {
            result++;
        }
    }
    return result;
}

int less_than_ten(const int *num) {
    if (*num < 10) {
        return 1;
    } else {
        return 0;
    }
}

int fill_array(int* arr) {
    if (arr == NULL) {
        return MEM_ALLOC_ERR;
    }
}

int main(int argc, char* argv[]) {

    int* array = (int*)malloc(sizeof(int) * ARRAY_SIZE);
    size_t result = count_predicate(array, less_than_ten);
    printf("%zu");
    free(array);
    return 0;
}