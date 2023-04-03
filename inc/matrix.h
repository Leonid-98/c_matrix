/**
 * @file matrix.h
 * @author Leonid Tšigrinski
 * @brief 
 * 
 * Matrix responds for all algorithmic actions: finding best fit and printing in the right order
 */

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_EMPTY_CHAR       '+'
#define MATRIX_EMPTY_STRING     "++++++++++"
#define MATRIX_WIDTH            10
#define MATRIX_HEIGHT           10

#include "stack.h"

/**
 * @brief Helper function.
 * Prints partitions in the format [str1, ...][str_i,...](strlen1),..(strlen_i)
 */
void matrix_debugPrint(stack_st **stack_arr, int size);

/**
 * @brief Helper function
 Compares two partitions and updates the best partition based on the following criteria:
 * - If the partition is smaller, that best, it becomes the new best.
 * - If the partition is the same, we need to consider the best partition is the one with bigger numbers
 *   Point is that partition (10, 10, 8) is better than (10, 9, 9)
 *      For that purpose, I'll use weighted mean value: sum(a*a) / sum(a).
 *      But since sum (=strlen) of the both cases would be the same, I can simply compare sum of squares. Bigger one wins
 *
 * @param comparable_part Potential new best
 * @param comp_size Comparable size
 * @param best_part Existing best
 */
void matrix_compareBestPartition(stack_st **comparable_part, int comp_size, stack_st **best_part);

/**
 * @brief
 * This function takes as an argument an array of strings (2d char array) and recursively looks over all partitions of an array
 * For each partition, function checks, is partition is valid or not, i.e. can elements be fitted into the matrix 10x10
 * For example, arr = {aa, b, cccc} can be splitted  as {{aa, b}, {cccc}} (one combination of many)
 * Returns true, is all words can be fitted into an array or not
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
 * @returns `true`, if found partition, that can fit. `false` otherwise
 */
bool matrix_findBestPartition(char **arr, int arr_size, stack_st **best_parts, stack_st **parts, int parts_nr, int idx, int empty_cnt);

/**
 * @brief
 * Function prints best partition as a matrix in decreasing order, i.e. longest string is put to the end of the matrix.
 * Empty space is replaced with +
 * Firstly, nonEmpty stack elements being sorted, then all of the stack being printed.
 *
 * @param best_partition Best combination, that found
 */
void matrix_printBestPartitions(stack_st **best_partitions);

#endif