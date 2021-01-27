/* Name: Junaid Javed, hw4.c, CS 24000, Fall 2020
 * Last updated Sep 29, 2020
 */

/* Add any includes here */
#include "hw4.h"
#include <math.h>


/*
 * add_complex takes in two complex numbers, first_complex & second_complex, and
 * returns a complex_t that is the sum of the two complex_number's
 */

complex_t add_complex(complex_t first_complex, complex_t second_complex) {
  double x = 0.0;
  double y = 0.0;

  x = first_complex.x + second_complex.x;
  y = first_complex.y + second_complex.y;

  complex_t complex_answer = {x, y};
  return complex_answer;
} /* add_complex() */

/*
 * neg_complex takes in one complex numbers, complex_number, and return a
 * complex_number that is the negative of the complex_number
 */

complex_t neg_complex(complex_t complex_number) {
  double x = 0.0;
  double y = 0.0;
  x = -1.0 * complex_number.x;
  y = -1.0 * complex_number.y;
  complex_t complex_answer = {x, y};
  return complex_answer;
} /* neg_complex() */

/*
 * sub_complex takes in two complex numbers, first_complex & second_complex, and
 * returns a complex_t that is the difference of the two complex_number's
 */

complex_t sub_complex(complex_t first_complex, complex_t second_complex) {
  return add_complex(first_complex, neg_complex(second_complex));
} /* sub_complex() */

/*
 * dot_complex takes in two complex numbers, first_complex and second_complex,
 * and return double that is the dot product of the two complex_number's
 */

double dot_complex(complex_t first_complex, complex_t second_complex) {
  double x = 0.0;
  double y = 0.0;

  x = first_complex.x * second_complex.x;
  y = first_complex.y * second_complex.y;

  return x + y;
} /* dot_complex() */

/*
 * inv_complex takes in one complex numbers, complex_number, and return a
 * complex_number that is the inverse of the complex_number
 */

complex_t inv_complex(complex_t complex_number) {
  double magnitude_squared = 0.0;
  double x = 0.0;
  double y = 0.0;

  magnitude_squared = ((complex_number.x * complex_number.x) + (complex_number.y
                       * complex_number.y));
  x = (complex_number.x / magnitude_squared);
  y = -1.0 * (complex_number.y / magnitude_squared);

  complex_t complex_answer = {x, y};
  return complex_answer;
} /* inv_complex() */

/*
 * dot_complex takes in two complex numbers, first_complex and second_complex,
 * and return complex_t that is the product of the two complex_number's
 */

complex_t mul_complex(complex_t first_complex, complex_t second_complex) {
  double x = 0.0;
  double y = 0.0;

  x = (first_complex.x * second_complex.x)
        - (first_complex.y * second_complex.y);
  y = (first_complex.x * second_complex.y)
        + (first_complex.y * second_complex.x);

  complex_t complex_answer = {x, y};
  return complex_answer;
} /* mul_complex() */

/*
 * dot_complex takes in two complex numbers, first_complex and second_complex,
 * and return complex_t that is the quotient of the two complex_number's
 */

complex_t div_complex(complex_t first_complex, complex_t second_complex) {
  return mul_complex(first_complex, inv_complex(second_complex));
} /* div_complex() */

/*
 * exp_complex takes in one complex numbers, complex_number, and return a
 * complex_number that is the computation of the complex exponential function
 * e^n where n = x+iy
 */

complex_t exp_complex(complex_t complex_number) {
  double x = 0.0;
  double y = 0.0;
  x = ((exp(complex_number.x)) * (cos(complex_number.y)));
  y = ((exp(complex_number.x)) * (sin(complex_number.y)));
  complex_t complex_answer = {x, y};
  return complex_answer;
} /* exp_complex() */

/*
 * mandelbrot takes in one complex numbers, complex_number, and return a
 * integer that is the number of calculations it takes for a {0,0} complex
 * number, current_complex_number, to become complex_number if we add
 * complex_number to the square of current_complex_number every time
 */

int mandelbrot(complex_t complex_number) {
  complex_t current_complex_number = {0, 0};
  double magnitude = 0.0;
  int number_of_calculations = 0;

  while ((magnitude <= 4.0) && (number_of_calculations < MAX_MANDELBROT)) {
    current_complex_number = add_complex(mul_complex(current_complex_number,
                              current_complex_number), complex_number);
    magnitude = dot_complex(current_complex_number, current_complex_number);
    number_of_calculations++;
  }

  return number_of_calculations;
} /* mandelbrot() */
