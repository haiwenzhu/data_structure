#ifndef _BINARY_TREE
#define _BINARY_TREE

typedef int key_t;
typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    key_t key;
} node;

typedef struct binary_tree {
    struct node *root;
} btree;

struct binary_tree* binary_tree_new();
void binary_tree_destrory(struct binary_tree*);
struct node* binary_tree_search(struct binary_tree*, key_t);
struct node* binary_tree_insert(struct binary_tree*, key_t);
void binary_tree_delete(struct binary_tree*, struct node*);
void bonary_tree_dump(struct binary_tree*);
#endif
