#ifndef PROJECT_INCLUDE_CHECKINPUT_H_
#define PROJECT_INCLUDE_CHECKINPUT_H_
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define NO_DATA_ERR 201
#define WRONG_NUM_ERR 202
#define TO_BIG_DATA_ERR 203
#define WRONG_PERSON_DATA_ERR 204
#define WRONG_COMMAND_ERR 205

#define CMD_LINE_SIZE 80
#define DEF_NUM_SIZE 5

int check_number(char* number);

int parse_command(char cmd_line[CMD_LINE_SIZE], char* name, char* surname, char* role);

int parse_person_data(char buffer[CMD_LINE_SIZE], char* name, char* surname, char* role, int* importance);

#endif  // PROJECT_INCLUDE_CHECKINPUT_H_
