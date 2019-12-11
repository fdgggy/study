/*
二叉搜索树：一颗二叉树，可以为空；不为空，满足：
1.非空左子树的所有键值小于其根节点的键值
2.非空右子树的所有键值大于其根节点的键值
3.左右子树都是二叉搜索树
find
findmin
findmax
insert
delete
 */
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

void dump_in_order(bs_node *tree) {
    if (tree == NULL) {
        return;
    }
    dump_in_order(tree->lchild);
    printf("data:%d\n", tree->data);
    dump_in_order(tree->rchild);
}

//也可以用非递归
bs_node *search(bs_node *root, int data) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == data) {
        return root;
    }else if (root->data > data) {
        return search(root->lchild, data);
    }else if (root->data < data) {
        return search(root->rchild, data);
    }
}
/*
1.没有左右子节点，直接删除
2.存在左或右节点，删除后移动子节点
3.同时存在左右节点，需要通过后继节点交换后转换为前2种情况，后继节点为1.右子树最小值  2.左子树最大值
*/
void delete(bs_tree *tree, int data) {
    if (tree == NULL) {
        printf("delete failed, tree is NULL\n");
        return;
    }

    bs_node *temp = tree->root;
    bs_node *p_temp = NULL; //记录temp的父节点

    while (temp != NULL) {
        int res = tree->cp(temp->data, data);
        if (res == 0) {
            break;
        }else if (res == 1) {
            p_temp = temp;
            temp = temp->lchild;
        }else if (res == 2) {
            p_temp = temp;
            temp = temp->rchild;
        }
    }
    if (temp == NULL) {
        printf("delete failed not find:%d\n", data);
        return;
    }
    if (temp->lchild != NULL && temp->rchild != NULL) {
        bs_node *min_temp = temp->rchild;
        p_temp = temp;
        while (min_temp->lchild != NULL)
        {
            p_temp = min_temp;
            min_temp = min_temp->lchild;
        }
        temp->data = min_temp->data;
        temp = min_temp;
    }

    bs_node *child = NULL;
    if (temp->lchild != NULL) {
        child = temp->lchild;
    }else if (temp->rchild != NULL) {
        child = temp->rchild;
    }else {
        child = NULL;
    }

    if (p_temp == NULL) {
        tree->root = child;
    }else if (temp == p_temp->lchild) {
        p_temp->lchild = child;
    }else {
        p_temp->rchild = child;
    }

    tree->size--;
    free(temp);
}

int main() {
    bs_tree* bt = create_tree(comp_int);
    insert(bt, 5);
    insert(bt, 1);
    insert(bt, 2);
    insert(bt, 8);
    insert(bt, 7);
    insert(bt, 9);
    insert(bt, 10);

    dump_in_order(bt->root);

    bs_node *node = search(bt->root, 60);
    if (node == NULL) {
        printf("not find\n");
    }else {
        printf("node:%d\n", node->data);
    }

    // delete(bt, 5);  //删除root
    // delete(bt, 8);  //删除带2个节点的节点
    delete(bt, 1);     //删除带1个节点的节点
    // delete(bt, 7);  //删除没有节点的节点


    printf("delete tree\n");
    dump_pre_order(bt->root);

    destroy_tree(bt);

    return 0;
}