#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "main.h"
#include "stack.h"
#include "file_parser.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
    // Parse file content into 2d string array - `lines`
    char *filename = argv[1];
    char *lines[FILE_BUFF_SIZE];
    for (int i = 0; i < FILE_BUFF_SIZE; i++)
    {
        lines[i] = malloc(FILE_BUFF_SIZE * sizeof(char));
    }
    int line_count = 0;
    Status_Code error_code = fileParser_ReadFile(filename, lines, &line_count);

    switch (error_code)
    {
    case ERROR_NO_FILE_SPECIFIED:
        fprintf(stderr, "File error: No file specified");
        return 1;

    case ERROR_CANT_OPEN_FILE:
        fprintf(stderr, "File error: Can't open file '%s'\n", filename);
        return 1;

    case ERROR_EMPTY_FILE:
        fprintf(stderr, "File error: File dosen't contain any alphabetic or numeric characters\n");
        return 1;

    case ERROR_EXCEEDED_WORD_LENGTH:
        fprintf(stderr, "File error: One of the words is longer than 10 characters\n");
        return 1;

    case ERROR_EXCEEDED_TOTAL_LENGTH:
        fprintf(stderr, "File error: Total word length exceeds 100 characters\n");
        return 1;

    default:
        break;
    }

    // Prepare containers to store all valid partitions
    stack_st *partitions[MATRIX_HEIGHT];      // helper container for recursion
    stack_st *best_partitions[MATRIX_HEIGHT]; // container to store best combination
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        partitions[i] = malloc(sizeof(stack_st));
        best_partitions[i] = malloc(sizeof(stack_st));
        stack_init(partitions[i]);
        stack_init(best_partitions[i]);
    }

    // Look over all partitions, find the best (densest) one
    for (int nr_of_parts = 1; nr_of_parts <= line_count; nr_of_parts++)
    {
        matrix_findBestPartition(lines, line_count, best_partitions, partitions, nr_of_parts, 0, 0);
    }

    printf("\n===============\n");
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        stack_print(best_partitions[i]);
        printf("\n");
    }
    printf("\n===============\n");
    matrix_printBestPartitions(best_partitions);

    // Free allocated memory
    for (int i = 0; i < FILE_BUFF_SIZE; i++)
    {
        free(lines[i]);
    }
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        free(partitions[i]);
        free(best_partitions[i]);
    }

    return 0;
}
