#include "gtest/gtest.h"
#include "count_predicate.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int error = RUN_ALL_TESTS();
    return error;
}