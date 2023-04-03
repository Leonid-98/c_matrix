

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 10

#include "stack.h"

/**
 * @brief This function takes as an argument an array of strings (2d char array) and recursively looks over all partitions of an array
 * For each partition, function checks, is partition is valid or not, i.e. can elements be fitted into the matrix 10x10
 * For example, arr = {aa, b, cccc} can be splitted  as {{aa, b}, {cccc}} (one combination of many)
 *
 * Recursion base:
 * When particular tree end reached, then I look over partitions and decide, is it the best one (tidiest one).
 *
 * Recursive step:
 * There are `parts_nr` of splits for each step. In order to reduce nr of steps, I go only path, when particular partition contains any elements.
 * Example of a tree with `parts_nr` = 2 and arr = {a, b}
 *
 *                  [ ][ ]                                                                                 [ ][ ]
 *           [a][ ] /   \ [ ][a]           As you can see, there are "mirrored elemetns"            [a][ ] /   x [ ][a]
 *            /   \        /    \          and results with empty parts                            x   \        x    x
 *     [a,b][ ]   [a][b] [b][a] [][b,a]    If I go by path, when part is not empty, I        [a,b][ ] [a][b] [b][a] [][b,a]
 *                                         can solve this issue
 *
 * @param arr all parsed words from file
 * @param arr_size words count
 * @param best_parts tidiest combination of parts
 * @param parts splitted pieces of `arr`
 * @param parts_nr into how many pieces `arr` would be splitted (recursion branch value)
 * @param idx curren inspected element
 * @param empty_cnt helps to prevent showing splits with empty parts, e.g. {{a, b},{}}
 */
void matrix_findBestPartition(char **arr, int arr_size, stack_st **best_parts, stack_st **parts, int parts_nr, int idx, int empty_cnt);

#endif