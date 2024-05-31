#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "csvToJSON.h"

void test_csv_to_json(void) {
    const char *csv_file_path = "./data/test.csv";
    char *json_data = csv_to_json(csv_file_path);

    // Expected JSON output
    const char *expected_json =
        "[{\"firstName\":\"John\",\"lastName\":\"Doe\",\"dob\":\"1985-08-01\"},"
        "{\"firstName\":\"Jane\",\"lastName\":\"Doe\",\"dob\":\"1991-04-20\"}]";

    // Print the generated and expected JSON for debugging
    printf("Generated JSON: %s\n", json_data);
    printf("Expected JSON: %s\n", expected_json);

    // Check if the generated JSON matches the expected JSON
    if (strcmp(json_data, expected_json) != 0) {
        fprintf(
            stderr,
            "Assertion failed: generated JSON does not match expected JSON\n");
        exit(EXIT_FAILURE);
    }

    free(json_data);
}

int main(void) {
    test_csv_to_json();
    printf("All tests passed.\n");
    return 0;
}
