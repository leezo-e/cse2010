#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List; 
typedef PtrToNode Position; 
typedef int ElementType;

struct Node{
    ElementType element; //key
    Position next; //그 다음 노드에 대한 포인터
}; 

List MakeEmptyList();
int isLast(Position p, List l);
void Delete(ElementType x, List l);
Position FindPrevious(ElementType x, List l);
Position Find(ElementType x, List l);
void Insert(ElementType x, Position p, List l);
void DeleteList(List l);
void PrintList(List l);

int main(int argc, char *argv[])
{
    char command;
    int key1, key2;
    FILE *input, *output;
    Position header = NULL, tmp = NULL;

    if (argc <= 1){
        printf("Please enter an input file.");
        return 0;
    }
    else 
        input = fopen(argv[1], "r");
    
    header = MakeEmptyList(); //
    while(1){
        command = fgetc(input);
        if(feof(input)) break;

        switch(command){
            case 'i' : 
                fscanf(input, "%d %d", &key1, &key2); //key1을 key2 옆에 삽입
                if(key1 <= 0){
                    printf("This is invalid key value. %d\n", key1);
                    break;
                }
                if(key2 < -1){
                    printf("This is invalid position.");
                    break;
                }
                tmp = Find(key2, header);
                if (key2 == -1){
                    tmp = header;
                }
                if (tmp == NULL){
                    printf("Insertion(%d) Failed: cannot find the location to be inserted. \n", key1);
                    break;
                }
    
                Insert(key1, tmp, header); //key1을 tmp 옆에 삽입. 
                break;
            case 'd' :
                fscanf(input, "%d", &key1);
                if (Find(key1, header) == NULL){
                    printf("Deletion failed: element %d is not in the list. \n", key1);
                    break;
                };      
                Delete(key1, header);
                break;
            case 'f' :
                fscanf(input, "%d", &key1);
                tmp = FindPrevious(key1, header);
                if(isLast(tmp, header))
                    printf("Could not find %d in the list.\n", key1);
                else if(tmp -> element > 0)
                    printf("Key of the previous node of %d is %d. \n", key1, tmp->element);
                else   
                    printf("Key of the previous node of %d is header.\n", key1);
                break;
            
            case 'p' : 
                PrintList(header);
                break;
            defalut : 
                printf("Invalid command line");

        }
    }

    DeleteList(header);
    fclose(input);

    return 0;
}

List MakeEmptyList(){//확정
    List l = (List)malloc(sizeof(struct Node));
    l -> element = -999;
    l -> next = NULL;
    return l;

} //empty list node 생성

int isLast(Position p, List l){//확정
    Position current = l; 
    while(current->next != NULL){ //현재 노드의 다음 노드가 NULL이면 멈춰. 
        current = current->next;
    }
    return p == current; //마지막 노드 반환
} //return p->next == NULL;

void Insert(ElementType x, Position p, List l){
Position new_node = (Position)malloc(sizeof(struct Node));
new_node -> element = x;
new_node -> next = p -> next;
p -> next = new_node;
}
//리스트 l에서 p 다음에 x를 삽입하는 함수.

Position Find(ElementType x, List l){
    Position p = NULL;
    p = l -> next;
    while(p != NULL && p->element != x){
    p = p -> next;
    }
    return p;
} //리스트에서 x를 찾아서 반환, 찾지 못하면 NULL 반환.

Position FindPrevious(ElementType x, List l){
    Position p = NULL;
    p = l;
    while(p -> next != NULL && p->next->element != x){
        p = p -> next;
    }
    return p;
} //x의 이전 노드 반환.

void Delete(ElementType x, List l){
    Position p = NULL, tmp = NULL;
    p = FindPrevious(x, l);
    if(!isLast(p, l)){
    tmp = p -> next;
    p -> next = tmp -> next;
    free(tmp);
    }
} //리스트에서 x를 찾아 삭제.


void PrintList(List l){
    PtrToNode tmp = NULL;
    tmp = l -> next;
    if(tmp == NULL){
        printf("list is empty!\n");
        return;
    }
    while(tmp != NULL){
        printf("key: %d\t", tmp -> element);
        tmp = tmp -> next;
    }
    printf("\n");
}

void DeleteList(List l){
    Position p = NULL, tmp = NULL;
    p = l -> next;
    l -> next = NULL;
    while(p != NULL){
        tmp = p -> next;
        free(p);
        p = tmp;
    }
}
