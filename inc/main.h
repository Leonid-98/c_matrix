/**
 * @file main.h
 * @author Leonid Tšigrinski
 * @brief 
 */

#ifndef MAIN_H
#define MAIN_H

#define MATRIX_WIDTH            10
#define MATRIX_HEIGHT           10
#define MATRIX_EMPTY_CHAR       '+'
#define MATRIX_EMPTY_STRING     "++++++++++"

typedef enum Status_Code_e
{
    SUCCESS = 0,
    ERROR_NO_FILE_SPECIFIED,
    ERROR_CANT_OPEN_FILE,
    ERROR_EMPTY_FILE,
    ERROR_EXCEEDED_WORD_LENGTH,
    ERROR_EXCEEDED_TOTAL_LENGTH,
    ERROR_STACK_UNDERFLOW,
    ERROR_STACK_OVERFLOW,
} Status_Code;

#endif