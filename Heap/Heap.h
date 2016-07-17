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

MaxHeap* CreatMaxHeapWithArray(ElementType* num, int len) //传入数组来建立堆
{
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

	int child;
	int parent = h->size/2;
	for(parent; parent >= 1; parent--)
	{
		//和DeleteMax的方法一样
		int temp = h->data[parent];
		for(parent; 2*parent<=h->size; parent = child)
		{
			child = 2*parent;  //先指向左儿子
			if( (2*parent+1) <= h->size && h->data[child] < h->data[child+1] )
			{
				child++;  //把最大的儿子的位置赋值给child
			}

			if( temp >= h->data[child] )  //temp一直悬在空中，并未赋值给谁，一直拿来作比较
			{
				break;
			}
			else
			{
				h->data[parent] = h->data[child];
			}
		}
		h->data[parent] = temp;
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

ElementType DeleteMax(MaxHeap* h)
{
	if( IsEmpty(h) )
	{
		printf("Heap is empty!\n");
		return MaxData;
	}
	else
	{
		int parent, child;
		int deleteData = h->data[1];  //保存根节点的值，因为最后需要返回
		int temp = h->data[h->size--];  //size = size - 1
		for(parent=1; 2*parent<=h->size; parent = child)
		{
			child = 2*parent;  //先指向左儿子
			if( (2*parent+1) <= h->size && h->data[child] < h->data[child+1] )
			{
				child++;  //把最大的儿子的位置赋值给child
			}

			if( temp >= h->data[child] )  //temp一直悬在空中，并未赋值给谁，一直拿来作比较
			{
				break;
			}
			else
			{
				h->data[parent] = h->data[child];
			}
		}
		h->data[parent] = temp;
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