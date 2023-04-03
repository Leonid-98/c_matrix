#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"

void matrix_debugPrint(stack_st **stack_arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        stack_print(stack_arr[i]);
    }
    for (int i = 0; i < size; i++)
    {
        printf("(%d)", stack_strlen(stack_arr[i]));
    }
    printf("\n");
}

void matrix_compareBestPartition(stack_st **comparable_part, int comp_size, stack_st **best_part)
{
    static int best_size = 0;

    if (best_size == 0 || comp_size < best_size)
    {
        // Overwrite best combination
        best_size = comp_size;
        for (int i = 0; i < MATRIX_HEIGHT; i++)
        {
            stack_copy(comparable_part[i], best_part[i]);
        }
    }
    else if (comp_size == best_size)
    {
        // Compare square sums of two combination
        int best_sum_squared;
        int comp_sum_squared;
        for (int i = 0; i < comp_size; i++)
        {
            comp_sum_squared = stack_strlen(comparable_part[i]) * stack_strlen(comparable_part[i]);
            best_sum_squared = stack_strlen(best_part[i]) * stack_strlen(best_part[i]);
        }
        if (comp_sum_squared > best_sum_squared)
        {
            // Overwrite best combination
            best_size = comp_size;
            for (int i = 0; i < MATRIX_HEIGHT; i++)
            {
                stack_copy(comparable_part[i], best_part[i]);
            }
        }
    }
}

bool matrix_findBestPartition(char **arr, int arr_size, stack_st **best_parts, stack_st **parts, int parts_nr, int idx, int empty_cnt)
{
    bool isFits = false;

    if (idx == arr_size) // Recursion base. All elements of arr is checked
    {
        if (empty_cnt == parts_nr) // Check only partitions, where no parts are empty
        {
            isFits = true;
            for (int i = 0; i < parts_nr; i++)
            {
                isFits = isFits && stack_strlen(parts[i]) <= MATRIX_WIDTH;
            }

            if (isFits) // Check only partitions, that can be fitted into the matrix
            {
                matrix_compareBestPartition(parts, parts_nr, best_parts);
                // matrix_debugPrint(parts, parts_nr); // Uncomment, if want to see all found partitions
            }
        }
        return isFits;
    }

    for (int i = 0; i < parts_nr; i++) // Recursion step. Number os splits in recursive tree == `parts_nr`
    {
        if (stack_isEmpty(parts[i])) // Branching only one time, if checked part is empty.
        {                            // Prevent repeating combinations (i.e. will checked {{a}, {b, c}} and not {{b, c}, {a}}
            stack_push(parts[i], arr[idx]);
            isFits = isFits || matrix_findBestPartition(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt + 1);
            stack_pop(parts[i]);
            break;
        }
        else
        {
            stack_push(parts[i], arr[idx]);
            isFits = isFits || matrix_findBestPartition(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt);
            stack_pop(parts[i]);
        }
    }

    return isFits;
}

void matrix_printBestPartitions(stack_st **best_partitions)
{
    int non_empty_count = 0;
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
        if (!stack_isEmpty(best_partitions[i]))
        {
            non_empty_count++;
        }
    }

    // Sort the non-empty stacks by stack_strlen
    for (int i = 0; i < non_empty_count; i++)
    {
        int max_strlen = 0;
        int max_index = -1;
        for (int j = i; j < MATRIX_HEIGHT; j++)
        {
            if (!stack_isEmpty(best_partitions[j]))
            {
                int strlen = stack_strlen(best_partitions[j]);
                if (strlen > max_strlen)
                {
                    max_strlen = strlen;
                    max_index = j;
                }
            }
        }
        stack_st *tmp = best_partitions[i];
        best_partitions[i] = best_partitions[max_index];
        best_partitions[max_index] = tmp;
    }

    // Print matrix
    for (int i = MATRIX_HEIGHT - 1; i >= 0; i--)
    {
        if (stack_isEmpty(best_partitions[i]))
        {
            printf("%s", MATRIX_EMPTY_STRING);
        }
        else
        {
            unsigned int space_left = MATRIX_WIDTH;
            while (!stack_isEmpty(best_partitions[i]))
            {
                char *str = stack_pop(best_partitions[i]);
                printf("%s", str);
                space_left -= strlen(str);
            }
            while (space_left)
            {
                printf("%c", MATRIX_EMPTY_CHAR);
                space_left--;
            }
        }
        printf("\n");
    }
}