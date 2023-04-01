#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 64
#define MAX_CHARS 64

int main(int argc, char *argv[])
{
    char *filename_ptr = argv[1];
    if (filename_ptr == NULL)
    {
        fprintf(stderr, "Error: No file specified");
        exit(1);
    }

    FILE *file_ptr = fopen(filename_ptr, "r");
    if (file_ptr == NULL)
    {
        fprintf(stderr, "Error: Can't open file '%s'\n", filename_ptr);
        exit(1);
    }



    char words[MAX_LINES][MAX_CHARS];
    int line_count = 0;
    int char_count = 0;
    char read_buffer[MAX_CHARS];
    while (fgets(read_buffer, MAX_CHARS, file_ptr) != NULL)
    {
        if (read_buffer[strlen(read_buffer) - 1] == '\n')
        {
            read_buffer[strlen(read_buffer) - 1] = '\0';
        }
        if (strlen(read_buffer) > 0 && isalnum(read_buffer[0]))
        {
            // Check if word length is less than or equal to 10
            if (strlen(read_buffer) > 10)
            {
                fprintf(stderr, "Error: word '%s' is longer than 10 characters\n", read_buffer);
                exit(1);
            }
            // Add word to the lines array and update total length
            strcpy(words[line_count], read_buffer);
            char_count += strlen(words[line_count]);
            line_count++;
        }
    }

    fclose(file_ptr);

    // Check total word lenght
    if (char_count == 0)
    {
        fprintf(stderr, "Error: File dosen't contain any alphabetic or numeric characters\n");
        return 1;
    }
    else if (char_count > 100)
    {
        fprintf(stderr, "Error: total word length exceeds 100 characters\n");
        return 1;
    }

    for (int j = 0; j < line_count; j++)
    {
        printf("%s\n", words[j]);
    }

    return 0;
}