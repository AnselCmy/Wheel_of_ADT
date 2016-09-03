#include <stdio.h>
#include <stdlib.h>
// #include "Struct_Define.cpp"
// #define stackET SearchTree*

// typedef struct TreeNode SearchTree;

// typedef struct StackNode
// {
//     	// stackET data;
//         SearchTree* data;
//     	struct StackNode* next;
// }Stack;
    
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

void Push(stackET num, Stack* s)
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

stackET Top(Stack* s)
{
	if(IsEmpty(s))
	{
		printf("Empty stack!");
		return NULL;
	}
	else
		return s->next->data;
}

void PrintStack(Stack* s)
{
    s = s->next;
    printf("Top->");
    while(s != NULL)
    {
        printf("%d ", s->data->data);
        s = s->next;
    }
    printf("\n");
}

void PrintStackInverted(Stack* s)
{
    Stack *temp = s->next;
    int a[100];
    int i=0;
    while(temp != NULL)
    {
        a[i] = temp->data->data;
        temp = temp->next;
        i++;
    }
    i--;
    while(i >= 0)
    {
        printf("%d ", a[i]);
        i--;
    }
}