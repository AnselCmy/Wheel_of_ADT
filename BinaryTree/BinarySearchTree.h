#include <stdio.h>
#include <stdlib.h>
#include "BST_stack.h"
#define ElementType int

typedef struct TreeNode 
{
	ElementType data;
	struct TreeNode* left;
	struct TreeNode* right;
}SearchTree;

SearchTree* CreatRoot(ElementType num)
{
	SearchTree* BST = (SearchTree*)malloc(sizeof(SearchTree));
	BST->data = num;
	BST->right = BST->left = NULL;
}

SearchTree* Insert(ElementType num, SearchTree* BST)
{
	if(BST == NULL)  
	{
		BST = (SearchTree*)malloc(sizeof(SearchTree));
		BST->data = num;
		BST->left = BST->right = NULL;
	}
	else
	{
		if(num > BST->data)
		{
			BST->right = Insert(num, BST->right);
		}
		else if(num < BST->data)
		{
			BST->left = Insert(num, BST->left);
		}
	}
	return BST;
}

SearchTree* Find(ElementType num, SearchTree* BST)
{
	if(BST == NULL)
	{
		return NULL;
	}
	else
	{
		if(num > BST->data)
		{
			return Find(num, BST->right);
		}
		else if(num < BST->data)
		{
			return Find(num, BST->left);
		}
		else if(num == BST->data)
		{
			return BST;
		}
	}
}

SearchTree* FindIter(ElementType num, SearchTree* BST)
{
	while(BST)
	{
		if(num > BST->data)
		{
			BST = BST->right;
		}
		else if(num < BST->data)
		{
			BST = BST->left;
		}
		else if(num == BST->data)
		{
			return BST;
		}
	}
	return NULL;
}

SearchTree* FindMin(SearchTree* BST)
{
	if(BST == NULL)
	{
		return NULL;
	}
	else
	{
		if(BST->left != NULL)
		{
			return FindMin(BST->left);
		}
		else
		{
			return BST;
		}
	}
}

SearchTree* FindMinIter(SearchTree* BST)
{
	if(!BST)
	{
		return NULL;
	}
	else
	{
		while(BST->left != NULL)
		{
			BST = BST->left;
		}
		return BST;
	}
}

SearchTree* FindMax(SearchTree* BST)
{
	if(BST == NULL)
	{
		return NULL;
	}
	else
	{
		if(BST->right != NULL)
		{
			return FindMax(BST->right);
		}
		else
		{
			return BST;
		}
	}
}

SearchTree* FindMaxIter(SearchTree* BST)
{
	if(!BST)
	{
		return NULL;
	}
	else
	{
		while(BST->right != NULL)
		{
			BST = BST->right;
		}
		return BST;
	}
}

SearchTree* Delete(ElementType num, SearchTree* BST)
{
	if(BST == NULL)
	{
		printf("no such node!");
	}
	else if(num < BST->data)
	{
		BST->left = Delete(num, BST->left);
	}
	else if(num > BST->data)
	{
		BST->right = Delete(num, BST->right);
	}
	else if(num == BST->data)
	{
		if(BST->left != NULL && BST->right != NULL)
		{
			BST->data = FindMin(BST->right)->data;
			BST->right = Delete(BST->data, BST->right);
		}
		else 
		{
			SearchTree* temp = BST;
			if(BST->left == NULL)
			{
				BST = BST->right;
			}
			else if(BST->right == NULL)
			{
				BST = BST->left;
			}
			free(temp);
		}
	}
	return BST;
}

int GetHeight(SearchTree *BST)
{
	int leftHeight = 0, rightHeight = 0;
	if(BST == NULL)
	{
		return 0;
	}
	else 
	{
		leftHeight = GetHeight(BST->left);
		rightHeight = GetHeight(BST->right);
		return (leftHeight>rightHeight ? leftHeight : rightHeight) + 1;
	}
}

int GetNodeNum(SearchTree *BST)
{
	int leftNum = 0, rightNum = 0;
	if(BST == NULL)
	{
		return 0;
	}
	else 
	{
		leftNum = GetNodeNum(BST->left);
		rightNum = GetNodeNum(BST->right);
		return (leftNum + rightNum) + 1;
	}
}

int GetLeafNum(SearchTree *BST)
{
	int leftLeaf = 0, rightLeaf = 0;
	if(BST)
	{
		if(BST->right == NULL && BST->left == NULL)
		{
			return 1;
		}
		else
		{
			leftLeaf = GetLeafNum(BST->left);
			rightLeaf = GetLeafNum(BST->right);
			return leftLeaf + rightLeaf;
		}
	}
	return 0;
}

void GetLeafNum2(SearchTree *BST, int &num)
{
	if(BST)
	{
		if( !BST->right && !BST->left )
			num++;
		GetLeafNum2(BST->left,  num);
		GetLeafNum2(BST->right,  num);
	}
}

int GetNodeLevel(ElementType num, SearchTree* BST)
{
	int level = 1;
	while(BST)
	{
		if(num > BST->data)
		{
			BST = BST->right;
			level++;
		}
		else if(num < BST->data)
		{
			BST = BST->left;
			level++;
		}
		else if(num == BST->data)
		{
			return level;
		}
	}
	return 0;
}

void PrintRouteToLeaf(SearchTree* BST, Stack* s)
{
	if(BST)  //***importan*** if some nodes only has one child
	{
		if( !BST->left && !BST->right)
		{
			Stack *temp = s->next;
			int a[100];
			int i=0;
			while(temp != NULL)
			{
				a[i] = temp->data->data;
				temp = temp->next;
				i++;
			}
			i--;
			while(i >= 0)
			{
				printf("%d ", a[i]);
				i--;
			}
			printf("%d\n", BST->data);
		}
		else
		{
			Push(BST, s);
			PrintRouteToLeaf(BST->left, s);
			PrintRouteToLeaf(BST->right, s);
			//back to last level, so pop.
			Pop(s);
		}
	}	
}

void PrintLeaf(SearchTree *BST)
{
	if(BST)
	{
		if(!BST->left && !BST->right)
		{
			printf("%d ", BST->data);
		}
		PrintLeaf(BST->left);
		PrintLeaf(BST->right);
	}	
}

void PreTrav(SearchTree *BST)
{
	if(BST)
	{
		printf("%d ", BST->data);
		PreTrav(BST->left);
		PreTrav(BST->right);
	}
}

void InTrav(SearchTree *BST)
{
	if(BST)
	{
		InTrav(BST->left);
		printf("%d ", BST->data);
		InTrav(BST->right);
	}
}

void PostTrav(SearchTree *BST)
{
	if(BST)
	{
		PostTrav(BST->left);
		PostTrav(BST->right);
		printf("%d ", BST->data);
	}
}