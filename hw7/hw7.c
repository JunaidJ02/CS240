/* Name: Junaid Javed, hw7.c, CS24000, Fall 2020
 * Last updated Oct 21, 2020
 */

/* Add any includes here */

#include "hw7.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/*
 * add_card_to_head takes in the head of a linked list, head_ref, and adds
 * a card to the head of the list with the suit and rank given from the
 * arguments. It then return the head of the new list.
 */

card_node_t * add_card_to_head(card_node_t* head_ref, char *suit, char *rank) {
  assert(suit != NULL);
  assert(rank != NULL);

  card_node_t *temp_node = malloc(strlen(suit) + strlen(rank) +
                             sizeof(head_ref) + 18);
  assert(temp_node != NULL);
  temp_node->suit = suit;
  temp_node->rank = rank;
  temp_node->next_card = head_ref;
  head_ref = temp_node;

  return head_ref;
} /* add_card_to_head() */

/*
 * remove_card_from_head takes in a head of the linked list, head_ref, and
 * removes the first node on the linked list and return the rest of the
 * linked list.
 */

card_node_t * remove_card_from_head(card_node_t *head_ref) {
  if (head_ref == NULL) {
    return NULL;
  }

  card_node_t* next = NULL;
  next = head_ref->next_card;

  free(head_ref->suit);
  free(head_ref->rank);
  free(head_ref);
  head_ref = NULL;

  return next;
} /* remove_card_from_head() */

/*
 * add_card_to_tail takes in the head of a linked list, head_ref, and adds a
 * a card to the end of that linked list also known as the tail. The added card
 * has a suit and rank given from the arguments. It return the head of the new
 * linked list
 */

card_node_t * add_card_to_tail(card_node_t *head_ref, char *suit, char *rank) {
  assert(suit != NULL);
  assert(rank != NULL);

  card_node_t *tmp = malloc(strlen(suit) + strlen(rank) +
                       sizeof(head_ref) + 18);
  assert(tmp != NULL);
  tmp->suit = suit;
  tmp->rank = rank;
  tmp->next_card = NULL;

  card_node_t *tail = head_ref;

  if (head_ref == NULL) {
    return tmp;
  }

  while (head_ref->next_card != NULL) {
    head_ref = head_ref->next_card;
  }

  head_ref->next_card = tmp;

  return tail;
} /* add_card_to_tail() */

/*
 * remove_card_from_tail takes in the agrument head_ref which is the head of a
 * linked list. The function then goes to the end of the linked list and removes
 * the last node. It then returns the head of the new linked list.
 */

card_node_t * remove_card_from_tail(card_node_t *head_ref) {
  if (head_ref == NULL) {
    return NULL;
  }

  if (head_ref->next_card == NULL) {
    free(head_ref->suit);
    free(head_ref->rank);
    free(head_ref);
    return NULL;
  }

  card_node_t *tail = NULL;
  tail = head_ref;

  while (head_ref->next_card->next_card != NULL) {
    head_ref = head_ref->next_card;
  }

  free(head_ref->next_card->suit);
  free(head_ref->next_card->rank);
  free(head_ref->next_card);
  head_ref->next_card = NULL;

  return tail;
} /* remove_card_from_tail() */

/*
 * count_cards takes in a head of a linked list, head_ref, and returns the
 * number of nodes in the list or also known as the number of cards in the list
 */

int count_cards(card_node_t *head_ref) {
  int count = 0;
  while (head_ref != NULL) {
    count++;
    head_ref = head_ref->next_card;
  }

  return count;
} /* count_cards() */

/*
 * search_by_index takes in a head of a linked list and an index. The function
 * finds the node in the index'th position after the head and return that node
 */

card_node_t * search_by_index(card_node_t *head_ref, int index) {
  assert(index > 0);

  while (index > 1) {
    if (head_ref == NULL) {
      return NULL;
    }
    head_ref = head_ref->next_card;
    index--;
  }
  return head_ref;
} /* search_by_index() */

/*
 * search_by_card gets the head of a linked list and a specific suit and rank.
 * The function finds if and where that card exists in the linked list and
 * returns it
 */

card_node_t * search_by_card(card_node_t *head_ref, char *suit, char *rank) {
  assert(suit != NULL);
  assert(rank != NULL);

  while (head_ref != NULL) {
    if ((strcmp(head_ref->rank, rank) == 0) &&
          (strcmp(head_ref->suit, suit) == 0)) {
      break;
    }
    head_ref = head_ref->next_card;
  }
  return head_ref;
} /* search_by_card() */

/*
 * modift_card_by_index finds node on the n'th position of head and
 * updates it with a new suit and rank that are provided from the arguments
 */

card_node_t * modify_card_by_index(card_node_t *head, int n, char *s, char *r) {
  assert(n > 0);
  assert(s != NULL);
  assert(r != NULL);

  head = search_by_index(head, n);
  if (head == NULL) {
    return NULL;
  }
  free(head->rank);
  free(head->suit);
  assert(malloc(strlen(s) + strlen(r) + 2) != NULL);

  head->suit = s;
  head->rank = r;

  return head;
} /* modify_card_by_index() */

/*
 * move_to_tail takes in the head of a linked list and an index. The function
 * takes the node in the position of the index and moves it to the end of the
 * linked list. It then returns the head of the new linked list.
 */

card_node_t * move_to_tail(card_node_t *head_ref, int index) {
  assert(index >= 0);
  assert(index <= count_cards(head_ref));

  card_node_t *tail = head_ref;
  card_node_t *new_head = head_ref;
  card_node_t *tmp = head_ref;

  for (int i = 1; i < index; i++) {
    head_ref = head_ref->next_card;
  }

  if (head_ref->next_card == NULL) {
    return tail;
  }

  tail = head_ref->next_card;
  new_head = head_ref->next_card;
  head_ref = tmp;

  while (tail->next_card != NULL) {
    tail = tail->next_card;
  }

  for (int i = 1; i <= index; i++) {
    tail->next_card = head_ref;
    head_ref = head_ref->next_card;
    tail = tail->next_card;
  }

  tail->next_card = NULL;
  return new_head;
} /* move_to_tail() */

/*
 * helper function for interleave_decksneeded to recurively call in order to
 * interleave the decks
 */

card_node_t * merge_decks(card_node_t *deck1, card_node_t *deck2, bool first) {
  if (deck1 == NULL) {
    return deck2;
  }

  if (deck2 == NULL) {
    return deck1;
  }

  if (first) {
    deck1->next_card =
                        merge_decks(deck1->next_card, deck2, false);
    return deck1;
  } else {
    deck2->next_card =
                        merge_decks(deck1, deck2->next_card, true);
    return deck2;
  }
  return NULL;
} /* merge_decks() */

/*
 * this function takes in two heads of a linked list and interleaves them
 * together in order to make one linked list. This function uses the help of
 * merge_decks in order to be called recursively and save memory.
 */

card_node_t * interleave_decks(card_node_t *deck1, card_node_t *deck2) {
  assert(deck1 != NULL);
  assert(deck2 != NULL);

  /*
   * Switches the decks if deck2 is bigger in order for the funciton
   * to work as intended.
   */
  if (count_cards(deck2) > count_cards(deck1)) {
    card_node_t *tmp = deck1;
    deck1 = deck2;
    deck2 = tmp;
  }

  return merge_decks(deck1, deck2, true);
} /* interleave_decks() */

/*
 * free_card_list takes in a linked list and frees the memory associated with
 * ever node in the lsit
 */

void free_card_list(card_node_t *head_ref) {
  while (head_ref != NULL) {
    head_ref = remove_card_from_head(head_ref);
  }
} /* free_card_list() */