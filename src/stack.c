#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void stack_init(stack_st *stack)
{
    stack->stack_ptr = -1;
}

int stack_isEmpty(stack_st *stack)
{
    return stack->stack_ptr == -1;
}

int stack_isFull(stack_st *stack)
{
    return stack->stack_ptr == MAX_STACK_SIZE - 1;
}

void stack_push(stack_st *stack, char *str)
{
    if (stack_isFull(stack))
    {
        printf("Stack overflow!\n");
        return;
    }

    stack->stack_ptr++;
    strcpy(stack->data[stack->stack_ptr], str);
}

char *stack_pop(stack_st *stack)
{
    if (stack_isEmpty(stack))
    {
        printf("Stack underflow!\n");
        return NULL;
    }

    char *str = stack->data[stack->stack_ptr];
    stack->stack_ptr--;
    return str;
}

void stack_clear(stack_st *stack)
{
    stack->stack_ptr = -1;
}

int stack_strlen(stack_st *stack) 
{
    int sum = 0;
    for (int i = stack->stack_ptr; i >= 0; i--)
    {
        sum += strlen(stack->data[i]);
    }
    return sum;
}

void stack_print(stack_st *stack)
{
    if (stack_isEmpty(stack))
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