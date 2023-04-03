#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "file_parser.h"

Status_Code fileParser_ReadFile(char *filename, char **result, int *line_count)
{
    if (filename == NULL)
    {
        return ERROR_NO_FILE_SPECIFIED;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return ERROR_CANT_OPEN_FILE;
    }

    int char_count = 0;
    char file_buffer[FILE_BUFF_SIZE];

    int i = 0;
    while (fgets(file_buffer, FILE_BUFF_SIZE, file) != NULL)
    {
        if (file_buffer[strlen(file_buffer) - 1] == '\n')
        {
            file_buffer[strlen(file_buffer) - 1] = '\0';
        }

        if (strlen(file_buffer) > 0 && isalnum(file_buffer[0]))
        {
            if (strlen(file_buffer) > MAX_WORD_LEN)
            {
                fclose(file);
                return ERROR_EXCEEDED_WORD_LENGTH;
            }

            strcpy(result[i], file_buffer);
            char_count += strlen(result[i]);
            i++;
        }
    }
    *line_count = i;
    fclose(file);

    if (char_count == 0)
    {
        return ERROR_EMPTY_FILE;
    }
    else if (char_count > MAX_CHAR_COUNT)
    {
        return ERROR_EXCEEDED_TOTAL_LENGTH;
    }

    return SUCCESS;
}