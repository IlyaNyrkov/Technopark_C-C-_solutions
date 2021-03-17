#include "gtest/gtest.h"
extern "C" {
    #include "../include/Person.h"
    #include "../include/CheckInput.h"
}
TEST(person_memory_allocation, malloc_test) {
    Person* person = (Person*)malloc(sizeof(Person));
    EXPECT_EQ(mem_alloc_person(person), 0);
    free(person->name);
    free(person->surname);
    free(person->role);
    free(person);
}

TEST(person_memory_allocation, fill_after_alloc) {
    Person* person = (Person*)malloc(sizeof(Person));
    const char name[20] = "maxim";
    const char surname[30] = "alexeevich";
    const char role[15] = "developer";
    int importance = 100;

    EXPECT_EQ(mem_alloc_person(person), 0);

    strcpy(person->name, name);
    strcpy(person->surname, surname);
    strcpy(person->role, role);
    person->importance = importance;

    EXPECT_EQ(strcmp(person->name, name), 0);
    EXPECT_EQ(strcmp(person->surname, surname), 0);
    EXPECT_EQ(strcmp(person->role, role), 0);
    EXPECT_EQ(person->importance, importance);

    free(person->name);
    free(person->surname);
    free(person->role);
    free(person);
}

TEST(person_memory_free, person_and_fields_exist) {
    Person* person = (Person*)malloc(sizeof(Person));
    person->name = (char*)malloc(20 * sizeof(char));
    person->surname = (char*)malloc(30 * sizeof(char));
    person->role = (char*)malloc(15 * sizeof(char));
    EXPECT_EQ(mem_free_person(person), 0);
    free(person);
}

TEST(person_memory_free, person_and_one_filled_exist) {
    Person* person = (Person*)malloc(sizeof(Person));
    person->name = (char*)malloc(20 * sizeof(char));
    person->surname = NULL;
    person->role = NULL;
    char* copy_name = person->name;
    mem_free_person(person);
    EXPECT_NE(person->name, copy_name);
    free(person);
}

TEST(person_memory_free, person_all_fields_exist) {
    Person* person = (Person*)malloc(sizeof(Person));
    person->name = (char*)malloc(20 * sizeof(char));
    char* copy_name = person->name;
    person->surname = (char*)malloc(30 * sizeof(char));
    char* copy_surname = person->surname;
    person->role = (char*)malloc(15 * sizeof(char));
    char* copy_role = person->role;
    mem_free_person(person);
    EXPECT_NE(person->name, copy_name);
    EXPECT_NE(person->surname, copy_surname);
    EXPECT_NE(person->role, copy_role);
    free(person);
}

TEST(person_add_data, null_person) {
    Person* person = NULL;
    char name[20] = "maxim";
    char surname[30] = "alexeevich";
    char role[15] = "developer";
    ASSERT_EQ(add_person_info(person, name, role, surname, 100), MEM_ALLOC_ERR);
}

TEST(person_add_data, null_fields_person) {
    Person* person = (Person*)malloc(sizeof(Person));
    person->name = NULL;
    person->surname = NULL;
    person->role = NULL;
    char name[20] = "maxim";
    char surname[30] = "alexeevich";
    char role[15] = "developer";
    EXPECT_EQ(add_person_info(person, name, role, surname, 100), MEM_ALLOC_ERR);
    free(person);
}

TEST(Check_number, negative_number) {
    char number1[3] = "-1";
    ASSERT_EQ(check_number(number1), WRONG_NUM_ERR);
    char number2[5] = "-434";
    ASSERT_EQ(check_number(number2), WRONG_NUM_ERR);
}

TEST(Check_number, wrong_size_number) {
    char number1[6] = "10000";
    ASSERT_EQ(check_number(number1), WRONG_NUM_ERR);
    char number2[1] = "";
    ASSERT_EQ(check_number(number2), WRONG_NUM_ERR);
}

TEST(Check_number, null_number) {
    char* number = NULL;
    ASSERT_EQ(check_number(number), WRONG_NUM_ERR);
}

TEST(Check_number, not_a_number) {
    char number1[2] = "a";
    ASSERT_EQ(check_number(number1), WRONG_NUM_ERR);
    char number2[4] = "aba";
    ASSERT_EQ(check_number(number2), WRONG_NUM_ERR);
    char number3[4] = "21a";
    ASSERT_EQ(check_number(number3), WRONG_NUM_ERR);
    char number4[5] = "-3a1";
    ASSERT_EQ(check_number(number4), WRONG_NUM_ERR);
}

TEST(Parse_person_data, all_fields_exist) {
    char buffer[60] = "Ilya;Nyrkov;Developer;100";
    char name_result[5] = "Ilya";
    char surname_result[7] = "Nyrkov";
    char role_result[10] = "Developer";
    int importance_result = 100;

    char name[20];
    char surname[30];
    char role[15];
    int importance;
    parse_person_data(buffer, name, surname, role, &importance);
    ASSERT_TRUE(strcmp(name, name_result) == 0 &&
        strcmp(surname, surname_result) == 0 && strcmp(role, role_result) == 0 && 
        importance_result == importance);
}

TEST(Parse_person_data, fields_missing_1) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = ";Nyrkov;Developer;100";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, fields_missing_2_second_fourth) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "Ilya;;Developer;";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, fields_missing_3_all) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = ";;;";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, wrong_importance_1) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "Ilya;Nyrkov;Developer;vcs";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, wrong_importance_2) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "Ilya;Nyrkov;Developer;-100";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, wrong_importance_3) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "Ilya;Nyrkov;Developer;100000";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, wrong_semicolon_count) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "Ilya;NyrkovDeveloper;100000";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, cat_on_keyboard) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "et12312gbrHebnheerhr";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_person_data, elon_musk_son_name) {
    char name[20];
    char surname[30];
    char role[15];
    int importance;
    char buffer[60] = "X AE A-12;MUSK;Developer;1000";
    ASSERT_EQ(parse_person_data(buffer, name, surname, role, &importance),
        WRONG_PERSON_DATA_ERR);
}

TEST(Parse_command, correct_input) {
    char command_line[60] = "Ilya;Nyrkov;Developer";
    char name_res[20] = "Ilya";
    char surname_res[30] = "Nyrkov";
    char role_res[15] = "Developer";
    char name[20];
    char surname[30];
    char role[15];
    ASSERT_TRUE(parse_command(command_line, name, surname, role) == 0);
    ASSERT_TRUE((strcmp(name, name_res) == 0) && (strcmp(surname, surname_res) == 0) &&
        (strcmp(role, role_res) == 0));
}

TEST(Parse_command, first_parameter_missing) {
    char command_line[80] = ";Nyrkov;Developer";
    char name_res[20] = "\n";
    char surname_res[30] = "Nyrkov";
    char role_res[15] = "Developer";
    char name[20] = "\n";
    char surname[30] = "\n";
    char role[15] = "\n";
    EXPECT_TRUE(parse_command(command_line, name, surname, role) == 0);
    EXPECT_TRUE((strcmp(name, name_res) == 0) && (strcmp(surname, surname_res) == 0) &&
        (strcmp(role, role_res) == 0));
}

TEST(Parse_command, second_parameter_missing) {
    char command_line[80] = "Ilya;;Developer";
    char name_res[20] = "Ilya";
    char surname_res[30] = "\n";
    char role_res[15] = "Developer";
    char name[20] = "\n";
    char surname[30] = "\n";
    char role[15] = "\n";
    EXPECT_TRUE(parse_command(command_line, name, surname, role) == 0);
    EXPECT_TRUE((strcmp(name, name_res) == 0) && (strcmp(surname, surname_res) == 0) &&
        (strcmp(role, role_res) == 0));
}

TEST(Parse_command, third_parameter_missing) {
    char command_line[80] = "Ilya;Nyrkov;";
    char name_res[20] = "Ilya";
    char surname_res[30] = "Nyrkov";
    char role_res[15] = "\n";
    char name[20] = "\n";
    char surname[30] = "\n";
    char role[15] = "\n";
    EXPECT_TRUE(parse_command(command_line, name, surname, role) == 0);
    EXPECT_TRUE((strcmp(name, name_res) == 0) && (strcmp(surname, surname_res) == 0) &&
        (strcmp(role, role_res) == 0));
}

TEST(parse_command, cat_on_keyboard) {
    char command_line[80] = "ahnwyjrthstna54ntterhfb";
    char name[20] = "\n";
    char surname[30] = "\n";
    char role[15] = "\n";
    ASSERT_EQ(parse_command(command_line,name, surname, role), WRONG_COMMAND_ERR);
}

TEST(Check_person, no_parameters) {
    Person person;
    person.name = (char*)malloc(20 * sizeof(char));
    person.surname = (char*)malloc(30 * sizeof(char));
    person.role = (char*)malloc(15 * sizeof(char));
    strcpy(person.name, "Ilya");
    strcpy(person.surname, "Nyrkov");
    strcpy(person.role, "Developer");
    person.importance = 100;
    char empty_name[20] = "\n";
    char empty_surname[30] = "\n";
    char empty_role[15] = "\n";
    EXPECT_TRUE(check_person(&person, empty_name, empty_surname, empty_role) == 0);
    free(person.name);
    free(person.surname);
    free(person.role);
}

TEST(Check_person, not_all_parameters) {
    Person person;
    person.name = (char*)malloc(20 * sizeof(char));
    person.surname = (char*)malloc(30 * sizeof(char));
    person.role = (char*)malloc(15 * sizeof(char));
    strcpy(person.name, "Ilya");
    strcpy(person.surname, "Nyrkov");
    strcpy(person.role, "Developer");
    person.importance = 100;
    char empty_name[20] = "\n";
    char empty_surname[30] = "\n";
    char role[15] = "Developer";
    char role2[15] = "Manager";
    char surname[30] = "Nyrkov";
    char surname2[30] = "Pushkin";
    char name[20] = "Ilya";
    char name2[20] = "Alex";
    EXPECT_TRUE(check_person(&person, empty_name, empty_surname, role) == 0);
    EXPECT_TRUE(check_person(&person, name, empty_surname, role) == 0);
    EXPECT_TRUE(check_person(&person, empty_name, surname, role) == 0);
    EXPECT_TRUE(check_person(&person, empty_name, empty_surname, role2) == NO_PERSON_FOUND);
    EXPECT_TRUE(check_person(&person, name2, empty_surname, role2) == NO_PERSON_FOUND);
    EXPECT_TRUE(check_person(&person, empty_name, surname2, role2) == NO_PERSON_FOUND);
    free(person.name);
    free(person.surname);
    free(person.role);
}

TEST(Check_person, all_parameters) {
    Person person;
    person.name = (char*)malloc(20 * sizeof(char));
    person.surname = (char*)malloc(30 * sizeof(char));
    person.role = (char*)malloc(15 * sizeof(char));
    strcpy(person.name, "Ilya");
    strcpy(person.surname, "Nyrkov");
    strcpy(person.role, "Developer");
    person.importance = 100;
    char role[15] = "Developer";
    char role2[15] = "Manager";
    char surname[30] = "Nyrkov";
    char surname2[30] = "Pushkin";
    char name[20] = "Ilya";
    char name2[20] = "Alex";
    EXPECT_TRUE(check_person(&person, name, surname, role) == 0);
    EXPECT_TRUE(check_person(&person, name2, surname2, role2) == NO_PERSON_FOUND);
    free(person.name);
    free(person.surname);
    free(person.role);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}