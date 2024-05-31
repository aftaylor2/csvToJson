#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csvToJSON.h"

#define BUFFER_SIZE 1024

// Function to replace newline characters
void replace_newline(char *str) {
    char *pos;
    while ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}

// Function to read a CSV file and convert it to JSON
char *csv_to_json(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char *json = malloc(BUFFER_SIZE * sizeof(char));
    if (json == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(json, "[");

    // Read the first row (columns)
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        perror("Failed to read file");
        exit(EXIT_FAILURE);
    }
    replace_newline(buffer);
    char *columns = strdup(buffer);

    // Tokenize the column headers
    char *col_headers[BUFFER_SIZE];
    int col_count = 0;
    char *col = strtok(columns, ",");
    while (col) {
        col_headers[col_count++] = col;
        col = strtok(NULL, ",");
    }

    // Process each row of data
    int first_row = 1;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        replace_newline(buffer);
        if (!first_row) {
            strcat(json, ",");
        }
        strcat(json, "{");

        char *val = strtok(buffer, ",");
        for (int i = 0; i < col_count; i++) {
            if (i > 0) {
                strcat(json, ",");
            }
            strcat(json, "\"");
            strcat(json, col_headers[i]);
            strcat(json, "\":\"");
            strcat(json, val);
            strcat(json, "\"");
            val = strtok(NULL, ",");
        }
        strcat(json, "}");
        first_row = 0;
    }
    strcat(json, "]");

    fclose(file);
    free(columns);

    return json;
}
