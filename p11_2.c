#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QuickSort {
    int Capacity;
    int Size;
    int *array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size) {
    QuickSort q = (QuickSort)malloc(sizeof(struct QuickSort));
    q->Capacity = size;
    q->Size = 0;
    q->array = (int*)malloc(size * sizeof(int));
    return q;
}

void Insert(QuickSort q, int a) {
    q->array[q->Size++] = a;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int middle_partition(QuickSort q, int left, int right) {
    int mid = (left + right) / 2;
    int pivot = q->array[mid]; // pivot 값을 가운데 값으로 설정
    int i = left;
    int j = right;

    while (1) {
        while (q->array[i] < pivot)
            i++;

        while (q->array[j] > pivot)
            j--;

        if (i >= j)
            return j;

        swap(&q->array[i], &q->array[j]);

        // pivot 값과 같은 값이 있는 경우 중복 처리
        if (q->array[i] == pivot)
            j--;
        if (q->array[j] == pivot)
            i++;
    }
}


int leftmost_partition(QuickSort q, int left, int right) {
    int pivot = q->array[left]; // pivot 값을 맨 왼쪽 값으로 설정
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= j && q->array[i] <= pivot)
            i++;

        while (j >= i && q->array[j] > pivot)
            j--;

        if (i < j)
            swap(&q->array[i], &q->array[j]);
    }

    swap(&q->array[left], &q->array[j]);
    return j;
}

int rightmost_partition(QuickSort q, int left, int right) {
    int pivot = q->array[right]; // pivot 값을 맨 오른쪽 값으로 설정
    int i = left;
    int j = right - 1;

    while (i <= j) {
        while (i <= j && q->array[i] < pivot)
            i++;

        while (j >= i && q->array[j] >= pivot)
            j--;

        if (i < j)
            swap(&q->array[i], &q->array[j]);
    }

    swap(&q->array[i], &q->array[right]);
    return i;
}

void quicksort(QuickSort q, int left, int right, int type) {
    if (left < right) {
        int pivot;
        if (type == 0) {
            pivot = leftmost_partition(q, left, right);
        } else if (type == 1) {
            pivot = rightmost_partition(q, left, right);
        } else if (type == 2) {
            pivot = middle_partition(q, left, right);
        }

        printf("pivot value: %d\n", q->array[pivot]);
        printf("result: ");
        for (int i = 0; i < q->Size; i++) {
            printf("%d ", q->array[i]);
        }
        printf("\n");
        
        quicksort(q, left, pivot - 1, type);
        quicksort(q, pivot + 1, right, type);

        
    }
}


int main(int argc, char* argv[]) {
    char type_s[10];
    int list_size, key, type_i;
    QuickSort q;
    FILE* fi = fopen(argv[1], "r");
    fscanf(fi, "%s", type_s);
    if (!(strcmp(type_s, "leftmost"))) type_i = 0;
    else if (!(strcmp(type_s, "rightmost"))) type_i = 1;
    else if (!(strcmp(type_s, "middle"))) type_i = 2;

    fscanf(fi, "%d", &list_size);
    q = make_list(list_size);
    for (int i = 0; i < list_size; i++) {
        fscanf(fi, "%d", &key);
        Insert(q, key);
    }

    quicksort(q, 0, list_size - 1, type_i);


    free(q->array);
    free(q);

    fclose(fi);

    return 0;
}

/*
input : 
option for choosing pivot value
max size of list
the list elements to be sorted

아래와 같이 입력을 하면, 
rightmost
9
5 0 7 6 9 2 1 3 8

아래와 같이 출력이 되어야 한다. 
pivot value : 8
result : 5 0 7 6 3 2 1 8 9
pivot value : 1
result : 0 1 7 6 3 2 5 8 9
pivot value : 5
result : 0 1 2 3 5 7 6 8 9
pivot value : 3
result : 0 1 2 3 5 7 6 8 9
pivot value : 6
result : 0 1 2 3 5 6 7 8 9

아래와 같이 입력을 하면,
leftmost
9
5 0 7 6 9 2 1 3 8

아래와 같이 출력이 되어야 한다 
pivot value : 5
result : 2 0 3 1 5 9 6 7 8
pivot value : 2
result : 1 0 2 3 5 9 6 7 8
pivot value : 1
result : 0 1 2 3 5 9 6 7 8
pivot value : 9
result : 0 1 2 3 5 8 6 7 9
pivot value : 8
result : 0 1 2 3 5 7 6 8 9
pivot value : 7
0 1 2 3 5 6 7 8 9


아래와 같이 입력을 하면
middle
9
5 0 7 6 9 2 1 3 8 


아래와 같이 출력이 된다 
pivot value : 9
result : 5 0 7 6 8 2 1 3 9
pivot value : 6
result : 5 0 3 1 2 6 8 7 9
pivot value : 3
result : 2 0 1 3 5 6 8 7 9
pivot value : 0
result : 0 2 1 3 5 6 8 7 9
pivot value : 2
result : 0 1 2 3 5 6 8 7 9
pivot value : 8
result : 0 1 2 3 5 6 7 8 9 

*/