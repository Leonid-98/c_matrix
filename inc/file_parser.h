#ifndef FILE_PARSER_H
#define FILE_PARSER_H

typedef enum ErrorCode_e
{
    SUCCESS,
    ERROR_NO_FILE_SPECIFIED,
    ERROR_CANT_OPEN_FILE,
    ERROR_EMPTY_FILE,
    ERROR_EXCEEDED_WORD_LENGTH,
    ERROR_EXCEEDED_TOTAL_LENGTH,
} ErrorCode;

ErrorCode parseLines(char *filename, char **result, int *line_count);

#endif