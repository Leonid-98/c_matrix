#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"

/** @brief Helper function
 Compares two partitions and updates the best partition based on the following criteria:
 * - If the partition is smaller, that best, it becomes the new best.
 * - If the partition is the same, we need to consider the best partition is the one with bigger numbers
 *   Point is that partition (10, 10, 8) is better than (10, 9, 9)
 *      For that purpose, I'll use weighted mean value: sum(a*a) / sum(a).
 *      But since sum (strlen) of the both cases would be the same, I can simply compare sum of squares. Bigger one wins

 * @param comparable_part Potential new best
 * @param comp_size Comparable size
 * @param best_part Existing best
 */
static void priv_compareBestPartition(stack_st **comparable_part, int comp_size, stack_st **best_part)
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

void matrix_findBestPartition(char **arr, int arr_size, stack_st **best_parts, stack_st **parts, int parts_nr, int idx, int empty_cnt)
{
    if (idx == arr_size) // Recursion base. All elements of arr is checked
    {
        if (empty_cnt == parts_nr) // Check only partitions, where no parts are empty
        {
            bool isFits = true;
            for (int i = 0; i < parts_nr; i++)
            {
                isFits = isFits && stack_strlen(parts[i]) <= MATRIX_WIDTH;
            }

            if (isFits) // Check only partitions, that can be fitted into the matrix
            {
                priv_compareBestPartition(parts, parts_nr, best_parts);

                /* Uncomment, if you want to see all found partitions
                for (int i = 0; i < parts_nr; i++)
                {
                    stack_print(parts[i]);
                }
                for (int i = 0; i < parts_nr; i++)
                {
                    printf("(%d)", stack_strlen(parts[i]));
                }
                printf("\n");
                */
            }
        }
        return;
    }

    for (int i = 0; i < parts_nr; i++) // Recursion step. Number os splits in recursive tree == `parts_nr`
    {
        if (stack_isEmpty(parts[i])) // Branching only one time, if checked part is empty.
        {                            // Prevent repeating combinations (i.e. will checked {{a}, {b, c}} and not {{b, c}, {a}}
            stack_push(parts[i], arr[idx]);
            matrix_findBestPartition(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt + 1);
            stack_pop(parts[i]);
            break;
        }
        else
        {
            stack_push(parts[i], arr[idx]);
            matrix_findBestPartition(arr, arr_size, best_parts, parts, parts_nr, idx + 1, empty_cnt);
            stack_pop(parts[i]);
        }
    }
}