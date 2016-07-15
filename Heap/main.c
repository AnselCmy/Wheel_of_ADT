#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
int main(int argc, char const *argv[])
{
	int a[] = {23,45,78,12,43,57,98,64,24,88,24,97};
	int len = sizeof(a)/sizeof(a[0]);
	MaxHeap* mh = CreatMaxHeapWithArray(a, len);
	PrintHeap(mh, mh->size);
	DeleteMax(mh);
	PrintHeap(mh, mh->size);
	Insert(68, mh);
	PrintHeap(mh, mh->size);
	return 0;
}