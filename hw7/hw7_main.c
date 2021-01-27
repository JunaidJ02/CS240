/* Includes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw7.h"

#define MAX_SUIT_LEN (50)
#define MAX_RANK_LEN (50)

static void print_card(card_node_t *list);
static card_node_t *copy(card_node_t *list);

/*
 * This function is used to handle the input reading
 */

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return 1;
} /* clean_stdin() */

/*
 * This function is used to run the different functions implemented in file
 * hw8.c. User input is used to determine which function to run and what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main() {
  char c = ' ';
  int read = 0;
  int n = 0;
  int choice = 0;
  int count = 0;
  int number = 0;
  char suit[MAX_SUIT_LEN] = "";
  char rank[MAX_RANK_LEN] = "";
  card_node_t *card1 = NULL;
  card_node_t *card2 = NULL;

  while (1) {
    printf("\nOPTIONS:\n"
           "0) Quit\n"
           "1) add_card_to_head()\n"
           "2) remove_card_from_head()\n"
           "3) add_card_to_tail()\n"
           "4) remove_card_from_tail()\n"
           "5) count_cards()\n"
           "6) search_by_index()\n"
           "7) search_by_card()\n"
           "8) modify_card_by_index()\n"
           "9) move_to_tail()\n"
           "10) interleave_decks()\n"
           "11) free_card_list()\n"
           "Select a function: ");

    read = scanf("%d%c", &choice, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Wrong input!\n");
      printf("Select a function: ");
      read = scanf("%d%c", &choice, &c);
    }

    if (choice == 0) {
      printf("\nGoodbye!\n\n");
      break;
    }

    switch (choice) {
      case 0:
        printf("\nGoodbye!\n\n");
        break;
      case 1:
        printf("\nSelect deck to add (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
                 || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to add (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter suit: ");
        scanf("%s", suit);
        printf("\nEnter rank: ");
        scanf("%s", rank);

        if (number == 1) {
          card1 = add_card_to_head(card1, suit, rank);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          card2 = add_card_to_head(card2, suit, rank);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 2:
        printf("\nSelect deck to remove (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
              || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to add (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        if (number == 1) {
          card1 = remove_card_from_head(card1);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          card2 = remove_card_from_head(card2);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 3:
        printf("\nSelect deck to add (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
          || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to add (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter suit: ");
        scanf("%s", suit);
        printf("\nEnter rank: ");
        scanf("%s", rank);

        if (number == 1) {
          card1 = add_card_to_tail(card1, suit, rank);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          card2 = add_card_to_tail(card2, suit, rank);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 4:
        printf("\nSelect deck to remove (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to add (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        if (number == 1) {
          card1 = remove_card_from_tail(card1);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else{
          card2 = remove_card_from_tail(card2);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 5:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        if (number == 1) {
          count = count_cards(card1);
          printf("\nThe number of cards in the deck %d is: %d\n",
                number, count);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          count = count_cards(card2);
          printf("\nThe number of cards in the deck %d is: %d\n",
              number, count);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 6:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter the search index: ");
        read = scanf("%d%c", &n, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("\nWrong input!\n");
          printf("\nEnter the search index: ");
          read = scanf("%d%c", &n, &c);
        }

        if (number == 1) {
          if (n <= 0) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else {
            card_node_t *temp = search_by_index(card1, n);
            printf("\nThe card in deck %d after searching with index %d is:\n",
                number, n);
            print_card(temp);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        else {
          if ((n <= 0) || (n > count_cards(card2))) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else {
            card_node_t *temp = search_by_index(card2, n);
            printf("\nThe card in deck %d after searching with index %d is:\n",
                 number, n);
            print_card(temp);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        break;
      case 7:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
              || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter suit: ");
        scanf("%s", suit);
        printf("\nEnter rank: ");
        scanf("%s", rank);

        if (number == 1) {
          card_node_t *temp = search_by_card(card1, suit, rank);
          printf("\nThe card in deck %d "
                 "after searching with suit %s and rank %s is:\n",
                 number, suit, rank);
          print_card(temp);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          card_node_t *temp = search_by_card(card2, suit, rank);
          printf("\nThe card in deck %d after searching with suit %s"
                 " and rank %s is:\n", number, suit, rank);
          print_card(temp);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 8:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter the index: ");
        read = scanf("%d%c", &n, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("\nWrong input!\n");
          printf("\nEnter the index: ");
          read = scanf("%d%c", &n, &c);
        }

        if (number == 1) {
          if (n <= 0) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else {
            printf("\nEnter suit: ");
            scanf("%s", suit);
            printf("\nEnter rank: ");
            scanf("%s", rank);
            card_node_t *temp = modify_card_by_index(card1, n, suit, rank);
            printf("\nThe card in deck %d after modifying with index %d, "
                   "suit %s and rank %s is:\n", number, n, suit, rank);
            print_card(temp);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        else{
          if (n <= 0) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else {
            printf("\nEnter suit: ");
            scanf("%s", suit);
            printf("\nEnter rank: ");
            scanf("%s", rank);
            card_node_t *temp = modify_card_by_index(card2, n, suit, rank);
            printf("\nThe card in deck %d after modifying with index %d, "
                   "suit %s and rank %s is:\n", number, n, suit, rank);
            print_card(temp);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        break;
      case 9:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        printf("\nEnter the index: ");
        read = scanf("%d%c", &n, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("\nWrong input!\n");
          printf("\nEnter the index: ");
          read = scanf("%d%c", &n, &c);
        }

        if (number == 1) {
          if (n < 0) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else{
            card1 = move_to_tail(card1, n);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        else {
          if (n < 0) {
            printf("Specified index is out of bounds for deck %d.\n", number);
          }
          else{
            card2 = move_to_tail(card2, n);
            printf("\nElements in the deck 1:\n");
            print_card(card1);
            printf("\nElements in the deck 2:\n");
            print_card(card2);
          }
        }
        break;
      case 10:
        if ((card1 == NULL) || (card2 == NULL)) {
          printf("You have an empty deck!");
        }
        else {
          card_node_t *temp = interleave_decks(copy(card1), copy(card2));
          printf("\nElements after interleaving deck 1 and deck 2 are:\n");
          print_card(temp);
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      case 11:
        printf("\nSelect deck to count (1 or 2): ");
        read = scanf("%d%c", &number, &c);
        while ((((read != 2) || (c != '\n')) && (clean_stdin()))
             || ((number != 1) && (number != 2))) {
          printf("\nWrong input!\n");
          printf("\nSelect deck to count (1 or 2): ");
          read = scanf("%d%c", &number, &c);
        }

        if (number == 1) {
          free_card_list(card1);
          card1 = NULL;
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        else {
          free_card_list(card2);
          card2 = NULL;
          printf("\nElements in the deck 1:\n");
          print_card(card1);
          printf("\nElements in the deck 2:\n");
          print_card(card2);
        }
        break;
      default:
        printf("\nInvalid input! Try again...\n");
        break;
    } /* switch (choice) */

  } /* while (1) */
  free_card_list(card1);
  free_card_list(card2);

  return 0;
} /* main() */

/*
 * Function to print a list of card
 */

static void print_card(card_node_t *list){
  card_node_t * temp = list;
  while (temp != NULL) {
    printf("([%s, %s])->", temp->suit, temp->rank);
    temp = temp->next_card;
  }
  printf("(NULL)\n");
} /* print_card() */

/*
 * Function to copy the list
 */

static card_node_t *copy(card_node_t *list) {

  card_node_t *newlist = NULL;
  card_node_t *p = NULL;
  card_node_t *prev = NULL;

  while (list != NULL) {
    p = malloc(sizeof(*p));
    p->suit = malloc(strlen(list->suit) + 1);
    strcpy(p->suit, list->suit);
    p->rank = malloc(strlen(list->rank) + 1);
    strcpy(p->rank, list->rank);

    if (!newlist) {
      newlist = p;
    }
    else {
      prev->next_card = p;
    }
    prev = p;
    list = list->next_card;
  }
  prev->next_card = NULL;
  return newlist;
} /* copy() */
