#include <stdio.h>
#include <stdlib.h>

struct MergeSort {
    int Capacity;
    int Size;
    int* array;
    int* Tmparray;
};

typedef struct MergeSort* Mergesort;

Mergesort make_list(int size) {
    Mergesort M = (Mergesort)malloc(sizeof(struct MergeSort));
    M->Capacity = size;
    M->Size = 0;
    M->array = (int*)malloc(sizeof(int) * size);
    M->Tmparray = (int*)malloc(sizeof(int) * size);
    return M;
}

void Insert(Mergesort m, int a) {
    if (m->Size >= m->Capacity) {
        //입력 받은 숫자의 개수가 capacity보다 클 때는 삽입 무시 
        printf("Ignore additional insertions!\n");
        return;
    }
    m->array[m->Size++] = a;
}


void printArray(Mergesort A, int l, int r) {
    if (l > r || l < 0 || r >= A->Size) {
        // 유효하지 않은 인덱스 범위이므로 예외 처리를 추가해야 합니다.
        return;
    }
    for (int i = l; i <= r; i++) {
        printf("%d ", A->array[i]);
    }
    printf("\n");
}



void Merge(Mergesort A, int l, int m, int r) {
    int left_end, num, tmp;
    left_end = m - 1;
    tmp = l;
    num = r - l + 1;

    while(l <= left_end && m <= r){
        if (A->array[l]<=A->array[m])
            A->Tmparray[tmp++] = A -> array[l++];
        else 
            A->Tmparray[tmp++] = A -> array[m++];            
    }

    while (l <= left_end)
        A->Tmparray[tmp++] = A->array[l++];
    while (m <= r)
        A->Tmparray[tmp++] = A->array[m++];

    for (int i = 0; i<num; i++, r--)
        A->array[r] = A->Tmparray[r];

}

/*void Merge(Mergesort A, int l, int m, int r) {
    int a = 0;
    int b = 0;
    int c = l;

    int n1 = m - l + 1;
    int n2 = r - m;

    for (int i = 0; i < n1; i++) {
        A->Tmparray[i] = A->array[l + i];
        //임시배열에 앞 배열 복사 
    }

    for (int i = 0; i < n2; i++) {
        A->Tmparray[n1 + i] = A->array[m + 1 + i];
        //임시배열에 뒷 배열 복사 
    }

    while (a < n1 && b < n2) {
        if (A->Tmparray[a] <= A->Tmparray[n1 + b]) {
            A->array[c] = A->Tmparray[a];
            a++;
        } else {
            A->array[c] = A->Tmparray[n1 + b];
            b++;
        }
        c++;
    }

    while (a < n1) {
        A->array[c++] = A->Tmparray[a++];
    }

    while (b < n2) {
        A->array[c++] = A->Tmparray[n1 + b++];
    }
}
*/




void RmergeSort(Mergesort A, int l, int r) {
    if (l < r) {
        int m = (l + r)/ 2; 
        RmergeSort(A, l, m);
        RmergeSort(A, m + 1, r);
        Merge(A, l, m+1, r);
        printArray(A, l, r);
    }
}

void ImergeSort(Mergesort A, int n) {
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size < n; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? (left_start + 2 * curr_size - 1) : (n - 1);
            Merge(A, left_start, mid+1, right_end);
            printArray(A, left_start, right_end);
        }
    }
}


/*

void ImergeSort(Mergesort A, int n) {
	int a = 2;
	while (a <= n/2) {
		int i = 0;
		for (i = 0; i + a - 1 <=n; i+=a) {
			Merge(A, i, i + a / 2, i + a - 1);
			printArray(A, i, i + a - 1);
		}
		if (i <= n) {
			printArray(A, i , n);
		}
		a *= 2;
        Merge(A, 0, a/2, n);
	    printArray(A, 0, n);
	}
	

}
*/






void freeMerge(Mergesort A){
    free(A->array);
    free(A->Tmparray);
    free(A);
}

int main(int argc, char* argv[]) {
    int size, key;
    FILE* fi = fopen(argv[1], "r");
    Mergesort iter_m, rec_m;

    fscanf(fi, "%d", &size);

    iter_m = make_list(size);
    rec_m = make_list(size);

    for (int i = 0; i < size; i++) {
        fscanf(fi, "%d", &key);
        Insert(iter_m, key);
        Insert(rec_m, key);
    }

    printf("input : \n");
    printArray(iter_m, 0, iter_m->Size - 1);
    printf("\n");

    printf("iterative : \n");
    ImergeSort(iter_m, iter_m->Size);
    printf("\n");

    printf("recursive : \n");
    RmergeSort(rec_m, 0, rec_m->Size-1);
    printf("\n");

    return 0;


    fclose(fi);
    freeMerge(iter_m);
    freeMerge(rec_m);

}


//capacity를 초과했을 시 확인도 해줘


/*input 예시
input:10 
26 5 77 1 61 11 59 15 48 19

output 예시
input  : 
26 5 77 1 61 11 59 15 48 19

iterative :
5 26
1 77
11 61 
15 59
19 48 
1 5 26 77
11 15 59 61
19 48 
1 5 11 15 26 59 61 77
19 48
1 5 11 15 19 26 48 59 61 77

recursive :
5 26
5 26 77
1 61 
1 5 26 61 77
11 59 
11 15 59
19 48 
11 15 19 48 59 
1 5 11 15 19 26 48 59 61 77

input : 
10 7 3 8 5 2 1 

iterative : 
7 10 
3 8 
2 5 
1
3 7 8 10 
1 2 5 
1 2 3 5 7 8 10 

recursive : 
7 10 
3 8 
3 7 8 10 
2 5 
1 2 5 
1 2 3 5 7 8 10 

*/

//1이 출력되지 않는 문제를 해결해보자....