#include "CheckInput.h"


int check_number(char* number) {
    if (number == NULL) {
        return WRONG_NUM_ERR;
    }
    if (strlen(number) > DEF_NUM_SIZE - 1 || strlen(number) == 0) {
        return WRONG_NUM_ERR;
    }
    if (number[0] == '-') {
        return WRONG_NUM_ERR;
    }
    for (size_t i = 0; i < strlen(number); i++) {
        if (isdigit(number[i]) == 0) {
            return WRONG_NUM_ERR;
        }
    }
    return 0;
}

int parse_command(char cmd_line[CMD_LINE_SIZE], char* name, char* surname, char* role) {
    if (cmd_line == NULL || name == NULL || surname == NULL || role == NULL) {
        return WRONG_COMMAND_ERR;
    }
    int offset = 0;
    int elem_count = 0;
    int semi_colomn_count = 0;
    if (sscanf(cmd_line, "%19[a-zA-Z]%n;", name, &offset) == 1) {
        elem_count++;
    }
    cmd_line += offset;
    if (cmd_line[0] == ';') {
        semi_colomn_count++;
    }
    cmd_line++;
    if (sscanf(cmd_line, "%29[a-zA-Z]%n;", surname, &offset) == 1) {
        elem_count++;
    }
    if (strcmp(surname, "\n") == 0) {
        offset = 0;
    }
    cmd_line += offset;
    if (cmd_line[0] == ';') {
        semi_colomn_count++;
    }
    cmd_line++;
    if (sscanf(cmd_line, "%14[a-zA-Z]%n", role, &offset) == 1) {
        elem_count++;
    }
    if (elem_count == 0 || semi_colomn_count != 2) {
        return WRONG_COMMAND_ERR;
    }
    return 0;
}

int parse_person_data(char buffer[CMD_LINE_SIZE], char* name, char* surname, char* role, int* importance) {
    if (buffer == NULL || name == NULL || surname == NULL|| role == NULL || importance == NULL) {
        return WRONG_PERSON_DATA_ERR;
    }
    int tmp_importance;
    if (sscanf(buffer, "%19[a-zA-Z];%29[a-zA-Z];%14[a-zA-Z];%d",
        name, surname, role, &tmp_importance) != 4) {
            return WRONG_PERSON_DATA_ERR;
        }
    if (tmp_importance < 0 || tmp_importance > 9999) {
        return WRONG_PERSON_DATA_ERR;
    }
    if (importance == NULL) {
        return WRONG_PERSON_DATA_ERR;
    }
    *importance = tmp_importance;
    return 0;
}
