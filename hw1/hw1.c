/* Junaid Javed, hw1.c, CS 24000, Fall 2020
 * Last updated June 16, 2020
 */

/* Add any includes here */

#include "hw1.h"

/* Define compute_arithmetic_series here*/

int compute_arithmetic_series(int first_number, int number_of_elements, int common_difference) {
    if (number_of_elements <= 0 || number_of_elements > ARRAY_SIZE) {
        return ARITHMETIC_ERROR;
    }
    g_arithmetic_array[0] = first_number;
    int sum = first_number;
    for (int i = 1; i < number_of_elements; i++) {
        int new_number = first_number + (i) * common_difference;
        g_arithmetic_array[i] = new_number;
        sum += new_number;
    }
    return sum;
} /* compute_arithmetic_series() */

/* Define check_arithmetic_series here*/

int check_arithmetic_series(int limit) {
    if (limit <= 0 || limit > ARRAY_SIZE) {
        return ARITHMETIC_ERROR;
    }
    if (limit == 1) {
        return ARITHMETIC_CORRECT;
    }
    int difference = g_arithmetic_array[1] - g_arithmetic_array[0];
    for (int current_index = 1; current_index < limit; current_index++) {
        if (g_arithmetic_array[current_index] - g_arithmetic_array[current_index - 1] != difference) {
            return current_index;
        }
    }
    return ARITHMETIC_CORRECT;
} /* check_arithmetic_series() */

/* Remember, you don't need a main function!
 * It is provided by hw1_main.c or hw1_test.o
 */
