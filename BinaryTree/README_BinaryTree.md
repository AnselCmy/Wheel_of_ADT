
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
SearchTree* FindMinIter(SearchTree* BST)
SearchTree* FindMax(SearchTree* BST)
SearchTree* FindMaxIter(SearchTree* BST)
SearchTree* Delete(ElementType num, SearchTree* BST)
int GetHeight(SearchTree *BST)
int GetNodeNum(SearchTree *BST)
int GetLeafNum(SearchTree *BST)
void GetLeafNum2(SearchTree *BST, int &num)
void GetNodeLevel(ElementType num, SearchTree* BST, int &level)
int GetNodeLevelIter(ElementType num, SearchTree* BST)
void PrintRouteToLeaf(SearchTree* BST, Stack* s)
void PrintLeaf(SearchTree *BST)
void PreTrav(SearchTree *BST)
void InTrav(SearchTree *BST)
void PostTrav(SearchTree *BST)
```

- `SearchTree* CreatRoot(ElementType num)`  
    + 建立根节点，传入的参数是根节点的data

- `SearchTree* Insert(ElementType num, SearchTree* BST)`
    + 按照搜索二叉树的原则插入元素，采用递归的方法，当发现BST变成了NULL，说明不能继续向下递归了这时就申请新的内存给这个数据（所以第一个if里面的语句很重要），为了要连在上一个节点后面，这里函数的返回值是该节点的指针，在上一级的递归里面用BST->left或者BST->right来连接这个节点，所以这里的返回值特别重要

- `SearchTree* Find(ElementType num, SearchTree* BST)`
    + 采用递归的方法按照搜索二叉树的规则递归，是尾递归

-  `SearchTree* FindIter(ElementType num, SearchTree* BST)`
    + 把上一个函数的尾递归改成了迭代循环的方法

- `SearchTree* FindMin(SearchTree* BST)`  
    + 一直向左边走，直到BST为NULL，说明走到头，就是最小的节点

- `SearchTree* FindMaxIter(SearchTree* BST)`
    + FindMax是是用的尾递归，所以可以改成循环的方式来找到最大的data

- `SearchTree* Delete(ElementType num, SearchTree* BST)`
    + 分为几种情况，如果要删除的节点只有一个子节点，则可以直接删除那个节点，

- `int GetHeight(SearchTree *BST)`    
    + 采用递归的思想，一棵树的高度是指左子树和右子树中最大的，当一个节点没有左子树和右子树的时候，则高度为1。递归的递进动作是在GetHeight(BST->left)里面完成的。

- `int GetLeafNum(SearchTree *BST)`
    + GetHeight,GetNodeNum,GetLeafNum都是用的一种递归的方法，一层一层向下递归，直到到最后一层可以确定一个数值，比如自己是NULL的时候，则高度是0，此时节点数也是0。
    + 注意到GetHeight,GetNodeNum 与 GetLeafNum之间还是有一点差别，前者的两个每次return都会加一，而后者不会

- `void GetNodeLevel(ElementType num, SearchTree* BST, int &level)`
    + 这里加入了一个引用，因为在递归里面，如果把记录level的变量放在函数里面声明的话，会有变量范围的问题，所以声明在外面，用来记录。

- `int GetNodeLevelIter(ElementType num, SearchTree* BST)`
    + 用迭代的方法，循环到参数所指定的数值的时候。


 