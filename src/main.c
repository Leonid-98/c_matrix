#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

int main() {
    char lines[MAX_LINES][MAX_LENGTH];
    char filename[] = "readme.txt";

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    int i = 0;
    while (fgets(lines[i], MAX_LENGTH, file) != NULL) {
        // Remove newline character if present
        if (lines[i][strlen(lines[i])-1] == '\n') {
            lines[i][strlen(lines[i])-1] = '\0';
        }
        i++;
    }

    // Close the file
    fclose(file);

    // Print the lines stored in the array
    for (int j = 0; j < i; j++) {
        printf("%s\n", lines[j]);
    }

    return 0;
}