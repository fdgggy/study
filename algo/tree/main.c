/*
前序遍历：树中任意节点，先打印这个节点，再打印左子树，最后打印右子树
中序遍历：树中任意节点，先打印左子树，再打印它本身，最后打印它右子树
后序遍历：树中任意节点，先打印左子树，再打印右子树，最后打印它本身
*/
#include <stdio.h>
#include <stdlib.h>


#define MAX_TREE_NODES (1 << 8)

struct node {
    int data;
};

struct binary_tree{
    union {
        unsigned long nodes;
        struct node *n[MAX_TREE_NODES];
    };
};

void init_binary_tree(struct binary_tree *tree) {
    for (int i = 0; i < MAX_TREE_NODES; i++) {
        tree->n[i] = NULL;
    }
}

struct node* create_node(int data) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    if (n) {
        n->data = data;
    }

    return n;
}

void fake_a_tree(struct binary_tree *tree) {
    int i, data[10] = {7, 4, 9, 2, 6, 8, 10, 1, 3, 5};
    init_binary_tree(tree);

    for (i=0; i < 10; i++) {
        tree->n[i+1] = create_node(data[i]);
    }
    tree->nodes = 10;
}   

//中序遍历
void _in_order(struct binary_tree* tree, int index)
{
	if (!tree->n[index])
		return;

	/* left child at (index << 1) */
	_in_order(tree, index << 1);

	printf("[%2d]: %4d\n", index, tree->n[index]->data);

	/* right child at (index << 1) + 1 */
	_in_order(tree, (index << 1) + 1);
}

void in_order(struct binary_tree* tree)
{
	_in_order(tree, 1);
}

int main() {
    struct node n;
    struct binary_tree tree;
    printf("tree:%ld node:%ld\n", sizeof(tree), sizeof(n)); //2048,4

	fake_a_tree(&tree);
	in_order(&tree);

    return 0;
}