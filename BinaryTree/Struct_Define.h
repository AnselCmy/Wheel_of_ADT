#define stackET SearchTree*
#define ElementType int

typedef struct TreeNode 
{
    ElementType data;
    struct TreeNode* left;
    struct TreeNode* right;
}SearchTree;

typedef struct StackNode
{
    stackET data;
    struct StackNode* next;
}Stack;