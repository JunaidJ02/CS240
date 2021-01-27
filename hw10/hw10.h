#ifndef HW10_H
#define HW10_H

/* Constant definitions */
#define PREFIX        (1)
#define POSTFIX       (2)
#define FORWARD       (3)
#define REVERSE       (4)
#define MAX_NODE_SIZE (20)

/* Structure Definitions */
typedef struct tree_node {
  int hash_value;
  char hash_char;
  struct tree_node *left_child_ptr;
  struct tree_node *right_child_ptr;
} tree_node_t;

/* Function prototypes */
tree_node_t *create_node(int, char);
void insert_node(tree_node_t **, tree_node_t *);
tree_node_t *search_node(tree_node_t *, int);
void delete_tree(tree_node_t **);
int find_message(tree_node_t *, int);

extern char g_message[MAX_NODE_SIZE];

#endif // HW10_H
