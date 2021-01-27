/* CS240 Fall 2020
 * hw1 main function
 */

#include <stdio.h>

#include "hw1.h"

int g_arithmetic_array[ARRAY_SIZE];
int g_geometric_array[ARRAY_SIZE];

/*  This function is used to run the compute_arithmetic_series()
 *  and compute_geometric_series() functions implemented in file 
 *  hw1.c. User input is used to determine which function to run
 *  and what input is passed to it. Upon completion, the function 
 *  returns zero.
 */

int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int main() {
  int count = 0;
  int choice = 0;
  int starting_number = 0;
  int sum = 0;
  int value = 0;
  int read = 0;
  char c;

  while (choice != 3) {
    printf("-------------------------------------------------------\n");
    printf("Select a function to test:\n"
           "   1) compute_arithmetic_series()\n"
           "   2) check_arithmetic_series()\n"
           "   3) Exit\n"
           "Your choice? ");

    read = scanf("%d%c", &choice, &c);
    while ((read !=2 || c!= '\n') && clean_stdin()){
          printf("Wrong input!\n");
          printf("Your choice? ");
          read = scanf("%d%c", &choice, &c);
    }
    int limit = 0;
    int common_difference = 0;
    switch (choice) {
      case 1:
        printf("Enter a starting number: ");
        read = scanf("%d%c", &starting_number, &c);
        while ((read !=2 || c!= '\n') && clean_stdin()){
        	printf("Wrong input!\n");
        	printf("Enter a starting number: ");
        	read = scanf("%d%c", &starting_number, &c);
        }
        printf("Enter a limit: ");
        read = scanf("%d%c", &limit, &c);
        while ((read !=2 || c!= '\n') && clean_stdin()){
        	printf("Wrong input!\n");
        	printf("Enter a limit: ");
        	read = scanf("%d%c", &limit, &c);
        }
        printf("Enter a common difference: ");
        read = scanf("%d%c", &common_difference, &c);
        while ((read !=2 || c!= '\n') && clean_stdin()){
        	printf("Wrong input!\n");
        	printf("Enter a common difference: ");
        	read = scanf("%d%c", &common_difference, &c);
        }
        if (limit > ARRAY_SIZE) {
          printf("You should choose a limit less than %d!\n",
                 ARRAY_SIZE + 1);
        }
        else if (limit < 1) {
          printf("You should choose a limit larger than 0!\n");
        }
        else {
          sum = compute_arithmetic_series(starting_number, limit, common_difference);
          printf("The resulting array looks like:\n");
          for (count = 0; count < limit; count++) {
            printf("%d\t", g_arithmetic_array[count]);
            if (count % 10 == 9) {
              printf("\n");
            }
          }
          if (limit % 10 == 0) {
            printf("The sum of the series is %d\n", sum);
          }
          else {
            printf("\nThe sum of the series is %d\n", sum);
          }
        }
        break;

      case 2:
        printf("Enter a Limit: ");
        read = scanf("%d%c", &limit, &c);
        while ((read !=2 || c!= '\n') && clean_stdin()){
        	printf("Wrong input!\n");
        	printf("Enter a limit: ");
        	read = scanf("%d%c", &limit, &c);
        }
        printf("Enter numbers to put into the array.\n");
        for (count = 0; count < limit; count++) {
          printf("Element %2d: ", count+1);
          read = scanf("%d%c", &value, &c);
          while ((read !=2 || c!= '\n') && clean_stdin()){
        	printf("Wrong input!\n");
        	printf("Element %2d: ", count+1);
        	read = scanf("%d%c", &value, &c);
          }
          g_arithmetic_array[count] = value;
        }

        value = check_arithmetic_series(limit);
	if (value != 0) 
	{
	  printf("An arithmetic error was thrown!\n");
          printf("Value returned from check_arithmetic_series(%d) = %d\n", limit, value);
	}
	else 
	{
	  printf("Arithmetic Sequence is valid!\n");
          printf("Value returned from check_arithmetic_series(%d) = %d\n", limit, value);
	}
        break;

      case 3:
        printf("Goodbye!\n");
        break;

      default:
        printf("Select one of the given options...!\n");
        break;
    }
  }

  return 0;
} /* main() */
