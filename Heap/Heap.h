#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MaxData 10000//哨兵放在data[0]的位置

typedef struct  Heap
{
	ElementType *data;
	int size;
	int capacity;
} MaxHeap;


MaxHeap* CreatMaxHeap(int c) //c指的时堆的capacity
{
	MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
	h->size = 0;
	h->capacity = c;
	h->data = (ElementType*)malloc(sizeof(ElementType) * (c+1));
	h->data[0] = MaxData;  //哨兵 
	return h;
}

//这里的PercDown()就是下滤节点， 在delete和creat里面可以简化代码
void PercDown(ElementType a[], int start, int end)  //a时需要变成符合堆的条件的数组，
													//start是这个堆的头节点，end是尾
{
	int child;
	int parent = start;
	ElementType temp = a[start]; //保存头节点的数值
	for(parent; parent*2 <= end; parent = child)
	{
		child = 2*parent; //先指向左儿子
		if(2*parent+1<=end && a[child +1] > a[child])
		{
			child++;  //如果右边大，则指向右儿子
		}

		if(temp >= a[child])
		{
			break;
		}
		else
		{
			a[parent] = a[child];
		}
	}
	a[parent] = temp;
}	

//增加了PercDown()函数之后修改的creat函数
MaxHeap* CreatMaxHeapWithArray(ElementType* num, int len)
{
	//先动态内存分配
	MaxHeap *h = (MaxHeap*)malloc(sizeof(MaxHeap));
	h->size = len;
	h->capacity = len;
	h->data = (ElementType*)malloc(sizeof(ElementType) * (len+1));
	h->data[0] = MaxData;
	int i;
	for(i=1; i<=len; i++)
	{
		h->data[i] = num[i-1];  //先把所有数据放入堆中
	}
	
	for(i=len/2; i>0; i--) //从最右下角的堆慢慢开始建立
	{
		PercDown(h->data, i, len);
	}
	return h;
}

int IsFull(MaxHeap* h)
{
	return h->size == h->capacity;
}

int IsEmpty(MaxHeap* h)
{
	return h->size == 0;
}

void Insert(ElementType num, MaxHeap* h)
{
	if( IsFull(h) )
	{
		printf("Heap is full!\n");
		return;
	}
	int i = ++h->size;
	for(; h->data[i/2] < num; i = i/2)  //因为设置了哨兵MaxData才可以这样写
	{
		h->data[i] = h->data[i/2];
	}
	h->data[i] = num;
}	

//增加了PrecDown()之后的delete
ElementType DeleteMax(MaxHeap* h)
{
	if( IsEmpty(h) )
	{
		printf("Heap is empty!\n");
		return MaxData;
	}
	else
	{
		ElementType deleteData = h->data[1]; //保存根节点，为了最后需要返回这个值
		h->data[1] = h->data[h->size--]; //直接拿最后一个值覆盖根节点，然后向下过滤
		PercDown(h->data, 1, h->size);
		return deleteData;
	}
}

void PrintHeap(MaxHeap* h, int len)
{
	int  i;
	for(i = 1; i<=len; i++)
	{
		printf("%d ", h->data[i]);
	}
	printf("\n");
}