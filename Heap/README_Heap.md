# Heap

## Struct
```c
typedef struct  Heap
{
    ElementType *data;
    int size;
    int capacity;
} MaxHeap;
```

## Function
```c
MaxHeap* CreatMaxHeap(int c)
void PercDown(ElementType a[], int start, int end)
MaxHeap* CreatMaxHeapWithArray(ElementType* num, int len) 
int IsFull(MaxHeap* h)
int IsEmpty(MaxHeap* h)
void Insert(ElementType num, MaxHeap* h)
ElementType DeleteMax(MaxHeap* h)
void PrintHeap(MaxHeap* h, int len)
```

***

- `MaxHeap* CreatMaxHeap(int c)`  
    + 以c作为capacity建堆，不仅需要对堆申请内存，还要对堆里面的data数组申请内存，并且设置[0]位置为哨兵

- `void PercDown(ElementType a[], int start, int end)`
    + 进行下滤操作的函数，简化了creat和delete函数，这两个函数就是不同方式地调用了这个下滤的函数

- `MaxHeap* CreatMaxHeapWithArray(ElementType* num, int len)`  
    + 传入数组和长度建堆，建堆的方法并不是一个一个Insert，是先全部放到data数组里面，再开始从最右下角的最小的堆开始使其符合堆的要求，方法类似于`Delete()`，第一个循环是从下到上移动parent，每到一个parent就相当于一次Delete()

- `void Insert(ElementType num, MaxHeap* h)` 
    + 先把新的节点放在堆的最后一个位置，然后再一点点将节点向移动，类似于`Delete()`，当发现所在的堆不符合，则将[i/2]的值赋给[i]，并不需要对调两个的值，一直只需要拿原本的那个定值num来比较，相当于i一直悬空

- `ElementType DeleteMax(MaxHeap* h)`  
    + 可以返回删除的元素的值，先把堆里面的最后一个元素覆盖根节点的元素，再进行一层层的向下过滤，直到符合堆的要求，再赋值