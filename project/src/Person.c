
#include "../include/Person.h"

int mem_alloc_person(Person* person) {
    person->name = malloc(20 * sizeof(char));
    if (person->name == NULL) {
        return MEM_ALLOC_ERR;
    }
    person->surname = malloc(30 * sizeof(char));
    if (person->surname == NULL) {
        return MEM_ALLOC_ERR;
    }
    person->role = malloc(15 * sizeof(char));
    if (person->surname == NULL) {
        return MEM_ALLOC_ERR;
    }
    return 0;
}

int mem_free_person(Person* person) {
    if (person == NULL) {
        return MEM_FREE_ERR;
    }
    if (person->name != NULL) {
        free(person->name);
        person->name = NULL;
    }
    if (person->surname != NULL) {
        free(person->surname);
        person->surname = NULL;
    }
    if (person->role != NULL) {
        free(person->role);
        person->role = NULL;
    }
    return 0;
}

int add_person_info(Person* person, char name[20], char role[15], char surname[30], int importance) {
    if (person == NULL) {
        return MEM_ALLOC_ERR;
    }
    if (person->name == NULL) {
        return MEM_ALLOC_ERR;
    }
    snprintf(person->name, sizeof(person->name), "%s", name);
    if (person->surname == NULL) {
        return MEM_ALLOC_ERR;
    }
    snprintf(person->surname, sizeof(person->surname), "%s", surname);
    if (person->role == NULL) {
        return MEM_ALLOC_ERR;
    }
    snprintf(person->role, sizeof(person->role), "%s", role);
    person->importance = importance;
    return 0;
}
// how this works: there are free checks and ability to not enter all fields for check
// we need to check that given parameter (number, surname, role) is empty (check b: on the right)
// тif it's empty, then structure check field equal to given parameter (check a: on the left) doesn't
// change anything, logic table for one 3's subexpressions, the logic expression: (+) or mod 2
// |a|b|res|
// |0|0| 0 |
// |0|1| 1 |
// |1|0| 1 |
// |1|1| 0 |
int check_person(Person* people, char name[20], char surname[30], char role[15]) {
    if ( ( (strcmp(people->role, role) == 0) + (strcmp(role, "\n") == 0) ) % 2 &&
            ( (strcmp(people->name, name) == 0) + (strcmp(name, "\n") == 0) ) % 2 &&
            ( (strcmp(people->surname, surname) == 0) + (strcmp(surname, "\n") == 0) ) % 2) {
                return 0;
            }
    return NO_PERSON_FOUND;
}
