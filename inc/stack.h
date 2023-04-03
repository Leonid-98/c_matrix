#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define MAX_STACK_SIZE 128
#define MAX_STRING_SIZE 64

/** @brief Stack data structure, but instead of numbers, it takes char array (strings) as an element */
typedef struct
{
    char data[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int stack_ptr;
} stack_st;

void stack_init(stack_st *stack);
bool stack_isEmpty(stack_st *stack);
bool stack_isFull(stack_st *stack);
void stack_push(stack_st *stack, char *str);
char *stack_pop(stack_st *stack);

/** @brief Restores stack ptr to the beginning. Keeps data memory allocated */
void stack_clear(stack_st *stack);

/** @brief Returns total strlen of each element of the stack */
int stack_strlen(stack_st *stack);

/** @brief Copies content from one stack to another */
void stack_copy(stack_st *src, stack_st *dest);

/** @brief Prints stack in the format "[Str1, Str2, ...]" */
void stack_print(stack_st *stack);

#endif