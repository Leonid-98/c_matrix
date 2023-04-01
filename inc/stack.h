#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100
#define MAX_STRING_SIZE 64

typedef struct
{
    char data[MAX_STACK_SIZE][MAX_STRING_SIZE];
    int stack_ptr;
} stack_st;

void init(stack_st *stack);
int is_empty(stack_st *stack);
int is_full(stack_st *stack);
void push(stack_st *stack, char *str);
char *pop(stack_st *stack);
void print_stack(stack_st *stack);

#endif