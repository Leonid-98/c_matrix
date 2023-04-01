#ifndef MAIN_H
#define MAIN_H

#define MAX_LINES 64
#define MAX_CHARS 64

typedef enum ErrorCode_e
{
    SUCCESS,
    ERROR_NO_FILE_SPECIFIED,
    ERROR_CANT_OPEN_FILE,
    ERROR_EMPTY_FILE,
    ERROR_EXCEEDED_WORD_LENGTH,
    ERROR_EXCEEDED_TOTAL_LENGTH,
} ErrorCode;

ErrorCode parseLines(char *filename, char result[][MAX_CHARS], int *line_count);

#endif