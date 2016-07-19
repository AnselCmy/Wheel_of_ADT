
# BinaryTree
***
## Struct
```c
typedef struct TreeNode 
{
    ElementType data;
    struct TreeNode* left;
    struct TreeNode* right;
}SearchTree;
```

## Function
```c
SearchTree* CreatRoot(ElementType num)
SearchTree* Insert(ElementType num, SearchTree* BST)
SearchTree* Find(ElementType num, SearchTree* BST)
SearchTree* FindIter(ElementType num, SearchTree* BST)
SearchTree* FindMin(SearchTree* BST)
SearchTree* FindMax(SearchTree* BST)
SearchTree* Delete(ElementType num, SearchTree* BST)
int GetHeight(SearchTree *BST)
int GetNodeNum(SearchTree *BST)
int GetLeafNum(SearchTree *BST)
void GetLeafNum2(SearchTree *BST, int &num)
int GetNodeLevel(ElementType num, SearchTree* BST)
void PrintRouteToLeaf(SearchTree* BST, Stack* s)
void PrintLeaf(SearchTree *BST)
void PreTrav(SearchTree *BST)
void InTrav(SearchTree *BST)
void PostTrav(SearchTree *BST)
```

- `SearchTree* CreatRoot(ElementType num)`  
    + 建立根节点，传入的参数是根节点的data

- `SearchTree* Insert(ElementType num, SearchTree* BST)`
    + 按照搜索二叉树的原则插入元素，采用递归的方法，当发现BST变成了NULL，说明不能继续向下递归了这时就申请新的内存给这个数据，为了要连在上一个节点后面，这里函数的返回值是该节点的指针，在上一级的递归里面用BST->left或者BST->right来连接这个节点，所以这里的返回值特别重要

- `SearchTree* Find(ElementType num, SearchTree* BST)`
    + 采用递归的方法按照搜索二叉树的规则递归，是尾递归

-  `SearchTree* FindIter(ElementType num, SearchTree* BST)`
    + 把上一个函数的尾递归改成了迭代循环的方法

- `SearchTree* FindMin(SearchTree* BST)`  
    + 一直想左边走，直到BST为NULL，说明走到头，就是最小的节点

- `SearchTree* Delete(ElementType num, SearchTree* BST)`
    + 分为几种情况，如果要删除的节点只有一个子节点，则可以直接删除那个节点，    