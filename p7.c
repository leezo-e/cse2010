#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(ElementType num1, ElementType num2){
    return (num1 > num2) ? num1 : num2;
}

int Height (Position P){
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

Position SingleRotateWithLeft(Position node){
    Position root = node->Left;
    node->Left = root->Right;
    root->Right = node;
    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
    root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
    return root;
}

Position SingleRotateWithRight(Position node){
    Position root = node->Right;
    node->Right = root->Left;
    root->Left = node;
    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
    root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
    return root;
}

Position DoubleRotateWithLeft(Position node){
    node->Left = SingleRotateWithRight(node->Left);
    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
    node->Right = SingleRotateWithLeft(node->Right);
    return SingleRotateWithRight(node);
}


AVLTree Insert(ElementType X, AVLTree T){
    if (T == NULL) {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        if (T == NULL) {
            printf("Out of space\n");
            exit(1);
        } else {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) {
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) {
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    else if (X == T->Element){
        printf("Insertion Error: %d already in the tree! \n", T->Element);
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T){
    if (T != NULL) {
        PrintInorder(T->Left);
        printf("%d(%d) ", T->Element, T->Height);
        PrintInorder(T->Right);
    }
}


void DeleteTree(AVLTree T){
    
    if(T->Left != NULL)
        DeleteTree(T->Left);
    if(T->Right !=NULL)
        DeleteTree(T->Right);
    free(T);    
}

int main(int argc, char **argv){

    AVLTree myTree = NULL;
    int key;

    FILE *fi = fopen(argv[1], "r");
    while(fscanf(fi,"%d", &key)!=EOF){
        myTree = Insert(key, myTree);
        PrintInorder(myTree);
        printf("\n");
    }
    fclose(fi);

    DeleteTree(myTree);
    return 0;
}
