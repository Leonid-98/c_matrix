#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#define FILE_BUFF_SIZE 64
#define MAX_WORD_LEN 10
#define MAX_CHAR_COUNT 100

typedef enum FileParser_Status_e
{
    SUCCESS,
    ERROR_NO_FILE_SPECIFIED,
    ERROR_CANT_OPEN_FILE,
    ERROR_EMPTY_FILE,
    ERROR_EXCEEDED_WORD_LENGTH,
    ERROR_EXCEEDED_TOTAL_LENGTH,
} FileParser_Status;

/**
 * @brief Reads file line by line and stored each word into 2d char array.
 * All symbols besides alphanumeric is ignored and not counted.
 * Parsing can be failed if word length > 10 or total symbol count > 100, i.e. words don't fit into the matrix
 *
 * @param filename pointer to string buffer
 * @param result pointer to 2d char array, words
 * @param line_count
 * @return FileParser_Status - enum with reading status
 */
FileParser_Status fileParser_ReadFile(char *filename, char **result, int *line_count);

#endif