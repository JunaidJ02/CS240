/* Name: Junaid Javed, library.c, CS 24000, Fall 2020
 * Last updated November 8, 2020
 */

/* Add any includes here */

#include "library.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ftw.h>
#include <stdlib.h>
tree_node_t *g_song_library = NULL;

/*
 * This function should locate the node in the given tree having the given
 * song_name. If the desired song cannot be found in the tree, return NULL.
 * Otherwise, return the parent node’s pointer to the desired song.
 * For example, if the desired node is the left child of the root node,
 * the value returned should be the address of the the root node’s left_child
 * pointer.
 */

tree_node_t **find_parent_pointer(tree_node_t **tree, const char *song_name) {
  // If the tree is NULL, we return NULL
  if (*tree == NULL) {
    return NULL;
  }

  // Recursive loop break statment
  if (strcmp(song_name, (*tree)->song_name) == 0) {
    return tree;
  }

  /*
   * Recursively call the function with the correct child depending on the
   * return value of strcmp
   */
  if (strcmp(song_name, (*tree)->song_name) < 0) {
    return find_parent_pointer(&((*tree)->left_child), song_name);
  } else {
    return find_parent_pointer(&((*tree)->right_child), song_name);
  }

  // Return statment for good measure, will never reach this far
  return NULL;

} /* find_parent_pointer() */

/*
 * The first argument to this function is a double pointer to the root of the
 * tree. The second argument is a node to be inserted into the tree. If the
 * node is already present in the tree, return DUPLICATE_SONG. Otherwise,
 * insert the node at the appropriate location and return INSERT_SUCCESS.
 */

int tree_insert(tree_node_t **tree, tree_node_t *insert) {

  // Recursive loop break statment
  if (*tree == NULL) {
    *tree = insert;
    return INSERT_SUCCESS;
  }

  /*
   * If we find a song with the same name, then its a duplicate and we reutrn
   * DUPLICATE_SONG
   */
  if (strcmp(insert->song_name, (*tree)->song_name) == 0) {
    return DUPLICATE_SONG;

  /*
   * If the song we are on is lower alphabetically than the song we want to
   * insert, then we check if the left node is NULL. If it is then we insert it.
   * if not, we recusrively call the same function but now comapring the left
   * child
   */
  } else if (strcmp(insert->song_name, (*tree)->song_name) < 0) {

    if ((*tree)->left_child == NULL) {

      (*tree)->left_child = insert;
      return INSERT_SUCCESS;
    } else {

      return tree_insert(&((*tree)->left_child), insert);
    }
  /*
   * If the song we are on is higher alphabetically than the song we want to
   * insert, then we check if the right node is NULL. If it is then we insert
   * it. If not, we recusrively call the same function but now comapring the
   * right child
   */
  } else {

    if ((*tree)->right_child == NULL) {

      (*tree)->right_child = insert;
      return INSERT_SUCCESS;
    } else {

      return tree_insert(&((*tree)->right_child), insert);
    }
  }

  // Return statment for good measure, will never reach this far
  return INSERT_SUCCESS;
} /* tree_insert() */

/*
 * This function should search the given tree for a song with the given name.
 * If no such song is found, return SONG_NOT_FOUND. Otherwise, remove the
 * tree_node_t associated with that song from the tree and free all memory
 * associated with the node, including the song. Then, return DELETE_SUCCESS.
 */

int remove_song_from_tree(tree_node_t **tree_node, const char *song_name) {
  tree_node_t *node = (*tree_node);

  /*
   * In the case that the first song in the tree is the song we want to remove,
   * we will remove it and return DELETE_SUCCESS
   */
  if (strcmp(node->song_name, song_name) == 0) {
    tree_node_t *left_child_node = node->left_child;
    tree_node_t *right_child_node = node->right_child;
    free_node(node);

    // Insert the child nodes of the song we just removed back into the tree
    if (left_child_node != NULL) {
      *tree_node = left_child_node;
    }
    if (right_child_node != NULL) {
      if (*tree_node == NULL) {
        *tree_node = right_child_node;
      } else {
        tree_insert(tree_node, right_child_node);
      }
    }
    // Successfully deleted the song and returned DELETE_SUCCESS
    return DELETE_SUCCESS;
  }

  /*
   * While node contains something, we want to continue checking either the
   * left or right child depending on strcmp, similar to tree_insert. Once we
   * find the correct song to remove, we remove it and use tree_insert to insert
   * the correct nodes in their place
   */

  while (node != NULL) {
    // Strcmp returned greater than 0 meaning the song is towards the left
    if (strcmp(node->song_name, song_name) > 0) {
      node = node->left_child;

    // Strcmp returned less than 0 meaning the song is towards the right
    } else if (strcmp(node->song_name, song_name) < 0) {
      node = node->right_child;

    // Strcmp returned 0 meaning we have found the song
    } else {
      tree_node_t *left_child_node = node->left_child;
      tree_node_t *right_child_node = node->right_child;

      tree_node_t **parent = (find_parent_pointer(tree_node, song_name));
      free_node(node);
      *parent = NULL;

      // If their is a left child node, then we have to re-insert it
      if (left_child_node != NULL) {
        tree_insert(tree_node, left_child_node);
      }

      // If their is a right child node, then we have to re-insert it
      if (right_child_node != NULL) {
        tree_insert(tree_node, right_child_node);
      }
      // We successfully deleted the song and should return DELETE_SUCCESS
      return DELETE_SUCCESS;
    }
  }

  /*
   * If we finish the entire while loop and still have not found the song, then
   * we return SONG_NOT_FOUND
   */
  return SONG_NOT_FOUND;
} /* remove_song_from_tree() */

/*
 * This functions should free all data associated with the given tree_node_t,
 * including the data associated with its song.
 */

void free_node(tree_node_t *tree) {
  // Set the song_name equal to NULL
  tree->song_name = NULL;

  // Free the songs in the tree
  free_song(tree->song);

  // Set the left and child nodes to NULL
  tree->left_child = NULL;
  tree->right_child = NULL;

  // Finally free the tree and set it to NULL
  free(tree);
  tree = NULL;
} /* free_node() */

/*
 * This function should print the song name associated with the given tree node
 * to the specified file pointer, followed by a newline characater.
 */

void print_node(tree_node_t *tree, FILE *file) {
  fprintf(file, "%s\n", tree->song_name);
} /* print_node() */

/*
 * This function accepts a tree pointer, a piece of arbitrary data, and a
 * function pointer. This function should perform a pre-order traversal of the
 * tree, where the operation applied to each visited node is a call to the
 * function pointer with the node and arbitrary data passed in.
 */

void traverse_pre_order(tree_node_t *tree, void *data, traversal_func_t func) {
  /*
   * Pre order traversal is Node, Left, Right. Recursively call the function
   * until the tree becomes NULL
   */
  if (tree != NULL) {
    func(tree, data);
    traverse_pre_order(tree->left_child, data, func);
    traverse_pre_order(tree->right_child, data, func);
  }

} /* traverse_pre_order() */

/*
 * This function is exactly the same as the prior, but should visit each node
 * in an in-order fashion.
 */

void traverse_in_order(tree_node_t *tree, void *data, traversal_func_t func) {
  /*
   * In order traversal is Left, Node, Right. Recursively call the function
   * until the tree becomes NULL
   */
  if (tree != NULL) {
    traverse_in_order(tree->left_child, data, func);
    func(tree, data);
    traverse_in_order(tree->right_child, data, func);
  }
} /* traverse_in_order() */

/*
 * This function is exactly the same as the prior, but should visit each node
 * in a post-order fashion.
 */

void traverse_post_order(tree_node_t *tree, void *data, traversal_func_t func) {
  /*
   * Post order traversal is Left, Right, Node. Recursively call the function
   * until the tree becomes NULL
   */
  if (tree != NULL) {
    traverse_post_order(tree->left_child, data, func);
    traverse_post_order(tree->right_child, data, func);
    func(tree, data);
  }
} /* traverse_post_order() */

/*
 * This function should free all data associated with the input tree.
 */

void free_library(tree_node_t *library) {
  // Recursive break statement
  if (library == NULL) {
    return;
  }
  // Recursively free the left and right child nodes
  free_library(library->left_child);
  free_library(library->right_child);

  // Free each song in the node
  free_song(library->song);

  // Free the library iteself
  free(library);
} /* free_library() */

/*
 * This function should print the names of all songs in the given tree to the
 * file, separated by newline characters. These songs should be printed in
 * sorted order, where the sorting criteria is based on strcmp
 */

void write_song_list(FILE *fp, tree_node_t *song_list) {
  // Recursive break statement
  if (song_list == NULL) {
    return;
  }
  // Write the song into the given file pointer
  fprintf(fp, "%s\n", song_list->song_name);

  /*
   * Recursively call the function on the left and right child to print all
   * songs in the tree
   */
  write_song_list(fp, song_list->left_child);
  write_song_list(fp, song_list->right_child);
} /* write_song_list() */


/*
 * Helper function for make_library
 */

int ftw_function(const char *library_name, const struct stat *file, int flag) {
  // Find all the files that end in .mid
  if (flag != FTW_D) {
    // File does not have an ending so we return
    char *file_ending = strrchr(library_name, '.');
    if (file_ending == NULL) {
      return 0;
    }

    // Make sure that the file ending is ".mid".
    if (strcmp(file_ending, ".mid") == 0) {
      // Allocate the memory required for the tree
      tree_node_t *tree_node = malloc(sizeof(tree_node_t));
      assert(tree_node != NULL);

      // Set the song in the tree equal to the parsed song using the passed file
      tree_node->song = parse_file(library_name);

      // Set the left and right child nodes to NULL
      tree_node->left_child = NULL;
      tree_node->right_child = NULL;

      // Store the song name by using the passed file and getting its content
      tree_node->song_name = strrchr(tree_node->song->path, '/') + 1;

      // Make sure that we have not already added this song in the song_library
      assert(tree_insert(&g_song_library, tree_node) != DUPLICATE_SONG);
    }
  }
  return 0;
} /* ftw_function() */

/*
 * This function takes in the name of a directory, and should search through
 * the directory structure, adding adding every MIDI file found in the
 * structure (any file with the extension “.mid”) to the tree held by
 * g_song_library. You should assert that the directory structure contains
 * no duplicate songs.
 */

void make_library(const char *library_name) {
  g_song_library = NULL;
  ftw(library_name, ftw_function, 5);
} /* make_library() */
