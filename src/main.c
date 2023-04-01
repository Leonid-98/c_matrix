#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

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

    for (int j = 0; j < line_count; j++)
    {
        printf("%s\n", lines[j]);
    }

    



    return 0;
}