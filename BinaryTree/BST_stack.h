#include <stdio.h>
#include <stdlib.h>
#define stackET SearchTree*

typedef struct TreeNode SearchTree;

typedef struct StackNode
{
    	stackET data;
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