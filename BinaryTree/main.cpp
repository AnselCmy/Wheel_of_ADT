#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

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
	//Delete(15, BST);
	//PreTrav(BST);
	//printf("\n");	
	printf("Height: %d\n", GetHeight(BST) );
	
	printf("NodeNum: %d\n", GetNodeNum(BST) );
	
	printf("leafNum: %d\n", GetLeafNum(BST) );
	
	int leafNum = 0;
	GetLeafNum2(BST, leafNum);
	printf("leafNum: %d\n", leafNum);  
	
	printf("level of 1: %d\n", GetNodeLevel(1, BST) );
	printf("leaf: \n");
	PrintLeaf(BST);
	printf("\n");

	printf("route to leaf: \n");
	Stack *s = CreatStack();
	PrintRouteToLeaf(BST, s);
	
	
	return 0;
}