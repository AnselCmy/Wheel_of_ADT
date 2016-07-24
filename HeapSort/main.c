#include <stdio.h>
#include "HeapSort.h"

int main(int argc, char const *argv[])
{
	int a[] = {12, 34, 56, 11, 22, 10, 8, 45};
	int len = sizeof(a)/sizeof(a[0]);
	HeapSortOrder(a, len);
	int i;
	for(i=0; i<len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	HeapSortReverseOrder(a, len);
	for(i=0; i<len; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}