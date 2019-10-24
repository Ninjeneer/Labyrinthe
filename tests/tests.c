//
// Created by loan on 18/10/2019.
//

#include "../includes/minunit.h"
#include "../includes/file.h"
#include "../includes/game.h"

void test_setup() {}
void test_teardown() {}


MU_TEST(test_unexisting_map) { mu_check(readMap(&(Map){}, "no_existing_file") == 0); }
MU_TEST(test_existing_map) { mu_check(readMap(&(Map){}, "testMap") == 1); }


MU_TEST(test_identical_coordinates) { mu_check(comparePos((Coordinate){10, 15}, (Coordinate){10, 15}) == 1); }
MU_TEST(test_different_coordinates) { mu_check(comparePos((Coordinate){5, 7}, (Coordinate){8, 15}) == 0); }
MU_TEST(test_different_lig) { mu_check(comparePos((Coordinate){5, 7}, (Coordinate){8, 7}) == 0); }
MU_TEST(test_different_col) { mu_check(comparePos((Coordinate){6, 3}, (Coordinate){6, 5}) == 0); }


MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_unexisting_map);
    MU_RUN_TEST(test_existing_map);
    MU_RUN_TEST(test_identical_coordinates);
    MU_RUN_TEST(test_different_coordinates);
    MU_RUN_TEST(test_different_lig);
    MU_RUN_TEST(test_different_col);
}

int main() {

    MU_RUN_SUITE(test_suite);
    MU_REPORT();

    return 0;
}