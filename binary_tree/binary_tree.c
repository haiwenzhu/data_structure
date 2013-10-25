#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

key_t dump_arr[10][512];
int dump_arr_index[10];

static node* new_node(key_t key)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static void delete_node(node *d)
{
    assert(d);
    if (d->left) {
        delete_node(d->left);
    } else if (d->right) {
        delete_node(d->right);
    }
    free(d);
    return;
}

static node* binary_tree_min_key(node *d)
{
    node *x = d;
    while (x->left) {
        x = x->left;
    }
    return x;
}

static node* binary_tree_successor(node *d)
{
    if (d->right) {
        return binary_tree_min_key(d->right);
    } else {
        node *x = d;
        node *y = x->parent;
        while (y && x == y->right) {
            x = y;
            y = x->parent;
        }
        return y;
    }
}
            
btree* binary_tree_new()
{
    btree *tree = (btree*)malloc(sizeof(btree));
    tree->root = NULL;
    return tree;
}

void binary_tree_destroy(btree *tree)
{
    assert(tree);
    if (tree->root) {
        delete_node(tree->root);
    }
    free(tree);
    return;
}

node* binary_tree_insert(btree *tree, key_t key)
{ 
    assert(tree);
    node *y = NULL;
    node *x = tree->root;
    node *n_node = new_node(key);

    while (x) {
        y = x;
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    //tree is empty
    if (y == NULL) {
        tree->root = n_node;
    } else {
        n_node->parent = y;
        if (key < y->key) {
            y->left = n_node;
        } else {
            y->right = n_node;
        }
    }
    return n_node;
}

void binary_tree_delete(btree *tree, node *d)
{
    node *del_node, *chd_node; 
    if (d->left == NULL || d->right == NULL) {
        del_node = d; 
    } else {
        //if node has 2 children
        //delete the node's successor
        //copy successor key to node
        del_node = binary_tree_successor(d);
    }

    if (del_node->left != NULL) {
        chd_node = del_node->left;
    } else {
        chd_node = del_node->right;
    }
    if (chd_node != NULL) {
        chd_node->parent = del_node->parent;
    }
    //node is root
    if (del_node->parent == NULL) {
        tree->root = chd_node;
    } else {
        if (del_node == del_node->parent->left) {
            del_node->parent->left = chd_node;
        } else {
            del_node->parent->right = chd_node;
        }
        if (del_node != d) {
            d->key = del_node->key;
        }
    }
    free(del_node);
    return;
}

node* binary_tree_search(btree *tree, key_t key)
{
    assert(tree);
    node *d = tree->root;
    while (d) {
        if (d->key == key) {
            return d;
        } else if (key < d->key) {
            d = d->left;
        } else {
            d = d->right;
        }
    }
    return NULL;
}

static void binary_tree_dump_with_level(node *d, int level)
{
    int index = dump_arr_index[level]++;
    dump_arr[level][index] = d->key;
    level++;
    if (level >= 10) {
        return;
    }
    if (d->left) {
        binary_tree_dump_with_level(d->left, level);
    }
    if (d->right) {
        binary_tree_dump_with_level(d->right, level);
    }
}

void binary_tree_dump(btree *tree)
{
    memset(dump_arr, 0, sizeof(dump_arr));
    memset(dump_arr_index, 0, sizeof(dump_arr_index));
    assert(tree);
    if (tree->root) {
        binary_tree_dump_with_level(tree->root, 0);
        int i, j, flag;
        for (i = 0; i < 10; i++)
        {
            flag = 0;
            for (j = 0; j < dump_arr_index[i]; j++) {
                flag = 1;
                printf("%d", dump_arr[i][j]);
            }
            if (flag) {
                printf("\n");
            }
        }
    } else {
        printf("tree is empty!\n");
    }
}
