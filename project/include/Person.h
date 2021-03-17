#ifndef PROJECT_INCLUDE_PERSON_H_
#define PROJECT_INCLUDE_PERSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CheckInput.h"

#define MEM_ALLOC_ERR 101
#define MEM_FREE_ERR 102
#define NO_PERSON_FOUND 110
struct Person {
    char* name;
    char* surname;
    char* role;
    int importance;
};
typedef struct Person Person;

int mem_alloc_person(Person* person);

int mem_free_person(Person* person);

int add_person_info(Person* person, char name[20], char role[15], char surname[30], int importance);

int check_person(Person* people, char name[20], char surname[30], char role[15]);

#endif  // PROJECT_INCLUDE_PERSON_H_
