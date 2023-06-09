/**
 * @file file_parser.h
 * @author Leonid Tšigrinski
 * @brief 
 * 
 * Parses content of a file into char array. 
 * NB!!! Be careful of white spaces inside lines with words. 
 * Fully empty or white-spaced lines are ignored, but "normal" spaces inside words considered as part of the word
 */

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "main.h"

#define FILE_BUFF_SIZE      64
#define MAX_WORD_LEN        MATRIX_WIDTH
#define MAX_CHAR_COUNT      MATRIX_WIDTH * MATRIX_HEIGHT


/**
 * @brief Reads file line by line and stored each word into 2d char array.
 * All symbols besides alphanumeric is ignored and not counted.
 * Parsing can be failed if word length > 10 or total symbol count > 100, i.e. words don't fit into the matrix
 *
 * @param filename pointer to string buffer
 * @param result pointer to 2d char array, words
 * @param line_count
 * @return Status_Code - enum with reading status
 */
Status_Code fileParser_ReadFile(char *filename, char **result, int *line_count);

#endif