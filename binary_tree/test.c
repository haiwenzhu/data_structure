#include "binary_tree.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    struct binary_tree *tree = binary_tree_new();
    struct node *d;
    key_t key;
    char cmd;
    while (scanf("\n%c", &cmd)) {
        if (cmd == 'i' || cmd == 's' || cmd == 'd') {
            if (scanf("\n%d", &key)) {
                switch (cmd) {
                    case 'i':
                        //insert
                        binary_tree_insert(tree, key);
                        printf("insert key:%d\n", key);
                        binary_tree_dump(tree);
                        break;
                    case 's':
                        //search
                        d = binary_tree_search(tree, key);
                        if (d) {
                            printf("find key:%d\n", key);
                        } else {
                            printf("can not find %d\n", key);
                        }
                        break;
                    case 'd':
                        //delete
                        d = binary_tree_search(tree, key);
                        if (d) {
                            binary_tree_delete(tree, d);
                            printf("delete node with key:%d\n", key);
                        } else {
                            printf("can not find %d\n", key);
                        }
                        binary_tree_dump(tree);
                        break;
                    default:
                        break;
                }
            } else {
                break;
            }
        } else {
            break;
        }
    }
    binary_tree_destroy(tree);
}
