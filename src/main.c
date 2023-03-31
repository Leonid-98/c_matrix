#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(int argc, char *argv[])
{
    char *filename_ptr = "readme.txt";
    FILE *file_ptr = fopen(filename_ptr, "r");

    if (file_ptr == NULL)
    {
        printf("Error: could not open file %s", filename_ptr);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, file_ptr))
        printf("%s", buffer);

    // close the file
    fclose(file_ptr);

    return 0;
}