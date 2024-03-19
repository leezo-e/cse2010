
#include <stdio.h>
#include <stdlib.h>

struct TreeStruct {
    int size;
    int numOfNode;
    int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size) {
    Tree T = (Tree)malloc(sizeof(struct TreeStruct));
    T->size = size;
    T->numOfNode = 0;
    T->element = (int*)malloc(sizeof(int) * size);
    return T;
}

void Insert(Tree tree, int value) {
    if (tree->numOfNode < tree->size) {
        tree->element[tree->numOfNode++] = value;
    }
    else {
        printf("Error! Tree is full.\n");
    }
}

void PrintPreorder(Tree tree, int index) {
    if (index >= tree->numOfNode) {
        return;
    }
    printf("%d ", tree->element[index]);
    PrintPreorder(tree, 2 * index + 1);
    PrintPreorder(tree, 2 * index + 2);
}

void PrintInorder(Tree tree, int index) {
    if (index >= tree->numOfNode) {
        return;
    }
    PrintInorder(tree, 2 * index + 1);
    printf("%d ", tree->element[index]);
    PrintInorder(tree, 2 * index + 2);
}

void PrintPostorder(Tree tree, int index) {
    if (index >= tree->numOfNode) {
        return;
    }
    PrintPostorder(tree, 2 * index + 1);
    PrintPostorder(tree, 2 * index + 2);
    printf("%d ", tree->element[index]);
}

void PrintTree(Tree tree) {
    printf("Preorder: ");
    PrintPreorder(tree, 0);
    printf("\nInorder: ");
    PrintInorder(tree, 0);
    printf("\nPostorder: ");
    PrintPostorder(tree, 0);
    printf("\n");
}

void DeleteTree(Tree tree) {
    free(tree->element);
    free(tree);
}

int main(int argc, char* argv[]) {
    FILE* fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);

    while (fscanf(fi, "%d", &tmpNum) == 1) {
        Insert(tree, tmpNum);
    }
    PrintTree(tree);
    DeleteTree(tree);
    return 0;
}
