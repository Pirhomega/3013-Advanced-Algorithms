#include "BST.h"
#include<iostream>
#include<queue>

//-----------------------------------------------------------
//Constructor Section

//default constructor for class
BST::BST()
{
	root = nullptr;
	current = root;
	previous = current;
}

//destructor which calls the destroyTree function
BST::~BST()
{
	current = root;
	destroyTree(current);
}

//copy constructor
BST::BST(const BST& A)
{
	if (A.root == nullptr)
		root = nullptr;
	else
		copyTree(root, A.root);
}

//assignment operator (B = A)
BST& BST::operator=(const BST& A)
{
	if (this->root != nullptr)
	{
		this->destroyTree(root);
		copyTree(root, A.root);
	}
	return (*this);
}

//-----------------------------------------------------------
//Insertion Section

//public function which calls the private function insertNodePriv
void BST::insertNode(unsigned int val)
{
	current = root;//reset the 'current' pointer
	Node* temp = new Node(val);//create a new node with 'val'
	if (root == nullptr)//if tree is empty
		root = temp;
	else
		insertNodePriv(temp);
}

//private function that inserts a node into the tree
//It uses recursion to find the right spot to place the new node
void BST::insertNodePriv(Node*& temp)
{
	if (temp->value < current->value)
	{
		current->size++;//increment the size of the node
		if (current->left == nullptr)//insert temp on left of current
			current->left = temp;
		else
		{
			current = current->left;//traverse down the node's left subtree
			insertNodePriv(temp);
		}
	}
	else//traverse down the node's right subtree
	{
		current->size++;
		if (current->right == nullptr)//insert temp on right of current
			current->right = temp;
		else
		{
			current = current->right;//traverse down the node's right subtree
			insertNodePriv(temp);
		}
	}
}

//-----------------------------------------------------------
//Deletion/Destroying Section

//public function that will call the private function to delete a single node
void BST::deleteNode(unsigned int val)
{
	current = root;//reset current
	previous = current;	//reset previous (in this program, previous is always
						//dependent on current, not root
	if (current->value == val)//if node to be deleted is the root of the tree
		deleteNodePriv();
	else if (val < current->value)//traverse the node's left subtree
	{
		current->size--;//decrease the size of the root (since we're deleting 
						//a node in the tree and 'binarySearch' doesn't 
						//perform this action)
		current = current->left;
		binarySearch(val, -1);//traverse the tree till 'current' points to node
								//to be deleted
		if (current == nullptr)//if node to be deleted doesn't exist in tree
		{
			std::cout << "Value not found in tree\n";
			current = root;
			previous = current;
			binarySearch(val, 1);
			return;
		}
		deleteNodePriv();
	}
	else//traverse the node's right subtree
	{
		current->size--;
		current = current->right;
		binarySearch(val, -1);
		if (current == nullptr)
		{
			std::cout << "Value not found in tree\n";
			current = root;
			previous = current;
			binarySearch(val, 1);
			return;
		}
		deleteNodePriv();
	}
}

//private function that will delete a specific node
void BST::deleteNodePriv()
{
	Node* temp;
	if (current == previous)//if node to be deleted is root
	{
		current = current->right;
		temp = root->left;
		delete root;
		root = current;//new root of tree to be node on right of old root
		if (temp != nullptr)
		{
			//traverse new root's left subtree for its bottom-most node
			while (current->left != nullptr)
			{
				current->size += temp->size;
				current = current->left;
			}
			current->size += temp->size;
			current->left = temp;//place old root's left subtree under new
								 //root's bottom-most node in its left subtree
		}
	}
	else
	{
		//runs if deleting a node with children on the left and right
		if (current->left != nullptr && current->right != nullptr)
		{
			//the following two conditions perform the same tree-modification
			//operations. The only difference is on previous's position with
			//respect to 'current'. If current is on previous's left, 
			//previous->right will re-point to current's right. If current is on
			//the right, then previous->left will point to current's right. 
			if (previous->left == current)
			{
				previous->left = current->right;
				temp = current;
				current = current->left;
				delete temp;
				temp = previous->left;
				while (temp->left != nullptr)
				{
					temp->size += current->size;
					temp = temp->left;
				}
				temp->size += current->size;
				temp->left = current;
			}
			else
			{
				previous->right = current->right;
				temp = current;
				current = current->left;
				delete temp;
				temp = previous->right;
				while (temp->left != nullptr)
				{
					temp->size += current->size;
					temp = temp->left;
				}
				temp->size += current->size;
				temp->left = current;
			}
		}
		//runs if node has children on the right but not the left
		else if (current->left == nullptr && current->right != nullptr)
		{
			//the previous->right == current condition covers any instance
			//of zigzagging in a tree, where nodes' children alternate between
			//left and right children (node1->right = node2; node2->left = node3;
			//node3->right = node4; node4->left = node5; etc.)
			if (previous->right == current && current->right != nullptr)
				previous->right = current->right;
			else//this runs if the node is within a zigzag
				previous->left = current->right;
			delete current;
		}
		//runs if node has children on the left but not the right
		//Runs the same way as the above else if. 
		else if (current->left != nullptr && current->right == nullptr)
		{
			if (previous->left == current && current->left != nullptr)
				previous->left = current->left;
			else
				previous->right = current->left;
			delete current;
		}
		//runs if the node is a leaf
		else
		{
			if (previous->left == current)
				previous->left = nullptr;
			else
				previous->right = nullptr;
			delete current;
		}
	}
}

//private function that destroys every node without losing nodes and creating
//a memory leak
void BST::destroyTree(Node*& current)
{
	if (current != nullptr)
	{
		printInOrder(current->left);
		printInOrder(current->right);
		delete current;
		current = nullptr;
	}
}

//-----------------------------------------------------------
//Printing Section

//public function that will call the private function to print the tree
//contents in order of lowest to highest
void BST::printInOrder()
{
	current = root;
	printInOrder(current);
	std::cout << '\n';
}

//private function that will print all elements in tree from lowest to highest
//Function is recursive
void BST::printInOrder(Node* current)
{
	if (current != nullptr)
	{
		printInOrder(current->left);
		std::cout << current->value << ' ';
		printInOrder(current->right);
	}
}

//-----------------------------------------------------------
//Calculations Section

//public function that calls private function to sum the tree node values
int BST::Sum()
{
	current = root;
	return recursiveSum(current, 0);
}

//private function that will sum all nodes' values in tree
int BST::recursiveSum(Node* current, int sum)
{
	if (current == nullptr)
		return sum;
	else
		return current->value + recursiveSum(current->left, sum) 
		+ recursiveSum(current->right, sum);
}

//public function that will determine the number of nodes
//less than a specific node (that has 'val'). Essentially, it traverses to the 
//desired NODE and gathers the size of the root of the NODE's left subtree
int BST::rank(int val)
{
	current = root;
	previous = current;
	binarySearch(val, 0);
	if (current == nullptr)
	{
		std::cout << "Value not found in tree\n";
		return 0;
	}
	if (current->left != nullptr)
		return (current->left->size + 1);
	else 
		return 1;
}

//public function that returns the values in the range from 'lower' to 'higher'
int BST::range(int lower, int higher)
{
	current = root;
	return rangeAUX(lower, higher, current, 0);
}

//private function to find the nodes with value between the range 'lower' and 'higher'
//almost almost ALMOST works! It's one off sometimes. 
int BST::rangeAUX(int lower, int higher, Node*& temp, int range)
{
	if (temp != nullptr)
	{
		if (temp->value > lower && temp->value < higher)
		{
			return 1 + rangeAUX(lower, higher, temp->left, range + 1) 
				+ rangeAUX(lower, higher, temp->right, range + 1);
		}
		else if (temp->value == lower && temp->right != nullptr)
		{
			return range + temp->right->size;
		}
		else if (temp->value == higher && temp->left != nullptr)
		{
			return range + temp->left->size;
		}
		else
			return rangeAUX(lower, higher, temp->left, range) 
			+ rangeAUX(lower, higher, temp->right, range);
	}
	else
		return 0;
}

//-----------------------------------------------------------
//Friend, non-member functions section

//public friend utility function
void BST::copyTree(BST::Node*& toRoot, const BST::Node* fromRoot)
{
	if (fromRoot == nullptr)
		toRoot = nullptr;
	else
	{
		Node* temp = new Node(fromRoot->value);
		copyTree(toRoot->left, fromRoot->left);
		copyTree(toRoot->right, fromRoot->right);
	}
}

//used to find a specific node that has value == val
//'val' is the value the algorithm searches for
//'sizeAdj' will vary between -1 and  0. The binarySearch member
//traverses the entire tree and updates the size of each node through which
//it passes (decrements nodes when searching for a node to delete - when called
//from deleteNode() - or does nothing when just searching through the tree -
//when called from rank() ). 
void BST::binarySearch(int val, int sizeAdj)
{
	if (current != nullptr && val != current->value)
	{
		if (val < current->value)
		{
			current->size += sizeAdj;
			previous = current;
			current = current->left;
			binarySearch(val, sizeAdj);
		}
		else
		{
			current->size += sizeAdj;
			previous = current;
			current = current->right;
			binarySearch(val, sizeAdj);
		}
	}
}

void BST::levelOrderTraversal()
{
	Node* r = root;
	std::queue<Node*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		r = Q.front();
		Q.pop();
		if (r->left)
			Q.push(r->left);
		if (r->right)
			Q.push(r->right);
		std::cout << r->value << ' ';
	}
	std::cout << '\n';
}

void BST::internalPathLength()
{
	if (root != nullptr)
	{
		int depth = 0;
		std::cout << internalPathLengthPriv(current, depth);
	}
}


int BST::internalPathLengthPriv(Node* current, int depth)
{
	if (current == nullptr)
		return 0;
	else
		return depth + internalPathLengthPriv(current->left, depth + 1) + internalPathLengthPriv(current->right, depth + 1);
}

void BST::rightRotation()
{
	previous = root;
	current = root->left;
	Node* temp = current->left;
	current->left = temp->right;
	temp->right = current;
	current = temp;
	previous->left = temp;
}