#include "../includes/minunit.h"
#include "../includes/file.h"
#include "../includes/game.h"
#include "../includes/labyrinth.h"
#include "../includes/display.h"

#include <stdlib.h>

char *s1, *s2, *s3, *s4, *s5;

void test_setup() {
    s1 = (char *)malloc(sizeof(char) * MESSAGE_BUFFER_SIZE);
    s2 = (char *)malloc(sizeof(char) * MESSAGE_BUFFER_SIZE);
    s3 = (char *)malloc(sizeof(char) * MESSAGE_BUFFER_SIZE);
    s4 = (char *)malloc(sizeof(char) * MESSAGE_BUFFER_SIZE);
    s5 = (char *)malloc(sizeof(char) * MESSAGE_BUFFER_SIZE);

    strcpy(s1, "normal");
    strcpy(s2, "      spaces before");
    strcpy(s3, "spaces after     ");
    strcpy(s4, "       spaces both side     ");
    strcpy(s5, "              a          ");

    trim(s1);
    trim(s2);
    trim(s3);
    trim(s4);
    trim(s5);
}
void test_teardown() {}


MU_TEST(test_unexisting_map) { mu_check(readMap(&(Map){}, "no_existing_file") == 0); }
MU_TEST(test_existing_map) { mu_check(readMap(&(Map){}, "testMap") == 1); }

MU_TEST(test_identical_coordinates) { mu_check(comparePos((Coordinate){10, 15}, (Coordinate){10, 15}) == 1); }
MU_TEST(test_different_coordinates) { mu_check(comparePos((Coordinate){5, 7}, (Coordinate){8, 15}) == 0); }
MU_TEST(test_different_lig) { mu_check(comparePos((Coordinate){5, 7}, (Coordinate){8, 7}) == 0); }
MU_TEST(test_different_col) { mu_check(comparePos((Coordinate){6, 3}, (Coordinate){6, 5}) == 0); }

MU_TEST(test_trim_normal) { mu_check(strcmp(s1, "normal") == 0); }
MU_TEST(test_trim_before) { mu_check(strcmp(s2, "spaces before") == 0); }
MU_TEST(test_trim_after) { mu_check(strcmp(s3, "spaces after") == 0); }
MU_TEST(test_trim_both) { mu_check(strcmp(s4, "spaces both side") == 0); }
MU_TEST(test_trim_size) { mu_check(strlen(s5) == 1); }


MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_unexisting_map);
    MU_RUN_TEST(test_existing_map);
    MU_RUN_TEST(test_identical_coordinates);
    MU_RUN_TEST(test_different_coordinates);
    MU_RUN_TEST(test_different_lig);
    MU_RUN_TEST(test_different_col);
    MU_RUN_TEST(test_trim_normal);
    MU_RUN_TEST(test_trim_before);
    MU_RUN_TEST(test_trim_after);
    MU_RUN_TEST(test_trim_both);
    MU_RUN_TEST(test_trim_size);
}

int main() {

    MU_RUN_SUITE(test_suite);
    MU_REPORT();

    return 0;
}