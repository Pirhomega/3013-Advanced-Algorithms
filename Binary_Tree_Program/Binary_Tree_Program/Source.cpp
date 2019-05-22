/*
Corbin Matamoros
CMPS 3013 - Prof Simpson
Program 4 - Creating a Binary Tree
2/14/2019
This program creates a class object for a binary tree. Class methods
will add nodes to the tree, delete individual nodes, print the tree
contents in order, destroy the entire tree, 
*/

#include "BST.h"
#include <iostream>

using namespace std;

int main()
{
	BST Binary_Tree;
	int numCases, insertVal, delVal, rankVal, lowRange, highRange;

	////inserting 1 - 1000 into the binary tree
	////creates a flat tree
	//for (int i = 1; i <= 20; i++)
	//{
	//	Binary_Tree.insertNode(i);
	//}

	//inserting and deleting values into and from the binary tree
	cin >> numCases;
	for (int i = 0; i < numCases; i++)
	{
		cin >> insertVal;// >> delVal
		Binary_Tree.insertNode(insertVal);
		//Binary_Tree.deleteNode(delVal);
	}
	cout << '\n';

	Binary_Tree.levelOrderTraversal();
	//Binary_Tree.internalPathLength();
	Binary_Tree.rightRotation();
	Binary_Tree.levelOrderTraversal();

	////finding the rank for certain values
	//cin >> numCases;
	//for (int i = 0; i < numCases; i++)
	//{
	//	cin >> rankVal;
	//	cout << "The rank of " << rankVal << " is " << Binary_Tree.rank(rankVal) << '\n';
	//}
	//cout << '\n';

	////finding the range of values between two certain numbers
	//cin >> numCases;
	//for (int i = 0; i < numCases; i++)
	//{
	//	cin >> lowRange >> highRange;
	//	cout << "There are " << Binary_Tree.range(lowRange, highRange) 
	//		<< " values in between " << lowRange << " and " << highRange 
	//		<< '\n';
	//}
	//cout << endl;
	return 0;
}