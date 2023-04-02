#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100
#define MAX_STRING_SIZE 64

typedef struct
{
    char data[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int stack_ptr;
} stack_st;

void stack_init(stack_st *stack);
int stack_isEmpty(stack_st *stack);
int stack_isFull(stack_st *stack);
void stack_push(stack_st *stack, char *str);
char *stack_pop(stack_st *stack);
void stack_clear(stack_st *stack);
int stack_strlen(stack_st *stack);
void stack_print(stack_st *stack);

#endif