#include <stdio.h>
#include <stdlib.h>
#define stackET2 float
//line 49 and 69, the output need to be caution
typedef struct FloatStackNode
{
        stackET2 data;
        struct FloatStackNode* next;
}FloatStack;
    
FloatStack* CreatFloatStack()
{
        FloatStack* s = (FloatStack*)malloc(sizeof(FloatStack));
        s->next = NULL;
        return s;
}

int IsFloatEmpty(FloatStack* s)
{
        return s->next == NULL;
}

void PushFloat(stackET2 num, FloatStack* s)
{
        FloatStack* temp = (FloatStack*)malloc(sizeof(FloatStack));
        temp->data = num;
        temp->next = s->next;
        s->next = temp;
}

void PopFloat(FloatStack* s)
{
    if(IsFloatEmpty(s))
        printf("Empty stack!\n");
    else
    {
        FloatStack* temp = s->next;
        s->next = s->next->next;
        free(temp);
    }
}

void PrintFloatStack(FloatStack* s)
{
    s = s->next;
    printf("Top->");
    while(s != NULL)
    {
        printf("%2.1f ", s->data);
        s = s->next;
    }
    printf("\n");
}

void PrintFloatStackConvet(FloatStack* s)
{
    FloatStack *temp = s->next;
    stackET2 a[100];
    int i=0;
    while(temp != NULL)
    {
        a[i] = temp->data;
        temp = temp->next;
        i++;
    }
    i--;
    while(i >= 0)
    {
        printf("%2.1f ", a[i]);
        i--;
    }
}

stackET2 TopFloat(FloatStack* s)
{
    if(IsFloatEmpty(s))
    {
        printf("Empty stack!\n");
        return 0;
    }
    else
        return s->next->data;
}

// void MakeEmpty(FloatStack* s)
// {
//     if(s)
//     {
//         s = s->next;
//         FloatStack* temp = s->next;
//         free(s);
//         s = temp; 
//     }
// }

