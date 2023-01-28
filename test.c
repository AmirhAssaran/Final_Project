#include <stdio.h>
#include <stdlib.h>
 
#define MAX 5
 
int top = -1, stack[MAX];
void push();
void pop();
void display();
 
int main() {
    /*
    int ch;
    while (1) {
        printf("\n*** Stack Menu ***");
        printf("\n\n1.Push\n2.Pop\n3.Display\n4.Exit");
        printf("\n\nEnter your choice(1-4):");
        scanf("%d",&ch);

        switch (ch) {
            case 1: push();
            break;
            case 2: pop();
            break;
            case 3: display();
            break;
            case 4: exit(0);
            default: printf("\nWrong Choice!!");
        }
    }
    */
    int array[3] = {1, 2, 3};
    push(array, 1);
    push(array, 0);
    pop(array, 2);
    printf("%d\n", array[2]);
}
 
void push(int *array, int num) {

    int val = *(array + num);
    if(top == MAX - 1) {
        printf("\nStack is full!!");
    }
    else {
        top = top  +1;
        *(stack + top) = val;
    }
}

void pop (int *array, int num) {
    if(top == -1) {
        printf("\nStack is empty!!");
    }
    else {
        *(array + num) = *(stack + top);
        printf("%d\n", stack[top]);
        top = top - 1;
    }
}
 
