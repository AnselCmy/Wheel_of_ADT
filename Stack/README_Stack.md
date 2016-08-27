# Stack

## Struct
```c
typedef struct StackNode
{
        stackET data;
        struct StackNode* next;
}Stack;
```

## Function
```c
Stack* CreatStack()
int IsEmpty(Stack* s)
void Push(stackET num, Stack* s)
stackET Pop(Stack* s)
stackET Top(Stack* s)
void PrintStack(Stack* s)
void PrintStackInverted(Stack* s)
void MakeEmpty(Stack* s)
```
***

- `Stack* CreatStack()`
    + 需要注意的是这里的堆栈第一个节点并没有保存data，只是一个空的头节点  

- `void Push(stackET num, Stack* s)`
    + push的时候把新的节点插入在了头节点后面的位置

- `stackET Pop(Stack* s)`  
    + pop弹出栈顶的时候，注意需要保存栈顶元素指针为temp和temp->data，方便之后free和return出值
 
- `void PrintStackInverted(Stack* s)`  
    * 先声明一个固定为100长度的数组用来保存data，因为stack中只有一个指向后面的指针，所以到了后面就找不到前面的元素

## Attention
-  在`PrintStack()`和`PrintStackInverted()`里面由于有格式化输出，修改stackET的时候需要修改输出