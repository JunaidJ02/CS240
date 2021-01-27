#ifndef HW7_H
#define HW7_H

/* Structure Declarations */
typedef struct card_node {
  char *suit;
  char *rank;

  struct card_node *next_card;
} card_node_t;

/* Function prototypes */
card_node_t * add_card_to_head(card_node_t *, char *, char *);
card_node_t * remove_card_from_head(card_node_t *);
card_node_t * add_card_to_tail(card_node_t *, char *, char *);
card_node_t * remove_card_from_tail(card_node_t *);
int count_cards(card_node_t *);
card_node_t * search_by_index(card_node_t *, int);
card_node_t * search_by_card(card_node_t *, char *, char *);
card_node_t * modify_card_by_index(card_node_t *, int, char *, char *);
card_node_t * move_to_tail(card_node_t *, int);
card_node_t * interleave_decks(card_node_t *, card_node_t *);
void free_card_list(card_node_t *);

#endif // HW7_H
