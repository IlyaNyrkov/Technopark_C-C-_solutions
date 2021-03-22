#include "Person.h"

int show_person_info(Person* person) ;

int show_info_depending(Person* people, size_t n, char name[NAME_SIZE],
    char surname[SURNAME_SIZE], char role[ROLE_SIZE]);

int main(int argc, char* argv[]) {
    char people_count[DEF_NUM_SIZE] = {""};  // participants count and level of importance is in [0; 10000)
    do {
        printf("Enter count of project participants: ");
        scanf("%4s", people_count);
    } while (check_number(people_count) == WRONG_NUM_ERR);

    int n = atoi(people_count);
    Person* people = malloc(n * sizeof(Person));
    if (people == NULL) {
        fprintf(stderr, "Cannot alloc memory for participants\n");
        return MEM_ALLOC_ERR;
    }
    char* person_buffer = malloc(CMD_LINE_SIZE * sizeof(char));
    if (person_buffer == NULL) {
        fprintf(stderr, "Cannot alloc memory for person info buffer\n");
        free(people);
        return MEM_ALLOC_ERR;
        }

    for (int i = 0; i < n; i++) {
        if (mem_alloc_person(&people[i])) {
            fprintf(stderr, "Cannot allocate memory for person's data\n");
            free(people);
            free(person_buffer);
            return MEM_ALLOC_ERR;
        }
        char name[NAME_SIZE];
        char surname[SURNAME_SIZE];
        char role[ROLE_SIZE];
        int importance_level;
        do {
            printf("Enter %dst person's data, format is:  name;surname;role;importance\n", i+1);
            scanf("%79s", person_buffer);
        } while (parse_person_data(person_buffer, name, surname, role, &importance_level) ==
            WRONG_PERSON_DATA_ERR);
            add_person_info(&people[i], name, role, surname, importance_level);
    }
    free(person_buffer);
    person_buffer = NULL;
    char* command_buffer = malloc(CMD_LINE_SIZE * sizeof(char));
    if (command_buffer == NULL) {
        fprintf(stderr, "Cannot alloc memory for command buffer\n");
        return MEM_ALLOC_ERR;
    }
    char name[NAME_SIZE] = "\n";
    char surname[SURNAME_SIZE] = "\n";
    char role[ROLE_SIZE] = "\n";
    do {
        printf("Enter your search criteria: Format is name;surname;role\n");
        scanf("%79s", command_buffer);
    } while (parse_command(command_buffer, name, surname, role) == WRONG_COMMAND_ERR);
    show_info_depending(people, n, name, surname, role);
    free(people);
    people = NULL;
    free(command_buffer);
    command_buffer = NULL;
    return 0;
}

int show_person_info(Person* person) {
    if (person == NULL) {
        return MEM_ALLOC_ERR;
    }
    printf("name: %s\nsurname: %s\nrole: %s\nimportance: %d\n",
        person->name, person->surname, person->role, person->importance);
}

int show_info_depending(Person* people, size_t n, char name[NAME_SIZE],
    char surname[SURNAME_SIZE], char role[ROLE_SIZE]) {
    if (people == NULL || name == NULL || surname == NULL || role == NULL) {
        return MEM_ALLOC_ERR;
    }
    int elem_cnt = 0;
    for (size_t i = 0; i < n; i++) {
        if (check_person(&people[i], name, surname, role) != NO_PERSON_FOUND) {
                printf("person's info:\n");
                if (show_person_info(&people[i]) == MEM_ALLOC_ERR) {
                    return MEM_ALLOC_ERR;
                }
                elem_cnt++;
            }
    }
    if (elem_cnt == 0) {
        printf("No people found with name: %s surname: %s, role: %s\n", name, surname, role);
    }
    return 0;
}