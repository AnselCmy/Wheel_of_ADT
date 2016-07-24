#include <stdio.h>
#define ElementType int

void PercDownOrder(ElementType *a, int start, int end) //start and end are the indexs, not the length
{
	int child;
	int parent = start;
	ElementType temp = a[start];
	for(parent; 2*parent+1 <= end; parent=child)
	{
		child = 2*parent+1;
		if(2*parent+1 != end && a[child+1] > a[child])
		{
			child++;
		}

		if(temp < a[child])
		{
			a[parent] = a[child];
		}
		else
		{
			break;
		}
	}
	a[parent] = temp;
}

void PercDownReverseOrder(ElementType *a, int start, int end) //start and end are the indexs, not the length
{
	int child;
	int parent = start;
	ElementType temp = a[start];
	for(parent; 2*parent+1 <= end; parent=child)
	{
		child = 2*parent+1;
		if(2*parent+1 != end && a[child+1] < a[child])
		{
			child++;
		}

		if(temp > a[child])
		{
			a[parent] = a[child];
		}
		else
		{
			break;
		}
	}
	a[parent] = temp;
}

void HeapSortOrder(ElementType *a, int len)
{
	int i;
	ElementType temp;
	for(i=(len/2)-1; i>=0; i--)
	{
		PercDownOrder(a, i, len-1); //attention the second argu is the index of the last element  
	}

	for(i=len-1; i>0; i--)
	{
		temp = a[i]; //swap
		a[i] = a[0];
		a[0] = temp;
		PercDownOrder(a, 0, i-1);
	}
}

void HeapSortReverseOrder(ElementType *a, int len)
{
	int i;
	ElementType temp;
	for(i=(len/2)-1; i>=0; i--)
	{
		PercDownReverseOrder(a, i, len-1); //attention the second argu is the index of the last element  
	}

	for(i=len-1; i>0; i--)
	{
		temp = a[i]; //swap
		a[i] = a[0];
		a[0] = temp;
		PercDownReverseOrder(a, 0, i-1);
	}
}
