/* Name: Junaid Javed, hw11.c, CS 24000, Fall 2020
 * Last updated Nov 30, 2020
 */

/* Add any includes here */

#include "hw11.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void print_node(struct node *n_ptr) {
  assert(n_ptr && n_ptr->data && n_ptr->print);

  (n_ptr->print)(n_ptr->data);
} /* print_node() */

/*
 * Function to recursively print theptree using an inorderptraversal
 */

void print_tree(struct node *root ) {
  if (!root) {
    return;
  }

  print_tree(root->left);
  print_node(root);
  print_tree(root->right);

} /* print_tree() */

/*
 * Create a cpu node, allocate appropriate memory for the necessary fields,
 * and populate the fields by copying the arguments into the structure.
 *
 * Assertions: pointer to pointer to void and the char pointers should be
 * non-NULL. Pointer to void should be NULL.
 */

void create_cpu_data(void **void_pointer, const char *cpu_model,
                    const char *cpu_manufacturer, int cpu_speed,
                    int cpu_cores) {

  // Initial assertion checks
  assert((void_pointer != NULL) && (cpu_model != NULL));
  assert(((*void_pointer) == NULL) && (cpu_manufacturer != NULL));

  // Alocate enough memory for the cpu_node and check the malloc assertion
  cpu_t *ptr = malloc(sizeof(struct cpu_s));
  assert(ptr != NULL);
  printf("Done main\n");

  /*
   * Alocate enough model for the model and check the malloc assertion. Copy
   * the model over to the ptr.
   */
  ptr->model = malloc(strlen(cpu_model) + 1);
  assert(ptr->model != NULL);
  strcpy(ptr->model, cpu_model);
  printf("Done model\n");

  /*
   * Alocate enough manufacturer for the model and check the malloc assertion.
   * Copy the manufacturer over to the ptr.
   */

  ptr->manufacturer = malloc(strlen(cpu_manufacturer) + 1);
  assert(ptr->manufacturer != NULL);
  strcpy(ptr->manufacturer, cpu_manufacturer);
  printf("Done manufacturer\n");

  // Copy the speed and cores over to the ptr
  ptr->speed = cpu_speed;
  ptr->cores = cpu_cores;

  // Set the void pointer to point to the cpu node
  (*void_pointer) = (void *)ptr;
} /* create_cpu_data() */

/*
 * Deallocate the memory for the relevant fields. Then deallocate the node
 * itself. Set the pointer to NULL.
 *
 * Assertions: pointer to pointer to void should be non-NULL. pointer should
 * be non-NULL.
 */

void delete_cpu_data(void **cpu_ptr) {
  assert((cpu_ptr != NULL) && ((*cpu_ptr) != NULL));
  cpu_t *ptr = (cpu_t *)(*cpu_ptr);

  free(ptr->model);
  free(ptr->manufacturer);
  free(ptr);
  ptr = NULL;
} /* delete_cpu_data() */

/*
 * This function will compare the overall speed of our cpus. The function
 * returns an integer denoting the comparison of the two arguments passed in.
 * The value it returns should be 1 for arg1 > arg2, 0 if arg1 == arg2, and
 * -1 if arg1 < arg2.
 *
 * Assertions: pointers to void should be non-NULL.
 */

int compare_cpu_data(void *cpu1, void *cpu2) {
  assert((cpu1 != NULL) && (cpu2 != NULL));

  //Cast the void pointers into cpu pointers
  cpu_t *cpu1_ptr = (cpu_t *)cpu1;
  cpu_t *cpu2_ptr = (cpu_t *)cpu2;

  //Calculate the overall speed of the cpu's by multiplying the speed and cores
  int speed1 = cpu1_ptr->speed * cpu1_ptr->cores;
  int speed2 = cpu2_ptr->speed * cpu2_ptr->cores;

  // If the first cpu is faster, then return 1
  if (speed1 > speed2) {
    return 1;
  }

  // If the cpu's are the same speed, then return 0
  if (speed1 == speed2) {
    return 0;
  }

  // Otherwise, the second cpu is faster, so return -1
  return -1;
} /* compare_cpu_data() */

/*
 * Create a memory node, allocate appropriate memory for the necessary fields,
 * and populate the fields by copying the arguments into the structure.
 *
 * Assertions: pointer to pointer to void and the char pointers should be
 * non-NULL. Pointer to void should be NULL.
 */

void create_memory_data(void **void_pointer, const char *mem_model,
                    const char *mem_manufacturer, int mem_size,
                    int mem_speed, int mem_ddr_gen) {

  // Initial assertion checks
  assert((void_pointer != NULL) && (mem_model != NULL));
  assert(((*void_pointer) == NULL) && (mem_manufacturer != NULL));

  // Alocate enough memory for the cpu_node and check the malloc assertion
  memory_t *ptr = malloc(sizeof(struct memory_s));
  assert(ptr != NULL);

  /*
   * Alocate enough model for the model and check the malloc assertion. Copy
   * the model over to the ptr.
   */
  ptr->model = malloc(strlen(mem_model) + 1);
  assert(ptr->model != NULL);
  strcpy(ptr->model, mem_model);

  /*
   * Alocate enough manufacturer for the model and check the malloc assertion.
   * Copy the manufacturer over to the ptr.
   */

  ptr->manufacturer = malloc(strlen(mem_manufacturer) + 1);
  assert(ptr->manufacturer != NULL);
  strcpy(ptr->manufacturer, mem_manufacturer);

  // Copy the speed and cores over to the ptr
  ptr->size = mem_size;
  ptr->speed = mem_speed;
  ptr->ddr_gen = mem_ddr_gen;

  // Set the void pointer to point to the cpu node
  (*void_pointer) = (void *)ptr;
} /* create_memory_data() */

/*
 * Deallocate the memory for the relevant fields. Then deallocate the node
 * itself. Set the pointer to NULL.
 *
 * Assertions: pointer to pointer to void should be non-NULL. pointer should
 * be non-NULL.
 */

void delete_memory_data(void **mem_ptr) {
  assert((mem_ptr != NULL) && ((*mem_ptr) != NULL));
  cpu_t *ptr = (cpu_t *)(*mem_ptr);

  free(ptr->model);
  free(ptr->manufacturer);
  free(ptr);
  ptr = NULL;
} /* delete_memory_data() */

/*
 * This function will compare the model and manufacturer for memories. The rest
 * of the function specification is similar to the specification for
 * compare_cpu_data().
 */

int compare_memory_data(void *memory1, void *memory2) {
  assert((memory1 != NULL) && (memory2 != NULL));

  // Cast the void pointers into memory pointers
  memory_t *memory1_ptr = (memory_t *)memory1;
  memory_t *memory2_ptr = (memory_t *)memory2;

  // If the first model is greater, we return 1
  if (strcmp(memory1_ptr->model, memory2_ptr->model) > 0) {
    return 1;
  }
  // If the second manufacturer is greater, we return -1
  if (strcmp(memory1_ptr->model, memory2_ptr->model) < 0) {
    return -1;
  }

  // Both memories have the same model so we compare the manufacturer

  // If the first manufacturer is greater, we return 1
  if (strcmp(memory1_ptr->manufacturer, memory2_ptr->manufacturer) > 0) {
    return 1;
  }
  // If the second manufacturer is greater, we return -1
  if (strcmp(memory1_ptr->manufacturer, memory2_ptr->manufacturer) < 0) {
    return -1;
  }

  // Otherwise, they are the same, so return 0
  return 0;
} /* compare_memory_data() */

/*
 * ? Dynamically allocate a struct node and initialize the pointers of the node
 * using arguments 2-5. The arguments are: pointer to pointer to a node,
 * pointer to data structure, pointer to print function, pointer to delete
 * function, and pointer to the compare function—respectively.
 *
 * Assertions: pointer to pointer to node structure and arguments 2-5 should
 * be non-NULL, pointer to node structure should be NULL.
 */

void create_node(struct node **tree, void *data_struct,
              void (*print_node)(void *n_ptr), void (*delete_node)(void **tree),
              int (*compare_memory_data)(void *mem1, void *mem2)) {

  assert((tree != NULL) && (data_struct != NULL) && (print_node != NULL));
  assert((delete_node != NULL) && (compare_memory_data != NULL));
  assert((*tree) == NULL);

  // Allocate enough memory to hold the the node and its data
  (*tree) = malloc(sizeof(struct node *) + sizeof(data_struct)
                          + sizeof(print_node) + sizeof(delete_node) +
                          sizeof(compare_memory_data) + 8);
  assert((*tree) != NULL);

  // Initialize the nodes data using the passed parameters
  (*tree)->data = data_struct;
  (*tree)->print = print_node;
  (*tree)->delete = delete_node;
  (*tree)->compare = compare_memory_data;
} /* create_node() */

/*
 * Deallocate the data field by calling the delete function (using the delete
 * function pointer in the node pointer passed in) and then free the node
 * itself.
 *
 * Assertions: pointer to pointer to node structure and pointer to node
 * structure should be non-NULL. The left and right pointers of the node
 *  passed in should be NULL.
 */

void delete_node(struct node **tree) {
  assert((tree != NULL) && ((*tree) != NULL));
  assert(((*tree)->left == NULL) && ((*tree)->right == NULL));
  (*tree)->delete((void **)(&((*tree)->data)));
  free(*tree);

} /* delete_node() */

struct node *insert(struct node *curr, struct node *insert_ptr, struct node *root) {
  if (curr == NULL) {
    print_tree(root);
    return insert_ptr;
  }
  if ((root)->compare((void *)(curr), (void *)(insert_ptr)) <= 0) {
    printf("test\n");
    curr->left = insert(curr->left, insert_ptr, root);
  } else {
    printf("test\n");
    curr->right = insert(curr->right, insert_ptr, root);
  }

  return curr;
}

/*
 * he first argument is a pointer to pointer to the root element of a tree.
 * The second argument is a pointer to a new element to insert into the tree.
 *
 * Assertions: pointer to pointer to the root and pointer to new element
 * should be non- NULL.
 */

void insert_node(struct node **root, struct node *insert_ptr) {
  assert((root != NULL) && (insert_ptr != NULL));
  struct node *curr = (*root);
  insert(curr, insert_ptr, *root);
  printf("---------\n");
  print_tree((*root));
} /* insert_node() */

/*
 * The first argument points to the root node of a tree. The second argument
 * is the pointer to the data structure of the cpu or memory to be searched
 * for in the tree. The third argument is the integer value returned by the
 * function that represents the number of nodes present in the tree with a
 * matching comparison.
 *
 * This function returns the array of pointers.
 *
 * Assertions: none of the arguments should be NULL.
 */

struct node **find_nodes(struct node *root, void *data_struct, int *nodes) {
  assert((root != NULL) && (data_struct != NULL) && (nodes != NULL));
  struct node **new_node = NULL;
  return new_node;

} /* find_nodes() */

/*
 * The first argument is a pointer to pointer to the root node of a tree. The
 * second argument is the pointer to the node to be removed.
 *
 * Assertions: none of the arguments should be NULL.
 */

void remove_node(struct node **tree, struct node *remove) {
  assert((tree != NULL) && (remove != NULL));



} /* remove_node() */

void delete(struct node *curr) {
  if (curr == NULL) {
    return;
  }
  delete(curr->left);
  delete(curr->right);
  curr->delete((void **)(&(curr->data)));
  free(curr);
}

/*
 * The argument is a pointer to pointer to the root node of a tree. Delete the
 * whole tree and set the root pointer to NULL.
 *
 * Assertions: pointer to pointer to the root should be non-NULL.
 */

void delete_tree(struct node **tree) {
  assert(tree != NULL);
  delete((*tree));
} /* delete_tree() */

/* Remember, you don't need a main function!
 * it is provided by hw11_main.c or hw11_test.o
 */
