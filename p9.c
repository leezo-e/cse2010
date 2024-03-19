#include <stdlib.h>
#include <stdio.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
    int capacity; //max heap capacity
    int size; //current heap size
    int *elements;
};

Heap CreateHeap(int heapSize){
    Heap H = (Heap)malloc(sizeof(struct HeapStruct));
    H->capacity = heapSize;
    H->size = 0;
    H->elements = (int*)malloc(sizeof(int) * heapSize);
    return H;
}

void Insert(Heap heap, int value){
    
    if (heap->size == heap->capacity){
        printf("Insertion Error: Max Heap is full.\n");
        return;
    }//꽉 찼을 때 

    for (int i = 1; i <= heap->size; i++){
        if(heap->elements[i] == value){
            printf("%d is already in the heap.\n", value);
            return ;
        }
    } //겹치는 value가 존재할 때
    

    int i;
    if (heap->size < heap->capacity){
        for(i = ++heap->size; i > 1 && heap->elements[i/2] < value; i /= 2) {
            // i= 1 되면 멈춰야 됨!! max heap이니까 value가 더 크면 stop
            heap->elements[i] = heap->elements[i/2];
        }
        heap->elements[i] = value;
        printf("Insert %d \n", value);
        return;

    } //insert 
   
        
}

int Find(Heap heap, int value){
   for (int i = 1; i <= heap->capacity; i++){
        if(heap->elements[i] == value){
            return 1;
        }
    }
    return 0;//여기 돌려보고 수정 
}

void DeleteMax(Heap heap){

    if (heap->size == 0){
        printf("Deletion Error: Max Heap is empty!\n");
        return;
    } //비어있으면 에러 메시지 
    
    int i, child;
    
    int max = heap->elements[1];
    int last = heap->elements[heap->size--];
    
    printf("Max element(%d) deleted. \n", max);
    //우선 루트 노드 출력
    
    for (i = 1; i*2 <= heap->size; i = child){
        child = i*2;
        if (heap->elements[child+1] > heap ->elements[child] && child != heap-> size){
            child++;
        }
        if (last < heap->elements[child]){
            heap->elements[i] = heap->elements[child];
        }
        else  
            break;
    }
    
    heap -> elements[i] = last;
    //루트노드 없앤 뒤에 재정렬 
}



void PrintHeap(Heap heap){
    if (heap->size == 0)
        printf("Max Heap is empty!\n");
    else {
        for (int i = 1; i <= heap->size; i++){
            printf("%d ", heap -> elements[i]);
        }
        printf("\n");
    }
}

void FreeHeap(Heap heap){
    free(heap->elements);
    free(heap);
}

int main(int argc, char* argv[]){

    FILE *fi = fopen(argv[1],"r");
    char cv;
    Heap maxHeap;
    int value, maxValue;

    while(!feof(fi)){
        fscanf(fi, "%c", &cv);
        switch(cv){
        case 'n':
            fscanf(fi, "%d", &value);
            maxHeap = CreateHeap(value);
            break;
        case 'i':
            fscanf(fi, "%d", &value);
            Insert(maxHeap, value);
            break;
        case 'd':
            DeleteMax(maxHeap);
            break;
        case 'f':
            fscanf(fi, "%d", &value);
            if(Find(maxHeap, value))
                printf("%d is in the heap. \n", value);   
            else
                printf("%d is not in the heap. \n", value);
            break;
        case 'p':
            PrintHeap(maxHeap);
        }

    }
    FreeHeap(maxHeap);
}