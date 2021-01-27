/* Name: Junaid Javed, hw10.c, CS24000, Fall 2020
 * Last updated Nov 16, 2020
 */

/* Add any includes here */

#include "hw10.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Declare variables */
char g_message[MAX_NODE_SIZE];
int g_nodes_visited = 0;

/*
 * Dynamically allocate memory for a tree structure with both the hash value
 * (first input argu- ment) and hash char (second input argument) and
 * initialize both left_child_ptr and right_- child_ptr to NULL. This function
 * should return a pointer to the newly allocated node.
 */

tree_node_t *create_node(int init_value, char init_char) {
  assert(init_value > 0);
  int size = sizeof(init_value) + sizeof(init_char) + 19;
  tree_node_t *return_node = malloc(size);
  assert(return_node != NULL);
  return_node->hash_value = init_value;
  return_node->hash_char = init_char;
  return_node->left_child_ptr = NULL;
  return_node->right_child_ptr = NULL;
  return return_node;
} /* create_node() */

/*
 * The first argument is a pointer to the pointer to the root tree element.
 * The second argument is a pointer to the new tree element to be inserted.
 * If the root tree is NULL, the root should be set to the newly inserted
 * element. The tree should remain a binary tree after inserting the node.
 * The key for insertion should be the hash_value field. (Assume that there
 * are no duplicate hash values.)
 */

void insert_node(tree_node_t **tree_node_pointer, tree_node_t *tree_insert) {
  assert(tree_node_pointer != NULL);
  assert(tree_insert != NULL);
  assert(tree_insert->left_child_ptr == NULL);
  assert(tree_insert->right_child_ptr == NULL);

  if ((*tree_node_pointer) == NULL) {
    *tree_node_pointer = tree_insert;
    return;
  }

  if ((*tree_node_pointer)->hash_value > tree_insert->hash_value) {

    if ((*tree_node_pointer)->left_child_ptr == NULL) {
      (*tree_node_pointer)->left_child_ptr = tree_insert;
      return;
    }
    else
    {

      return insert_node(&((*tree_node_pointer)->left_child_ptr), tree_insert);
    }
  } else {

    if ((*tree_node_pointer)->right_child_ptr == NULL) {
      (*tree_node_pointer)->right_child_ptr = tree_insert;
      return;
    } else {

      return insert_node(&((*tree_node_pointer)->right_child_ptr), tree_insert);
    }
  }
} /* insert_node() */

/*
 * This function should find the node with the matching hash_value
 * (second argument) in the binary tree given by the root_node (first argument)
 * and return the pointer to the node found. (Assume that there are no
 * duplicate hash values.) It should return NULL if the given root_node is
 * NULL or if the node with the given hash_value is not found.
 */

tree_node_t *search_node(tree_node_t *root_node, int find_hash) {
  assert(find_hash > 0);
  if (root_node == NULL) {
    return NULL;
  }

  while (root_node->hash_value != find_hash) {
    if (root_node->hash_value > find_hash) {
      root_node = root_node->left_child_ptr;
    } else {
      root_node = root_node->right_child_ptr;
    }

    if (root_node == NULL) {
      return NULL;
    }
  }
  return root_node;
} /* search_node() */

/*
 * Delete the entire tree and its associated data recursively. After the
 * function returns, the root of the tree that was passed by pointer should be
 * set to NULL.
 */

void delete_tree(tree_node_t **tree_node_pointer) {
  assert(tree_node_pointer != NULL);

  if ((*tree_node_pointer) == NULL) {
    return;
  }

  delete_tree(&(*tree_node_pointer)->left_child_ptr);
  delete_tree(&(*tree_node_pointer)->right_child_ptr);
  free((*tree_node_pointer));

  tree_node_pointer = NULL;
} /* delete_tree() */


/*
 * prefix_traversal is a helper function for find_message. prefix_traversal
 * will traverse the tree whose root is passed in as root_node. PreFix
 * Traversal first visits the root node, then the left child node, and
 * lastly the right child node
 */

void prefix_traversal(tree_node_t *root_node) {
  g_nodes_visited++;
  if (root_node == NULL) {
    return;
  }

  strncat(g_message, &(root_node->hash_char), 1);
  prefix_traversal(root_node->left_child_ptr);
  prefix_traversal(root_node->right_child_ptr);
} /* prefix_traversal() */

/*
 * postfix_traversal is a helper function for find_message. postfix_traversal
 * will traverse the tree whose root is passed in as root_node. PostFix
 * Traversal first visits the left child node, then the right child node, and
 * lastly the root node
 */

void postfix_traversal(tree_node_t *root_node) {
  g_nodes_visited++;
  if (root_node == NULL) {
    return;
  }
  postfix_traversal(root_node->left_child_ptr);
  postfix_traversal(root_node->right_child_ptr);
  strncat(g_message, &(root_node->hash_char), 1);
} /* postfix_traversal() */

/*
 * forward_traversal is a helper function for find_message. forward_traversal
 * will traverse the tree whose root is passed in as root_node. Forward
 * Traversal first visits the left child node, then the root node, and
 * lastly the right child node
 */

void forward_traversal(tree_node_t *root_node) {
  g_nodes_visited++;
  if (root_node == NULL) {
    return;
  }
  forward_traversal(root_node->left_child_ptr);
  strncat(g_message, &(root_node->hash_char), 1);
  forward_traversal(root_node->right_child_ptr);
} /* forward_traversal() */

/*
 * reverse_traversal is a helper function for find_message. reverse_traversal
 * will traverse the tree whose root is passed in as root_node. Reverse
 * Traversal first visits the right child node, then the root node, and
 * lastly the left child node
 */

void reverse_traversal(tree_node_t *root_node) {
  g_nodes_visited++;
  if (root_node == NULL) {
    return;
  }
  reverse_traversal(root_node->right_child_ptr);
  strncat(g_message, &(root_node->hash_char), 1);
  reverse_traversal(root_node->left_child_ptr);
} /* reverse_traversal() */



/*
 * This function should traverse the tree from the root (first argument) using
 * a traversal order (second argument) to find the secret message. When
 * traversing the tree, store hash_char into g_message in order. And the
 * function returns the total number of the tree nodes by the given root.
 */

int find_message(tree_node_t *root_node, int traverse_value) {
  assert((traverse_value >= PREFIX) && (traverse_value <= REVERSE));
  g_message[0] = 0;
  g_nodes_visited = 0;
  switch (traverse_value) {
    case PREFIX:
      prefix_traversal(root_node);
      break;
    case POSTFIX:
      postfix_traversal(root_node);
      break;
    case FORWARD:
      forward_traversal(root_node);
      break;
    case REVERSE:
      reverse_traversal(root_node);
      break;
  }
  return strlen(g_message);
} /* find_message() */

