#ifndef PROJECT_INCLUDE_PERSON_H_
#define PROJECT_INCLUDE_PERSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CheckInput.h"

#define MEM_ALLOC_ERR 101
#define MEM_FREE_ERR 102
#define ADD_PERSON_DATA_ERR 103
#define NO_PERSON_FOUND 110

#define NAME_SIZE 20
#define SURNAME_SIZE 30
#define ROLE_SIZE 15
struct Person {
    char* name;
    char* surname;
    char* role;
    int importance;
};
typedef struct Person Person;

int mem_alloc_person(Person* person);

int mem_free_person(Person* person);

int add_person_info(Person* person, char name[NAME_SIZE],
    char role[ROLE_SIZE], char surname[SURNAME_SIZE], int importance);

int check_person(Person* people, char name[NAME_SIZE], char surname[SURNAME_SIZE],
    char role[ROLE_SIZE]);

#endif  // PROJECT_INCLUDE_PERSON_H_
