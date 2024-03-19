#include <stdio.h>
#include <stdlib.h>

/*
input의 유효성은 판단할 필요 없음
operand는 1~9까지
expression은 100 넘으면 안 되고 
# 나오면 expression의 끝. 
stack의 최대 size는 10

number 만나면 stack에 넣어
operator 만나면, 2개의 number들을 
stack에서 pop하고 그 result를 스택에 다시 push...
*/
typedef struct Stack{
    int* key; //key
    int top; //index
    int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack *s, int x);
int Pop(Stack* s);
int Top(Stack* s); //Top(Stack) 구현 안해도 된다?
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

void main(int argc, char* argv[]){

    FILE* fi = fopen(argv[1], "r");

    Stack* stack = CreateStack(10);

    char c;
    printf("Top numbers: ");
    while(1){
        int cnt = 0;
        fscanf(fi, "%c", &c);
        if (c == '#')
            break;

        Postfix(stack, c);
        printf("%d ", Top(stack));
        cnt ++;
        if (cnt >= 99) {
            printf("Stop.\n");
            break;
        }
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));

    fclose(fi);
    DeleteStack(stack);

}

Stack* CreateStack(int max) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->key = (int*)malloc(sizeof(int) * max);
    s->top = -1; //empty
    s->max_stack_size = max;
    return s;
}

void Push(Stack* s, int x) {
    if (IsFull(s)) {
        printf("Error: stack is full.\n");
        return;
    }
    s->top++;
    s->key[s->top] = x;
}

int Pop(Stack* s) {
    if (IsEmpty(s)) {
        printf("Error: stack is empty\n");
        return -1;
    }
    int val = s->key[s->top];
    s->top--;
    return val;
}

int Top(Stack* s) {
    if (IsEmpty(s)) {
        printf("Error: stack is empty\n");
        return -1;
    }
    return s->key[s->top];
}

void DeleteStack(Stack* s) {
    free(s->key);
    free(s);
}

int IsEmpty(Stack* s) {
    return s->top == -1;
}

int IsFull(Stack* s) {
    return s->top == s->max_stack_size - 1;
}

void Postfix(Stack* s, char input_str) {
    if (input_str >= '1' && input_str <= '9') {
        int num = input_str - '0';
        Push(s, num);
    } 
    else if (input_str == '+' || input_str == '-' || input_str == '*' || input_str == '/' || input_str == '%') {
        int num2 = Pop(s);
        int num1 = Pop(s);
        int result;
        if (input_str == '+') {
            result = num1 + num2;
        } else if (input_str == '-') {
            result = num1 - num2;
        } else if (input_str == '*') {
            result = num1 * num2;
        } else if (input_str == '/') {
            result = num1 / num2;
        } else if (input_str == '%'){
            result = num1 % num2;
        }

        Push(s, result);
    }
    else if(input_str == ','){
        printf("This operator is invalid.\n");
    }
}
