/* Name: Junaid Javed, hw6.c, CS24000, Fall 2020
 * Last updated Oct 12, 2020
 */

/* Add any includes here */

#include "hw6.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * read_knights reads the file named in_file and stores all the kinghts in the
 * global array called g_knight_array. The function then returns how many
 * knights it found in the file
 */

int read_knights(char *in_file) {
  assert(in_file != NULL);

  FILE *fptr = NULL;
  fptr = fopen(in_file, "r");

  if (fptr == NULL) {
    return NON_READABLE_FILE;
  }


  char pos[2];
  char color[MAX_COLOR_LEN];
  char top_right[MAX_POSITION_LEN];
  char top_left[MAX_POSITION_LEN];
  char bot_right[MAX_POSITION_LEN];
  char bot_left[MAX_POSITION_LEN];
  char right_top[MAX_POSITION_LEN];
  char right_bot[MAX_POSITION_LEN];
  char left_top[MAX_POSITION_LEN];
  char left_bot[MAX_POSITION_LEN];


  int number_of_values = fscanf(fptr,
   "%2[^|]|%5[^:]:%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]\n",
    pos, color, top_right, top_left, bot_right, bot_left, right_top, right_bot,
    left_top, left_bot);


  g_knight_count = 0;
  while (number_of_values == 10) {
    strncpy(g_knight_array[g_knight_count].position, pos, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].color, color, MAX_COLOR_LEN - 1);

    /*
     * Extra precaution because some tests contain colors that are not black
     * or white
     */
    if ((strncmp(color, "White", 5) != 0)
       && (strncmp(color, "Black", 5) != 0)) {
      fclose(fptr);
      fptr = NULL;
      return BAD_RECORD;
    }
    strncpy(g_knight_array[g_knight_count].top_right, strncmp(top_right,
     "??", 2) == 0  ? "\0": top_right, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].top_left, strncmp(top_left,
     "??", 2) == 0  ? "\0": top_left, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].bottom_right, strncmp(bot_right,
     "??", 2) == 0  ? "\0": bot_right, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].bottom_left, strncmp(bot_left,
     "??", 2) == 0  ? "\0": bot_left, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].right_top, strncmp(right_top,
     "??", 2) == 0  ? "\0": right_top, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].right_bottom, strncmp(right_bot,
     "??", 2) == 0  ? "\0": right_bot, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].left_top, strncmp(left_top,
     "??", 2) == 0  ? "\0": left_top, MAX_POSITION_LEN - 1);
    strncpy(g_knight_array[g_knight_count].left_bottom, strncmp(left_bot,
     "??", 2) == 0  ? "\0": left_bot, MAX_POSITION_LEN - 1);

    g_knight_count++;
    if (g_knight_count >= MAX_KNIGHT_COUNT) {
      fclose(fptr);
      fptr = NULL;
      return OUT_OF_BOUND;
    }

    number_of_values = fscanf(fptr,
     "%2[^|]|%5[^:]:%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]|%2[^|]\n",
    pos, color, top_right, top_left, bot_right, bot_left, right_top, right_bot,
    left_top, left_bot);
  }

  fclose(fptr);
  fptr = NULL;

  if ((number_of_values > 0) && (number_of_values != 10)) {
    return BAD_RECORD;
  }

  return g_knight_count;
} /* read_knights() */

/*
 * eastablish_game_board iterates through every knight in g_knight_array and
 * finds the knights that the current knight can land on, it then sets those
 * knights to the pointers of the current knight.
 */

void establish_game_board() {

  // Loop through every knight_t in g_knight_array
  for (int i = 0; i < MAX_KNIGHT_COUNT; i++) {
    if (g_knight_array[i].position[0] == '\0') {
      continue;
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in top_right position
      if (strncmp(g_knight_array[i].top_right, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].top_right_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in top_left position
      if (strncmp(g_knight_array[i].top_left, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].top_left_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in bottom_right position
      if (strncmp(g_knight_array[i].bottom_right, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].bottom_right_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in bottom_left position
      if (strncmp(g_knight_array[i].bottom_left, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].bottom_left_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in right_top position
      if (strncmp(g_knight_array[i].right_top, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].right_top_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in right_bottom position
      if (strncmp(g_knight_array[i].right_bottom, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].right_bottom_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in left_top position
      if (strncmp(g_knight_array[i].left_top, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].left_top_ptr = &g_knight_array[j];
      }
    }

    for (int j = 0; j < MAX_KNIGHT_COUNT; j++) {
      if (g_knight_array[j].position[0] == '\0') {
        continue;
      }
      // Find knight in left_bottom position
      if (strncmp(g_knight_array[i].left_bottom, g_knight_array[j].position, 2)
           == 0) {
        g_knight_array[i].left_bottom_ptr = &g_knight_array[j];
      }
    }
  }
} /* establish_game_board() */

/*
 * count_next_possible_moves takes the knight in the nth_position of
 * g_knight_array and sees how many possible moves that knight can take. A
 * possible move is one where the knight can move to and that position contains
 * a knight of the opposite color
 */

int count_next_possible_moves(int nth_position) {
  assert((nth_position >= 0) && (nth_position < g_knight_count));
  int possible_moves = 0;

  char* opposite_color = " ";
  if (strncmp(g_knight_array[nth_position].color, "Black", 5) == 0) {
    opposite_color = "White";
  }

  if (strncmp(g_knight_array[nth_position].color, "White", 5) == 0) {
    opposite_color = "Black";
  }

  if ((g_knight_array[nth_position].top_right_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].top_right_ptr).color,
         opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].top_left_ptr != NULL) &&
      (strncmp((*g_knight_array[nth_position].top_left_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].bottom_right_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].bottom_right_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].bottom_left_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].bottom_left_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].right_top_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].right_top_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].right_bottom_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].right_bottom_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].left_top_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].left_top_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }
  if ((g_knight_array[nth_position].left_bottom_ptr != NULL) &&
       (strncmp((*g_knight_array[nth_position].left_bottom_ptr).color,
        opposite_color, 5) == 0)) {
    possible_moves++;
  }

  return possible_moves;
} /* count_next_possible_moves() */

/*
 * check_destination checks if the knight in the nth_position can jump to the
 * jump_position. It can jump as long as it that knight can get there in one
 * move and that position contains a kinght of the opposite color. The function
 * then returns the index of the knight that would get killed
 */

int check_destination(int nth_position, char *jump_position) {
  assert((nth_position >= 0) && (nth_position < g_knight_count));
  assert(jump_position != NULL);

  for (int i = 0; i < g_knight_count; i++) {
    if (strncmp(g_knight_array[i].position, jump_position, 2) == 0) {
      if (abs((g_knight_array[nth_position]).position[0] -
           jump_position[0]) == 2) {
        if (abs((g_knight_array[nth_position]).position[1] -
             jump_position[1]) == 1) {
          if (strncmp(g_knight_array[nth_position].color,
               g_knight_array[i].color, 5) != 0) {
            return i;
          }
        }
      } else if (abs((g_knight_array[nth_position]).position[0] -
          jump_position[0]) == 1) {
        if (abs((g_knight_array[nth_position]).position[1] -
            jump_position[1]) == 2) {
          if (strncmp(g_knight_array[nth_position].color,
               g_knight_array[i].color, 5) != 0) {
            return i;
          }
        }
      }
    }
  }

  // Check if position is valid, if not, then return bad destination
  if ((jump_position[0] < 65) || (jump_position[0] > 72) ||
       (jump_position[1] < 49) || (jump_position[1] > 56)) {
    return BAD_DESTINATION;
  }

  // If position is valid, and no knight is found, return NO_KNIGHT
  return NO_KNIGHT;
} /* check_destination() */

/*
 * find_knights_by_row checks every knight in g_knight_array and checks to see
 * if there are any knights that have the same row as the input row. If they
 * match, then the index of that knight is stores in knight_array
 */

int find_knights_by_row(char *row, int *knight_array) {
  assert(row != NULL);
  assert(knight_array != NULL);

  int row_number = (int) *row;
  if ((row_number < 65) || (row_number > 72)) {
    return BAD_INPUT_ROW;
  }

  int number_of_pieces_found = 0;
  for (int i = 0; i < g_knight_count; i++) {
    if (g_knight_array[i].position[0] == row_number) {
      knight_array[number_of_pieces_found] = i;
      number_of_pieces_found++;
    }
  }

  return number_of_pieces_found;
} /* find_knights_by_row() */

