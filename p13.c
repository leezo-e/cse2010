#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node {
    int vertex;
    int dist;
    int prev;
} Node;

typedef struct Graph {
    int size;
    Node* nodes;
    int** matrix;
} Graph;

typedef struct Heap {
    int capacity;
    int size;
    Node* elements; //vertex, distance, previous 
} Heap;


//Heap은 permanent 될 때마다 저장해두는 역할? 

Graph* createGraph(int x);
Graph* findShortestPath(Graph* G, int s);
void printShortestPath(Graph* G);
Heap* createMinHeap(int x);
void insert(Heap* H, Node N);
Node deleteMin(Heap* H);
void decreaseKey(Heap* H, Node N);


Graph* createGraph(int x) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->size = x;
    g->nodes = (Node*)malloc(sizeof(Node) * (x + 1));
    g->matrix = (int**)malloc(sizeof(int*) * (x + 1));

    for (int i = 1; i <= x; i++){
        g->nodes[i].vertex = i;
        g->nodes[i].dist = INF;
        g->nodes[i].prev = -1;
    }

    for (int i = 1; i <= x; i++) {
        g->matrix[i] = (int*)malloc(sizeof(int) * (x + 1));
        for (int j = 1; j <= x; j++) {
            if (i == j) {
                g->matrix[i][j] = 0;
            }
            else {
                g->matrix[i][j] = INF;
            }
        }
    }

    return g;
}

Graph* findShortestPath(Graph* G, int s) {

    //다익스트라 
    Heap* minHeap = createMinHeap(G->size);
    int* vst = (int*)calloc(G->size + 1, sizeof(int)); 

    for (int i = 1; i <= G->size; i++) {
        G->nodes[i].dist = INF;
        G->nodes[i].prev = -1;
    }
    G->nodes[s].dist = 0;
    insert(minHeap, G->nodes[s]);

    while (minHeap->size > 0) {
        Node minNode = deleteMin(minHeap);
        int u = minNode.vertex;
        vst[u] = 1; 

        for (int v = 1; v <= G->size; v++) { 
            if (G->matrix[u][v] != INF) {
                int temp = G->nodes[u].dist + G->matrix[u][v]; 
                if (temp < G->nodes[v].dist) {
                    G->nodes[v].dist = temp;
                    G->nodes[v].prev = u;
                    Node update;
                    update.vertex = v;
                    update.dist = temp;
                    insert(minHeap, update);
                }
                else if (temp == G->nodes[v].dist && u < G->nodes[v].prev) {
                    G->nodes[v].prev = u;  // 같은 거리인 경우 더 작은 정점을 prev로 갱신
                }
            }
        }
    }
    free(minHeap->elements);
    free(minHeap);
    free(vst);

    return G;
}

void printShortestPath(Graph* G) {
    //print 
    for (int i = 2; i <= G->size; i++) {
        if (G->nodes[i].dist == INF) {
            printf("%d can not be reached\n", i);
        }
        else {
            int vertex = i;
            printf("%d", vertex);
            while (G->nodes[vertex].prev != -1) {
                vertex = G->nodes[vertex].prev;
                printf("<-%d", vertex);    
            }
            printf(" cost: %d\n", G->nodes[i].dist);
        }
    }
}

Heap* createMinHeap(int x) {
    Heap* H = (Heap*)malloc(sizeof(struct Heap));
    H->capacity = x;
    H->size = 0;
    H->elements = (Node*)malloc((x + 1) * sizeof(Node));
    return H;
}

void insert(Heap* H, Node N) {
    if (H->size == H->capacity) {
        return;
    }

    int i = ++H->size;

    while (i > 1 && N.dist < H->elements[i / 2].dist) {
        H->elements[i] = H->elements[i / 2];
        i /= 2;
    }

        H->elements[i] = N;
  
}

Node deleteMin(Heap* H) {
    //distance가 제일 작은 노드를 삭제하기
    Node min = H->elements[1];
    Node last = H->elements[H->size--];
    int i = 1;
    int child;


    while( i*2 <= H->size) {
        child = i * 2;

        if (child != H->size && H->elements[child + 1].dist < H->elements[child].dist) {
            child++;
        }

        if (last.dist > H->elements[child].dist) {
            H->elements[i] = H->elements[child];
            i = child;
        }
        else {
            break;
        }
    }

    H->elements[i] = last;

    return min; 
}

void decreaseKey(Heap* H, Node N) {

    //reconsturct the heap
    int i;

    for (i = 1; i <= H->capacity; i++) {
        if (H->elements[i].vertex == N.vertex) {
            break;
        }
    }

    H->elements[i].dist = N.dist;

    while (i != 1 && H->elements[i].dist < H->elements[i/2].dist) {
        Node temp = H->elements[i];
        H->elements[i] = H->elements[i/2];
        H->elements[i/2] = temp;
        i /= 2;
    }
}

int main(int argc, char* argv[]) {
    FILE* fi = fopen(argv[1], "r");
    int size;

    fscanf(fi, "%d", &size);

    Graph* G = createGraph(size);

    int node_s, node_d, weight;

    while ((fscanf(fi, "%d %d %d", &node_s, &node_d, &weight)) != EOF) {
        G->matrix[node_s][node_d] = weight;
    }

    G = findShortestPath(G, 1);

    printShortestPath(G);

    for (int i = 1; i <= G->size; i++) {
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G->nodes);
    free(G);

    fclose(fi);

    return 0;
}

