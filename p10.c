#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _DisjointSet{
    int size;
    int *ptr_arr;
    // parent
} DisjointSets;

typedef struct _PrintDisjointSet{
    int size;
    int *ptr_arr;
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets* maze, int n){

    sets->size = n;
    sets->ptr_arr = (int*)malloc(n * sizeof(int));
    maze->size = n;
    maze->ptr_arr = (int*)malloc((2*n -1)  * sizeof(int));

    for (int i = 0; i < n; i++) {
        sets->ptr_arr[i] = 0;  // root는 0 초기화 
        maze->ptr_arr[i] = 1;  // wall은 1 초기화 
    }

    maze->ptr_arr[0] = 0;  // 입구 벽 없애
    maze->ptr_arr[n - 1] = 0;  // 출구 벽 없애
}

int find(DisjointSets *sets, int x){
    if (sets->ptr_arr[x] == 0) {
        return x; 
    } else {
        return find(sets, sets->ptr_arr[x]); //root 도착할 때까지 돌려
    }
}

void union_ (DisjointSets *sets, int i, int j){
    
    int root1 = find(sets, i); //각 트리의 루트 찾기 
    int root2 = find(sets, j);

    if (root1 < root2) {
            sets->ptr_arr[root2] = root1; 
        } else {
            if (sets->ptr_arr[root2] == root1)
                sets->ptr_arr[root1]--;
            sets->ptr_arr[root1] = root2;  
        }
}


void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n){

    while (find(sets, 0) != find(sets, n - 1)) {
        int wall = 0;
        srand(time(NULL));
        wall = rand() % (2 * n - 2);  // 난수 찾기 

        int i, j;
        if (wall < n - 1) { 
            i = wall / (n - 1);
            j = wall % (n - 1);
        } else {
            i = (wall - (n - 1)) / (n - 1);
            j = (wall - (n - 1)) % (n - 1);
        }

        
        int is_horizontal = (wall < n - 1) ? 1 : 0; 

        int cell1, cell2;
        if (is_horizontal) {
            cell1 = i * n + j;
            cell2 = (i + 1) * n + j;
        } else {
            cell1 = j * n + i;
            cell2 = j * n + i + 1;
        }

        int root1 = find(sets, cell1);
        int root2 = find(sets, cell2);

        
        if (root1 != root2) { //다른 set면
            union_(sets, cell1, cell2);
            maze->ptr_arr[wall] = 0;  // wall 지우기 
        }
    }
}

void printMaze(PrintDisjointSets *maze, int n){
    for (int i = 0; i < 2 * n - 1; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n - 1; j++) {
                printf((maze->ptr_arr[i * (n - 1) + j] == 1) ? "-" : " ");
            }
            printf("+\n");
        } else {
            for (int j = 0; j < n; j++) {
                printf((maze->ptr_arr[(i - 1) * n + j] == 1) ? "|" : " ");
                printf(" ");
            }
            printf("|\n");
        }
    }
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze){
    free(sets->ptr_arr);
    free(maze->ptr_arr);
    free(sets);
    free(maze);
}

int main(int argc, char* argv[]){
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSets *sets;
    PrintDisjointSets *maze;

    sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

    init(sets, maze, num);

    createMaze(sets, maze, num);

    printMaze(maze, num);

    freeMaze(sets, maze);

    return 0;
}
