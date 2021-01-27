/* HW6 Main Function
 * CS24000, Fall 2020
 */

#include <stdio.h>
#include <string.h>
#include "hw6.h"

/*
 * This function is to check the position entry
 */

static char * optional_position(knight_t * i) {
  if (!i) {
    return NULL;
  }
  return i->position;
} /* optional_position() */

/*
 * This function is to check the color entry
 */

static char * optional_color(knight_t * i) {
  if (!i) {
    return NULL;
  }
  return i->color;
} /* optional_color() */

/*
 * This function is used to print the informatio for each knight
 */

static void print_knight_piece(knight_t i) {
  printf("{\n"
      "  position: '%s'\n"
      "  color: '%s'\n"
      "\n"
      "  top_right: %s\n"
      "  top_left: %s\n"
      "  bottom_right: %s\n"
      "  bottom_left: %s\n"
      "  right_top: %s\n"
      "  right_bottom: %s\n"
      "  left_top: %s\n"
      "  left_bottom: %s\n"
      "\n"
      "  top_right_ptr: %p (%s, %s)\n"
      "  top_left_ptr: %p (%s, %s)\n"
      "  bottom_right_ptr: %p (%s, %s)\n"
      "  bottom_left_ptr: %p (%s, %s)\n"
      "  right_top_ptr: %p (%s, %s)\n"
      "  right_bottom_ptr: %p (%s, %s)\n"
      "  left_top_ptr: %p (%s, %s)\n"
      "  left_bottom_ptr: %p (%s, %s)\n"
      "}\n",
      i.position, i.color, i.top_right, i.top_left, i.bottom_right,
      i.bottom_left,
      i.right_top, i.right_bottom, i.left_top, i.left_bottom,
      i.top_right_ptr, optional_position(i.top_right_ptr),
      optional_color(i.top_right_ptr),
      i.top_left_ptr, optional_position(i.top_left_ptr),
      optional_color(i.top_left_ptr),
      i.bottom_right_ptr, optional_position(i.bottom_right_ptr),
      optional_color(i.bottom_right_ptr),
      i.bottom_left_ptr, optional_position(i.bottom_left_ptr),
      optional_color(i.bottom_left_ptr),
      i.right_top_ptr, optional_position(i.right_top_ptr),
      optional_color(i.right_top_ptr),
      i.right_bottom_ptr, optional_position(i.right_bottom_ptr),
      optional_color(i.right_bottom_ptr),
      i.left_top_ptr, optional_position(i.left_top_ptr),
      optional_color(i.left_top_ptr),
      i.left_bottom_ptr, optional_position(i.left_bottom_ptr),
      optional_color(i.left_bottom_ptr)
   );
} /* print_knight_piece() */

/*
 * This function is used to read input from console
 */

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return 1;
} /* clean_stdin() */


/*
 * Here is the main function
 */

int main() {
  char c = ' ';
  int read = 0;
  char filename[100] = "";
  char pos[MAX_POSITION_LEN] = "";
  char row[MAX_POSITION_LEN - 1] = "";
  int num = 0;
  int int_result = 0;
  int count = 0;
  int chess_pieces[MAX_KNIGHT_COUNT] = {0};

  while (1) {
    printf("-------------------------------------------------------------\n");
    printf("0) Quit\n"
           "1) read_knights()\n"
           "2) establish_game_board()\n"
           "3) Print an array entry\n"
           "4) count_next_possible_moves()\n"
           "5) check_destination()\n"
           "6) find_knights_by_row()\n"
           "\nSelect a function: ");

    num = 333333;
    read = scanf("%d%c", &num, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Wrong input!\n");
      printf("Select a function: ");
      read = scanf("%d%c", &num, &c);
    }

    if ((num > 6) || (num < 0)) {
      printf("Invalid selection.\n");
      continue;
    }

    if (num == 0) {
      return 0;
    }
    else if (num == 1) {
      printf("Enter the name of an input file: ");
      scanf("%s", filename);
      int_result = read_knights(filename);
      printf("Value returned was: %d\n", int_result);
    }
    else if (num == 2) {
      establish_game_board();
      printf("You have established the game board!\n");
    }
    else if (num == 3) {
      printf("Enter array index of entry to print: ");
      read = scanf("%d%c", &count, &c);
      while (((read != 2) || (c != '\n')) && (clean_stdin())) {
        printf("Wrong input!\n");
        printf("Enter array index of entry to print: ");
        read = scanf("%d%c", &count, &c);
      }

      if ((count < 0) || (count >= g_knight_count)) {
        printf("Specified number is out of bounds.\n");
      }
      else {
        print_knight_piece(g_knight_array[count]);
      }
    }
    else if (num == 4) {
      printf("Enter array index of entry: ");
      read = scanf("%d%c", &count, &c);
      while (((read != 2) || (c != '\n')) && (clean_stdin())) {
        printf("Wrong input!\n");
        printf("Enter array index of entry: ");
        read = scanf("%d%c", &count, &c);
      }

      if ((count < 0) || (count >= g_knight_count)) {
        printf("Specified number is out of bounds.\n");
      }
      else {
        int_result = count_next_possible_moves(count);
        printf("Value returned was: %d\n", int_result);
      }
    }
    else if (num == 5) {
      printf("Enter array index of entry: ");
      read = scanf("%d%c", &count, &c);
      while (((read != 2) || (c != '\n')) && (clean_stdin())) {
        printf("Wrong input!\n");
        printf("Enter array index of entry: ");
        read = scanf("%d%c", &count, &c);
      }
      printf("Enter the destination position of an input file: ");
      scanf("%s", pos);
      if ((count < 0) || (count >= g_knight_count)) {
        printf("Specified number is out of bounds.\n");
      }
      else {
        int_result = check_destination(count, pos);
        printf("Value returned was: %d\n", int_result);
      }
    }
    else if (num == 6) {
      printf("Enter the letter representing the row:  ");
      scanf("%s", row);
      row[strlen(row)] = '\0';
      int_result = find_knights_by_row(row, chess_pieces);

      if (int_result < 0) {
        printf("This function returns an error code %d\n", int_result);
      }
      else{
        printf("%d chess pieces were found for row %s\n", int_result, row);
        for (count = 0; count < int_result; count++) {
          print_knight_piece(g_knight_array[chess_pieces[count]]);
        }
      }
    }
  }

  /* not reached. */
  return 0;
} /* main() */
