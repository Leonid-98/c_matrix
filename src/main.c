#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "stack.h"

ErrorCode parseLines(char *filename, char **result, int *line_count)
{
    if (filename == NULL)
    {
        return ERROR_NO_FILE_SPECIFIED;
    }

    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL)
    {
        return ERROR_CANT_OPEN_FILE;
    }

    int char_count = 0;
    char read_buffer[MAX_CHARS];

    int i = 0;
    while (fgets(read_buffer, MAX_CHARS, file_ptr) != NULL)
    {
        if (read_buffer[strlen(read_buffer) - 1] == '\n')
        {
            read_buffer[strlen(read_buffer) - 1] = '\0';
        }

        if (strlen(read_buffer) > 0 && isalnum(read_buffer[0]))
        {
            if (strlen(read_buffer) > MATRIX_WIDTH)
            {
                fclose(file_ptr);
                return ERROR_EXCEEDED_WORD_LENGTH;
            }

            strcpy(result[i], read_buffer);
            char_count += strlen(result[i]);
            i++;
        }
    }
    *line_count = i;
    fclose(file_ptr);

    if (char_count == 0)
    {
        return ERROR_EMPTY_FILE;
    }
    else if (char_count > MATRIX_WIDTH * MATRIX_HEIGHT)
    {
        return ERROR_EXCEEDED_TOTAL_LENGTH;
    }

    return SUCCESS;
}

void setPartitions(char **arr, int arr_size, stack_st **set_partitions, int nr_of_parts, int index, int nos)
{
    if (index == arr_size)
    {
        if (nos == nr_of_parts)
        {
            for (int i = 0; i < nr_of_parts; i++)
            {
                stack_print(set_partitions[i]);
            }
            printf("\n");
        }
        return;
    }

    for (int i = 0; i < nr_of_parts; i++)
    {
        if (stack_isEmpty(set_partitions[i]))
        {
            stack_push(set_partitions[i], arr[index]);
            setPartitions(arr, arr_size, set_partitions, nr_of_parts, index + 1, nos + 1);
            stack_pop(set_partitions[i]);
            break;
        }
        else
        {
            stack_push(set_partitions[i], arr[index]);
            setPartitions(arr, arr_size, set_partitions, nr_of_parts, index + 1, nos);
            stack_pop(set_partitions[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    char *lines[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++)
    {
        lines[i] = malloc(MAX_CHARS * sizeof(char));
    }
    int line_count = 0;
    ErrorCode error_code = parseLines(filename, lines, &line_count);

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

    stack_st *set_partitions[MATRIX_HEIGHT];
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        set_partitions[i] = malloc(sizeof(stack_st));
        stack_init(set_partitions[i]);
    }

    for (int nr_of_parts = 1; nr_of_parts <= line_count; nr_of_parts++)
    {
        for (int i = 0; i < MATRIX_HEIGHT; i++)
        {
            stack_clear(set_partitions[i]);
        }

        setPartitions(lines, line_count, set_partitions, nr_of_parts, 0, 0);
    }

    // Free allocated memory
    for (int i = 0; i < line_count; i++)
    {
        free(lines[i]);
    }
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        free(set_partitions[i]);
    }

    return 0;
}
