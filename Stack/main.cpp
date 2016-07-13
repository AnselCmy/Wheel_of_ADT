#include <stdio.h>
#include "Stack.h"
int main()
{
	Stack* stack = CreatStack();
	printf("%d\n", Top(stack));
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