#ifndef HW6_H
#define HW6_H

/* Constant definitions */
#define MAX_KNIGHT_COUNT  (32)
#define MAX_COLOR_LEN     (6)
#define MAX_POSITION_LEN  (3)

/* Error codes */
#define NON_READABLE_FILE (-1)
#define BAD_RECORD        (-2)
#define NO_KNIGHT         (-3)
#define OUT_OF_BOUND      (-4)
#define BAD_INPUT_ROW     (-5)
#define BAD_DESTINATION   (-6)

/* Structure Declarations */
typedef struct knight {
  char position[MAX_POSITION_LEN];
  char color[MAX_COLOR_LEN];

  char top_right[MAX_POSITION_LEN];
  char top_left[MAX_POSITION_LEN];
  char bottom_right[MAX_POSITION_LEN];
  char bottom_left[MAX_POSITION_LEN];
  char right_top[MAX_POSITION_LEN];
  char right_bottom[MAX_POSITION_LEN];
  char left_top[MAX_POSITION_LEN];
  char left_bottom[MAX_POSITION_LEN];

  struct knight *top_right_ptr;
  struct knight *top_left_ptr;
  struct knight *bottom_right_ptr;
  struct knight *bottom_left_ptr;
  struct knight *right_top_ptr;
  struct knight *right_bottom_ptr;
  struct knight *left_top_ptr;
  struct knight *left_bottom_ptr;
} knight_t;

extern knight_t g_knight_array[MAX_KNIGHT_COUNT];
extern int g_knight_count;

/* Function prototypes */
int read_knights(char *);
void establish_game_board();
int count_next_possible_moves(int);
int check_destination(int, char *);
int find_knights_by_row(char *, int *);

#endif // HW6_H
