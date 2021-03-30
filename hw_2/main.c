#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "configuration/config.h"
#include "ERRORS/error_msg.h"
#include "interface/interface.h"

struct option parameters[] = {
    { "parallel", required_argument, NULL, 'p'},
    { "input", required_argument, NULL, 'i'},
    { "arr_size", required_argument, NULL, 's'},
    { "help", no_argument, NULL, 'h'},
    { NULL, 0, NULL, 0}
};

int main(int argc, char* argv[]) {
    request new_request;
    strcpy(new_request, STDIN);
    new_request.arr_size = ARRAY_SIZE;
    new_request.is_parallel = BOOL_PARALLEL;

    int c;
    int opt_index;
    while ((c = getopt_long(argc, argv, "-:hpi:s", option, &opt_index)) != -1) {
        switch (c)
        {
        case 1:
            printf("Non-option argument %s\n", optarg);
            break;
        case 'h':
            printf("Usage: %s [--help|--parallel|--input <filename>|"
                "|--arr_size <size>|]\n", argv[0]);
                break;
        case 'i':
            stpcpy(new_request.input, optarg);
            break;
        case 'p':
            new_request.is_parallel = 1;
            break;
        case '?':
            printf("Unknown option %c\n", optopt);
            break;
        case ':':
            printf("Missing argument for %c\n", optopt);
            break;
        default:
            break;
        }
    }
    int error = request(&new_request);
    if (error) {
        print_error_msg(err);
    }
    return error;
}