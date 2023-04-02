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
 * all such partitions, how array can be splitted and fit into the matrix.
 * By split, I mean set partition: arr = {aa, b, cccc} can be splitted for example as {{aa, b}, {cccc}}, and each element will fit into
 * the matrix
 *
 * @param arr all parsed words from file
 * @param arr_size line count
 * @param partitions splitted pieces of `arr`
 * @param nr_of_parts into how many pieces `arr` would be splitted
 * @param index curren inspected element
 * @param empty_count helps to prevent repeats such {{a}, {b, c}} and {{b, c}, {a}}. Will be counter only one such combination
 */
void findValidPartitions(char **arr, int arr_size, stack_st **partitions, int nr_of_parts, int index, int empty_count)
{
    if (index == arr_size)
    {
        if (empty_count == nr_of_parts)
        {
            bool isFits = true;
            for (int i = 0; i < nr_of_parts; i++)
            {
                isFits = isFits && stack_strlen(partitions[i]) <= MATRIX_WIDTH;
            }

            if (isFits)
            {
                for (int i = 0; i < nr_of_parts; i++)
                {
                    stack_print(partitions[i]);
                }
                printf("\n");
            }
        }
        return;
    }

    for (int i = 0; i < nr_of_parts; i++)
    {
        if (stack_isEmpty(partitions[i]))
        {
            stack_push(partitions[i], arr[index]);
            findValidPartitions(arr, arr_size, partitions, nr_of_parts, index + 1, empty_count + 1);
            stack_pop(partitions[i]);
            break;
        }
        else
        {
            stack_push(partitions[i], arr[index]);
            findValidPartitions(arr, arr_size, partitions, nr_of_parts, index + 1, empty_count);
            stack_pop(partitions[i]);
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
    stack_st *partitions[MATRIX_HEIGHT]; // array os stacks {stack1, stack2}
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        partitions[i] = malloc(sizeof(stack_st));
        stack_init(partitions[i]);
    }

    // Look over all partitions, find the best (densest) one
    for (int nr_of_parts = 1; nr_of_parts <= line_count; nr_of_parts++)
    {
        for (int i = 0; i < MATRIX_HEIGHT; i++)
        {
            stack_clear(partitions[i]);
        }

        findValidPartitions(lines, line_count, partitions, nr_of_parts, 0, 0);
    }

    // Free allocated memory
    for (int i = 0; i < FILE_BUFF_SIZE; i++)
    {
        free(lines[i]);
    }
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        free(partitions[i]);
    }

    return 0;
}
