#ifndef HW1_H
#define HW1_H

#define ARRAY_SIZE 40
extern int g_arithmetic_array[ARRAY_SIZE];

#define ARITHMETIC_ERROR (-1)
#define ARITHMETIC_CORRECT (0)

int compute_arithmetic_series(int, int, int);
int check_arithmetic_series(int);

#endif // HW1_H
