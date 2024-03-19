#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue
{
    int size;
    int *key;
    int front;
    int rear;
}Queue;

Queue *CreateQueue (int x){
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->size = x;
    Q->key = (int *)malloc(sizeof(int) * x);
    Q->front = -1;
    Q->rear = -1;
    return Q;
}

void Enqueue(Queue *Q, int item){
    //여기 다시 해봐 
    if(Q->rear == Q->size - 1){
        printf("Queue is full! \n");
    }
    else {
        Q->key[++Q->rear] = item;
    }
}

int Dequeue(Queue *Q){
    if(Q->front == Q->rear){
        printf("Queue is empty! \n");
        return -1;
    }
   
    return Q->key[++Q->front]; 

    //여기 안 되면 Q-> front ++ 하고 해보기
}

//Queue는 언제 free하지?

typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
}Graph;

Graph *CreateGraph(int x){
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->size = x;
    G->vertex = (int*)malloc(sizeof(int) * x);
    G->edge = (int**)malloc(sizeof(int*) * x);

    for (int i = 0; i < x; i++){
        G->edge[i] = (int *)malloc(sizeof(int) * x);
        for (int j = 0; j < x; j++){
            G->edge[i][j] = 0;
        }
    }
    return G;
    //Create vertices
    //Create adjacency matrix
    //All the input nodes will be positivie numbers
}

void InsertEdge(Graph *G, int u, int v){
    //u,v는 노드값이니까 해당되는 index 값으로 바꿔줘야 함! 
    int idx_u = -1;
    int idx_v = -1;

    for (int i = 0; i < G->size; i++){
        if (G->vertex[i] == u)
            idx_u = i;
        if (G->vertex[i] == v)
            idx_v = i;
    }
    if(idx_u != -1 && idx_v != -1)
        G->edge[idx_u][idx_v] = 1;
}

void Topsort(Graph *G){

    int indegree [G->size];
    Queue *Q = CreateQueue(G->size);

    for (int i = 0; i < G->size; i++)
        indegree[i] = 0;
        //초기화

    for (int i = 0; i < G->size; i++){
        for (int j = 0; j < G->size; j++){
            if (G->edge[j][i] == 1){
            indegree[i]++;
            }
        }
    }
    // indegree에 총 개수 저장하기!

    for (int i = 0; i < G->size; i++){
        if (indegree[i] == 0)
            Enqueue(Q, i);
        }
    //

    while (Q->front != Q->rear){
        int vtx = Dequeue(Q);
        //dequeue에서 index를 받는 거니까...? 
        printf("%d ", G->vertex[vtx]);
        for (int i = 0; i < G->size; i++){
            if (G->edge[vtx][i] == 1){
                indegree[i]--;
                if (indegree[i] == 0)
                    Enqueue(Q, i);    
            }
        }
    }
    printf("\n");

    free(Q);
}

void _free(Graph *G){
    free(G->vertex);
    for (int i = 0; i < G->size-1; i++){
        free(G->edge[i]);
    }
    free(G->edge);
    free(G);
}

int main(int argc, char* argv[]){
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);
    
    //scanf("%d", &X);
  
    Graph *G = CreateGraph(X);

    for (int i = 0 ; i < X ; i++){
        fscanf(fi, "%d", &G->vertex[i]);
        //scanf("%d", &G->vertex[i]);
    }


    while (fscanf(fi, "%d %d", &u, &v)!= EOF){
        InsertEdge(G, u, v);
    }

    /*while(u != 0){
        scanf("%d %d", &u, &v);
        InsertEdge(G, u, v);
    }
    */

    Topsort(G);

    fclose(fi);

    _free(G);

    return 0;
}

/*
input file 
1 : the number of vertices
2 :  vertex key (not index
3 ~ last : edge (a -> b)

expected output
: topological sorting result 


input & output example
input:
5
1 2 3 4 5 
1 2 
2 3
3 4 
4 5 

output:
1 2 3 4 5 


input : 
6 
11 13 15 17 19 21 
11 13
11 15
13 17
13 19
15 17
15 19
17 19

output :
11 21 13 15 17 19

input : 9
1 5 6 7 2 3 4 8 9
1 6 
1 7 
1 3 
5 7 
5 2 
5 3
7 2
2 3 
7 6
6 4 
7 4
7 9
2 8
3 8 
2 9 

output :
1 5 7 6 2 4 3 9 8 

input1는 잘 나옴 , Input2sms segmentation fault
input3는 순서가 이상해
 */
