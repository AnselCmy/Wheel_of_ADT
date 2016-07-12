#include <stdio.h>
#include <stdlib.h>
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
	else
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

void PreTrav(SearchTree *BST)
{
	if(BST)
	{
		printf("%d ", BST->data);
		PreTrav(BST->left);
		PreTrav(BST->right);
	}
}

int main(int argc, char const *argv[])
{
	SearchTree* BST = CreatRoot(10);
	Insert(4, BST);
	Insert(12,BST);
	Insert(1, BST);
	Insert(11,BST);
	Insert(15,BST);
	//PreTrav(BST);
	//printf("%d\n", Find(11, BST)->data);
	Delete(15, BST);
	PreTrav(BST);	
	return 0;
}