#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "stack.h"

ErrorCode parseLines(char *filename, char result[][MAX_CHARS], int *line_count)
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
            if (strlen(read_buffer) > 10)
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
    else if (char_count > 100)
    {
        return ERROR_EXCEEDED_TOTAL_LENGTH;
    }

    return SUCCESS;
}

void setPartitions(char arr[][MAX_CHARS], int arr_size, int index, stack_st** partitions, int nr_of_partitions)
{
    if (index == arr_size) {
        print_stack(partitions[0]);
        print_stack(partitions[1]);
        printf("\n");
        return;
    }

    for (int i = 0; i < nr_of_partitions; i++)
    {
        push(partitions[i], arr[index]);
        setPartitions(arr, arr_size, index + 1, partitions, nr_of_partitions);
        pop(partitions[i]);
    }
}

int main(int argc, char *argv[])
{
    
    char *filename = argv[1];
    char lines[MAX_LINES][MAX_CHARS];
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

    const int K = 3;

    stack_st s1, s2, s3;
    init(&s1);
    init(&s2);
    init(&s3);
    stack_st* stacks[3] = {&s1, &s2, &s3};

    setPartitions(lines, line_count, 0, stacks, K);
    return 0;
}
