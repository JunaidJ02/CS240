/* HW10 main function */

/* Includes */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "hw10.h"

/* Defines */

#define CREATE_NODE  (1)
#define INSERT_NODE  (2)
#define SEARCH_NODE  (3)
#define DELETE_TREE  (4)
#define FIND_MESSAGE (5)
#define QUIT         (0)

/*
 * This function is used for reading input
 */

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return 1;
} /* clean_stdin() */

/*
 * This function is used to run the different functions implemented in file
 * hw11.c. Upon completion main returns zero.
 */

int main() {

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  char c = ' ';
  int read = 0;
  int order = 0;
  int response = 0;
  int hash_value = 0;
  char hash_char = ' ';
  int count = 0;
  tree_node_t *new_node = NULL;
  tree_node_t *tree_head = NULL;
  tree_node_t *search_return = NULL;

  while (true) {
    printf("\nTest Menu:\n");
    printf("1. create_node()\n");
    printf("2. insert_node()\n");
    printf("3. search_node()\n");
    printf("4. delete_tree()\n");
    printf("5. find_message()\n");
    printf("0. Exit\n");
    printf("\nEnter your choice: ");

    read = scanf("%d%c", &response, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Invalid selection.\n");
      printf("Enter your choice: ");
      read = scanf("%d%c", &response, &c);
    }

    switch (response) {
      case CREATE_NODE:
        printf("\nEnter a hash value integer: ");
        fscanf(stdin, "%d", &hash_value);
        while (getchar() != '\n'){
        }
        printf("Enter a hash character: ");
        fscanf(stdin, "%c", &hash_char);
        while (getchar() != '\n'){
        }
        if (new_node) {
          free(new_node);
          new_node = NULL;
        }
        new_node = create_node(hash_value, hash_char);
        printf("New node created with pointer [%p].\n", new_node);
        break;
      case INSERT_NODE:
        if (new_node == NULL) {
          printf("Please create your node before inserting.\n");
          break;
        }
        insert_node(&tree_head, new_node);
        printf("Node [%p] is inserted.\n", new_node);
        new_node = NULL;
        break;
      case SEARCH_NODE:
        printf("\nEnter a hash value integer for search: ");
        fscanf(stdin, "%d", &hash_value);
        while (getchar() != '\n'){
        }
        search_return = search_node(tree_head, hash_value);
        if (search_return == NULL) {
          printf("Node with hash value (%d) not found in tree.\n", hash_value);
        }
        else {
          printf("Node with hash value (%d) found at [%p]\n",
            search_return->hash_value, search_return);
        }
        break;
      case DELETE_TREE:
        delete_tree(&tree_head);
        printf("Tree deleted.\n");
        tree_head = NULL;
        break;
      case FIND_MESSAGE:
        printf("\nEnter a traverse order (1-4): ");
        fscanf(stdin, "%d", &order);
        while (getchar() != '\n'){
        }
        count = find_message(tree_head, order);
        printf("Returned value is (%d).\n", count);

        printf("The message is ");
        for (int i = 0; i < count; i++) {
          printf("%c", g_message[i]);
        }
        printf("\n");
        break;
      case QUIT:
        if (new_node != NULL) {
          free(new_node);
          new_node = NULL;
        }
        if (tree_head != NULL) {
          delete_tree(&tree_head);
          tree_head = NULL;
        }
        printf("\nGoodbye!!\n");
        return 0;
      default:
        printf("Invalid selection.\n");
        break;
    }
  }
  return 0;
} /* main() */
