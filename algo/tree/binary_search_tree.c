#include <stdio.h>
#include<stdlib.h>

#include "binary_search_tree.h"

int comp_int(int a, int b) {
    return a==b?0:(a>b?1:2);
}

bs_tree* create_tree(comp cp) {
    bs_tree* bt = (bs_tree*)malloc(sizeof(bs_tree));
    if (bt == NULL) {
        printf("create_tree failed\n");
        return NULL;
    }

    bt->root = NULL;
    bt->cp = cp;
    bt->size = 0;

    return bt;
}

bs_node* create_node(int data) {
    bs_node * node = (bs_node *)malloc(sizeof(bs_node));
    if (node == NULL) {
        printf("create_node failed, malloc node is NULL\n");
        return NULL;
    }
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;

    return node;
}

void destroy_node(bs_node *node) {
    if (node == NULL) {
        return;
    }

    destroy_node(node->lchild);
    destroy_node(node->rchild);
    free(node);
}

void destroy_tree(bs_tree *tree) {
    destroy_node(tree->root);
    free(tree);
}

void insert(bs_tree *tree, int data) {
    if (is_empty(tree)) {
        bs_node* node = create_node(data);
        if (node == NULL) {
            return;
        }

        tree->root = node;
        tree->size++;
        return;
    }

    bs_node *temp = tree->root;
    while (temp != NULL) {
        int res = tree->cp(temp->data, data);

        if (res == 1 || res == 0) {
            if (temp->lchild == NULL) {
                bs_node* node = create_node(data);
                if (node == NULL) {
                    return;
                }
                temp->lchild = node;
                tree->size++;
                break;
            }else {
                temp = temp->lchild;
            }
        }else if (res == 2) {
            if (temp->rchild == NULL) {
                bs_node* node = create_node(data);
                if (node == NULL) {
                    return;
                }
                temp->rchild = node;
                tree->size++;
                break;
            }else {
                temp = temp->rchild;
            }
        }
    }
}

void dump_pre_order(bs_node *tree) {
    if (tree == NULL) {
        return;
    }
    printf("data:%d\n", tree->data);
    dump_pre_order(tree->lchild);
    dump_pre_order(tree->rchild);
}

//也可以用非递归
bs_node *search(bs_node *root, int data) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == data) {
        return root;
    }

    if (root->data > data) {
        return search(root->lchild, data);
    }

    if (root->data < data) {
        return search(root->rchild, data);
    }

    return NULL;
}

void delete(bs_tree *tree, int data) {
    if (tree == NULL) {
        printf("delete failed, tree is NULL\n");
        return;
    }

    bs_node **pre_temp = NULL;
    bs_node *temp = tree->root;
    while (temp != NULL) {
        int res = tree->cp(temp->data, data);
        if (res == 0) {
            if (pre_temp == NULL) {
                if (temp->rchild == NULL) {
                    tree->root = temp->lchild;
                    free(temp);
                }else {

                }
            }else {
                if (temp->rchild == NULL) {
                    *pre_temp = temp->lchild;
                    free(temp);
                }else {
                    bs_node *ltemp = temp->rchild->lchild;


                    temp->rchild->lchild = temp->lchild;
                    *pre_temp = temp->rchild;
                    free(temp);
                }
            }
        }else if (res == 1) {
            pre_temp = &temp->lchild;
            temp = temp->lchild;
        }else if (res == 2) {
            pre_temp = &temp->lchild;
            temp = temp->rchild;
        }
    }
}

int main() {
    bs_tree* bt = create_tree(comp_int);
    insert(bt, 5);
    insert(bt, 3);
    insert(bt, 6);
    insert(bt, 8);

    dump_pre_order(bt->root);

    bs_node *node = search(bt->root, 60);
    if (node == NULL) {
        printf("not find\n");
    }else {
        printf("node:%d\n", node->data);
    }

    destroy_tree(bt);

    return 0;
}