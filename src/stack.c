#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "stack.h"

void stack_init(stack_st *stack)
{
    stack->stack_ptr = -1;
}

bool stack_isEmpty(stack_st *stack)
{
    return stack->stack_ptr == -1;
}

bool stack_isFull(stack_st *stack)
{
    return stack->stack_ptr == MAX_STACK_SIZE - 1;
}

void stack_push(stack_st *stack, char *str)
{
    if (stack_isFull(stack))
    {
        fprintf(stderr, "Stack error: overflow\n");
        exit(ERROR_STACK_OVERFLOW);
    }

    stack->stack_ptr++;
    strcpy(stack->data[stack->stack_ptr], str);
}

char *stack_pop(stack_st *stack)
{
    if (stack_isEmpty(stack))
    {
        fprintf(stderr, "Stack error: underflow\n");
        exit(ERROR_STACK_UNDERFLOW);
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

void stack_copy(stack_st *src, stack_st *dest)
{
    dest->stack_ptr = src->stack_ptr;
    for (int i = 0; i <= src->stack_ptr; i++)
    {
        strcpy(dest->data[i], src->data[i]);
    }
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