
#include "Person.h"

int mem_alloc_person(Person* person) {
    person->name = malloc(NAME_SIZE * sizeof(char));
    if (person->name == NULL) {
        return MEM_ALLOC_ERR;
    }
    person->surname = malloc(SURNAME_SIZE * sizeof(char));
    if (person->surname == NULL) {
        return MEM_ALLOC_ERR;
    }
    person->role = malloc(ROLE_SIZE * sizeof(char));
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

int add_person_info(Person* person, char name[NAME_SIZE], char role[ROLE_SIZE],
    char surname[SURNAME_SIZE], int importance) {
    if (person == NULL || name == NULL || role == NULL || surname == NULL) {
        return ADD_PERSON_DATA_ERR;
    }
    if (person->name == NULL || person->surname == NULL || person->role) {
        return ADD_PERSON_DATA_ERR;
    }
    if (snprintf(person->name, sizeof(person->name), "%s", name) < 0) {
        return ADD_PERSON_DATA_ERR;
    }
    if (snprintf(person->surname, sizeof(person->surname), "%s", surname) < 0) {
        return ADD_PERSON_DATA_ERR;
    }
    if (snprintf(person->role, sizeof(person->role), "%s", role) < 0) {
        return ADD_PERSON_DATA_ERR;
    }
    if (importance > 9999 || importance < 0) {
        return ADD_PERSON_DATA_ERR;
    }
    person->importance = importance;
    return 0;
}
// how this works: there are three subexpressions and ability to not enter all fields for check
// we need to check that given parameter (number, surname, role) is empty (check b: on the right)
// if it's empty, then structure check field equal to given parameter (check a: on the left) doesn't
// change anything, logic table for every of 3's subexpressions, the logic expression: (+) or mod 2
// |a|b|res|
// |0|0| 0 |
// |0|1| 1 |
// |1|0| 1 |
// |1|1| 0 |
int check_person(Person* people, char name[NAME_SIZE], char surname[SURNAME_SIZE], char role[ROLE_SIZE]) {
    if ( ( (strcmp(people->role, role) == 0) + (strcmp(role, "\n") == 0) ) % 2 &&
            ( (strcmp(people->name, name) == 0) + (strcmp(name, "\n") == 0) ) % 2 &&
            ( (strcmp(people->surname, surname) == 0) + (strcmp(surname, "\n") == 0) ) % 2) {
                return 0;
            }
    return NO_PERSON_FOUND;
}
