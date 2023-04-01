#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void init(stack_st *stack)
{
    stack->stack_ptr = -1;
}

int is_empty(stack_st *stack)
{
    return stack->stack_ptr == -1;
}

int is_full(stack_st *stack)
{
    return stack->stack_ptr == MAX_STACK_SIZE - 1;
}

void push(stack_st *stack, char *str)
{
    if (is_full(stack))
    {
        printf("Stack overflow!\n");
        return;
    }

    stack->stack_ptr++;
    strcpy(stack->data[stack->stack_ptr], str);
}

char *pop(stack_st *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow!\n");
        return NULL;
    }

    char *str = stack->data[stack->stack_ptr];
    stack->stack_ptr--;
    return str;
}

void print_stack(stack_st *stack)
{
    if (is_empty(stack))
    {
        printf("[]");
        return;
    }

    printf("[");
    for (int i = stack->stack_ptr; i >= 0; i--)
    {
        printf("%s", stack->data[i]);
        if (i > 0)
        {
            printf(", ");
        }
    }
    printf("]");
}