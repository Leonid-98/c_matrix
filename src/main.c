#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "main.h"
#include "stack.h"
#include "file_parser.h"
#include "logic.h"

/**
 * @brief This function takes as an argument an array of strings (2d char array) and stores to the `result`
 * all such parts, how array can be splitted and fit into the matrix.
 * By split, I mean set partition: arr = {aa, b, cccc} can be splitted for example as {{aa, b}, {cccc}}, and each element will fit into
 * the matrix
 *
 * @param arr all parsed words from file
 * @param arr_size line count
 * @param best_parts tidiest combination of parts
 * @param parts splitted pieces of `arr`
 * @param parts_nr into how many pieces `arr` would be splitted
 * @param idx curren inspected element
 * @param empty_cnt helps to prevent repeats such {{a}, {b, c}} and {{b, c}, {a}}. Will be counter only one such combination
 */
void findValidPartitions(char **arr, int arr_size, stack_st **best_parts, stack_st **parts, int parts_nr, int idx, int empty_cnt)
{
    if (idx == arr_size)
    {
        if (empty_cnt == parts_nr)
        {
            bool isFits = true;
            for (int i = 0; i < parts_nr; i++)
            {
                isFits = isFits && stack_strlen(parts[i]) <= MATRIX_WIDTH;
            }

            if (isFits)
            {
                for (int i = 0; i < parts_nr; i++)
                {
                    stack_copy(parts[i], best_parts[i]);
                    stack_print(parts[i]);
                }
                for (int i = 0; i < parts_nr; i++)
                {
                    // printf("(%d)", stack_strlen(parts[i]));
                }
                printf("\n");
            }
        }
        return;
    }

    for (int i = 0; i < parts_nr; i++)
    {
        if (stack_isEmpty(parts[i]))
        {
            stack_push(parts[i], arr[idx]);
            findValidPartitions(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt + 1);
            stack_pop(parts[i]);
            break;
        }
        else
        {
            stack_push(parts[i], arr[idx]);
            findValidPartitions(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt);
            stack_pop(parts[i]);
        }
    }
}

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
    FileParser_Status error_code = fileParser_ReadFile(filename, lines, &line_count);

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
        for (int i = 0; i < MATRIX_HEIGHT; i++)
        {
            stack_clear(partitions[i]);
        }

        findValidPartitions(lines, line_count, best_partitions, partitions, nr_of_parts, 0, 0);
    }

    printf("\n===============\n");
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
        stack_print(best_partitions[i]);
        printf("\n");
    }

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
