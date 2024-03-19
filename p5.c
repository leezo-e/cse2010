#include <stdio.h>
#include <stdlib.h>

struct CircularQueueStruct{
    int *key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;

};

typedef struct CircularQueueStruct* CircularQueue;

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q, int X);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue);

void main(int argc, char* argv[]){

    char command;
    FILE *input;
    CircularQueue queue;
    int queueSize;
    int tmpNum;

    input = fopen(argv[1], "r");

    //queue = MakeEmpty(queueSize);

    while(1){
        command = fgetc(input);
        if(feof(input)) break;
        switch(command){
            case 'n' : 
                fscanf(input, "%d", &queueSize);
                queue = MakeEmpty(queueSize);
                break;
            case 'e' :
                fscanf(input, "%d", &tmpNum);
                Enqueue(queue, tmpNum);
                break;
            case 'd' :
                Dequeue(queue);
                break;
            case 'f' :
                PrintFirst(queue);
                break;
            case 'r' :
                PrintRear(queue);
                break;
            default : 
                break;
        }
    }
    DeleteQueue(queue);

}

CircularQueue MakeEmpty(int max){
    CircularQueue Q;
    Q = (CircularQueue)malloc(sizeof(struct CircularQueueStruct));
    Q->key = (int*)malloc(sizeof(int)*max);
    Q->max_queue_size = max;
    Q->qsize = 0;
    Q->first = 0;
    Q->rear = -1;
    return Q;
}

int IsEmpty(CircularQueue Q){
    return Q->qsize == 0;
}

int IsFull(CircularQueue Q){
    return Q->qsize == Q->max_queue_size;
}

void Dequeue(CircularQueue Q){
    if (IsEmpty(Q)) {
        printf("Dequeue failed : Queue is Empty!\n");
        return;
    }
    printf("Dequeue %d\n", Q->key[Q->rear]); 
    Q->qsize--;
    Q->first = (Q->first + 1) % Q->max_queue_size;
}

void Enqueue(CircularQueue Q, int X){
    if (IsFull(Q)) {
        printf("Enqueue failed : Queue is Full!\n");
        return;
    }
    Q->qsize++;
    Q->rear = (Q->rear + 1) % Q->max_queue_size;
    Q->key[Q->rear] = X;
    printf("Enqueue %d\n", X);
}

void PrintFirst(CircularQueue Q){
    if (IsEmpty(Q)) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("First : %d\n", Q->key[Q->first]);
}

void PrintRear(CircularQueue Q){
    if (IsEmpty(Q)) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Rear : %d\n", Q->key[Q->rear]);
}

void DeleteQueue(CircularQueue Q){
    free(Q->key);
    free(Q);
}
