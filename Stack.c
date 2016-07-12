/****************
Structure:
    typedef struct StackNode
    {
        ElementType data;
        struct StackNode* next;
    }Stack;
Function:
    Stack* CreatStack()
    int IsEmpty(Stack*)
    void Push(ElementType, Stack*)
    void Pop(Stack* )
    void PrintStack(Stack*)
    ElementType Top(Stack*)
*****************/
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct StackNode
{
    ElementType data;
    struct StackNode* next;
}Stack;

Stack* CreatStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->next = NULL;
    return s;
}

int IsEmpty(Stack* s)
{
    return s->next == NULL;
}

void Push(ElementType num, Stack* s)
{
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    temp->data = num;
    temp->next = s->next;
    s->next = temp;
}

void Pop(Stack* s)
{
    if(IsEmpty(s))
        printf("Empty stack!");
    else
    {
        Stack* temp = s->next;
        s->next = s->next->next;
        free(temp);
    }
}

void PrintStack(Stack* s)
{
    s = s->next;
    printf("Top->");
    while(s != NULL)
    {
        printf("%d ", s->data);
        s = s->next;
    }
    printf("\n");
}

ElementType Top(Stack* s)
{
    if(IsEmpty(s))
    {
        printf("Empty stack!");
        return 0;
    }
    else
        return s->next->data;
}

int main()
{
    Stack* stack = CreatStack();
    Push(3, stack);
    Push(5, stack);
    Push(6, stack);
    Push(2, stack);
    PrintStack(stack);
    Pop(stack);
    PrintStack(stack);
    printf("%d\n", Top(stack));
    printf("Hello World!");
}
