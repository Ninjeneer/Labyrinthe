//
// Created by loan on 18/10/2019.
//

#include "../includes/minunit.h"
#include "../includes/file.h"

void test_setup() {}
void test_teardown() {}

MU_TEST(test_unexisting_map) { mu_check(readMap(&(Map){}, "no_existing_file") == 0); }
MU_TEST(test_existing_map) { mu_check(readMap(&(Map){}, "testMap") == 1); }


MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_unexisting_map);
    MU_RUN_TEST(test_existing_map);
}

int main() {

    MU_RUN_SUITE(test_suite);
    MU_REPORT();

    return 0;
}