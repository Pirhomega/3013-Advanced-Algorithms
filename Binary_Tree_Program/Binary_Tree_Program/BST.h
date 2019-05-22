#pragma once
class BST
{
private:
	struct Node
	{
		unsigned int value;
		unsigned int size;//number of nodes from a node's own subtree
		Node* right;//points to a node's right subtree
		Node* left;//points to a node's left subtree

		//overloaded constructor
		Node(unsigned int val)
		{
			value = val;
			size = 1;
			right = nullptr;
			left = nullptr;
		}
	};
	Node* root;//points to the root of the binary tree
	Node* current;//points to a node under inspection
	Node* previous;//points to current pointer's preceeding node
public:
	BST();//default constructor
	~BST();//destructor
	
	BST(const BST&);// copy constructor
	//BST(BST&&);// rvalue reference constructor(move)

	BST& operator=(const BST&);

	void insertNode(unsigned int);
	void deleteNode(unsigned int);
	void printInOrder();
	int range(int, int);
	int Sum();
	int rank(int);//O(height of the tree)
	void binarySearch(int, int);//O(log(n))
	void copyTree(BST::Node*&, const BST::Node*);//O(n)

	void levelOrderTraversal();
	void internalPathLength();
	void rightRotation();
private:
	void insertNodePriv(Node*&);//O(n)
	void deleteNodePriv();//O(n)
	void printInOrder(Node*);//O(n)
	void destroyTree(Node*&);//O(n)
	int recursiveSum(Node*, int);//O(n)
	int rangeAUX(int, int, Node*&, int);//O(height of the tree)

	int internalPathLengthPriv(Node*, int);
};

