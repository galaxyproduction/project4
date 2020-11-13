// Test driver
#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.cpp"
#include <iostream>

using namespace std;

TreeType<int> makeTree(int arr[], int size);
void makeTreeHelper(int arr[], int start, int end, TreeType<int> &tree);

int main()
{
	string command; // operation to be executed

	int item;
	TreeType<int> tree;
	bool found;
	ifstream inFile;
	inFile.open("input.txt");
	inFile >> command;

	cout << "This project is done by Hunter Wilkins." << endl;

	while (command != "Quit")
	{

		//1
		if (command == "PutItem")
		{
			//cout << "Enter Item to be inserted in the tree  ";
			inFile >> item;
			tree.PutItem(item);
			cout << item;
			cout << " is inserted" << endl;
		}
		//2
		else if (command == "DeleteItem")
		{
			inFile >> item;
			tree.DeleteItem(item);
		}
		//3
		else if (command == "GetItem")
		{
			inFile >> item;
			item = tree.GetItem(item, found);
			if (found)
				cout << item << " found in tree." << endl;
			else
				cout << item << " is not in tree." << endl;
		}
		//4
		else if (command == "GetLength")
		{
			cout << "Calling GetLength\n";
			cout << "Number of nodes is " << tree.GetLength() << endl;
		}
		//5
		else if (command == "IsEmpty")
			if (tree.IsEmpty())
				cout << "Tree is empty." << endl;
			else
				cout << "Tree is not empty." << endl;
		//6
		else if (command == "IsFull")
			if (tree.IsFull())
				cout << "Tree is full." << endl;
			else
				cout << "Tree is not full." << endl;
		//7
		else if (command == "Print")
		{
			cout << "Printing the tree...InOrder Traversal\n";
			tree.Print();
			cout << endl;
		}
		//8
		else if (command == "PreOrderPrint")
		{
			cout << "PreOrder Print:\n";
			tree.PreOrderPrint();
		}
		//9
		else if (command == "PostOrderPrint")
		{
			cout << "PostOrder Print:\n";
			tree.PostOrderPrint();
		}
		//10
		else if (command == "LevelOrderPrint")
		{
			cout << "LevelOrder Print:\n";
			tree.LevelOrderPrint();
		}
		//11
		else if (command == "MakeEmpty")
		{
			tree.MakeEmpty();
			std::cout << "Tree has been made empty." << endl;
		}

		//12
		else if (command == "GetSuccessor")
		{
			inFile >> item;
			cout << "Logical successor of " << item << " is: ";
			try
			{
				int successor = tree.GetSuccessor(item);
				if (successor != NULL)
				{
					cout << successor << endl;
				}
				else
				{
					cout << "NULL\n-99999" << endl;
				}
			}
			catch (ItemNotFound inf)
			{
				cout << "Item was not in the tree\n-99999" << endl;
			}
		}
		//13
		else if (command == "PrintAncestorsOf")
		{
			inFile >> item;
			cout << "testing Ancestors of " << item << endl;
			tree.PrintAncestors(item);
		}
		//14
		else if (command == "MirrorImage")
		{
			cout << "Testing Mirror Image\n";
			tree.MakeEmpty();
			tree.PutItem(10);
			tree.PutItem(13);
			tree.PutItem(5);
			tree.PutItem(4);
			tree.PutItem(7);
			tree.PutItem(12);
			tree.PutItem(20);
			cout << "\nOriginal Tree before mirroring:\n";
			tree.LevelOrderPrint();
			TreeType<int> mirrorOftree;
			tree.mirrorImage(mirrorOftree);
			cout << "Original Tree After Mirroring:\n";
			tree.LevelOrderPrint();
			cout << "Mirror Image:\n";
			mirrorOftree.LevelOrderPrint();
		}

		//15
		else if (command == "MakeTree")
		{

			int array[100], length;
			inFile >> length;
			for (int i = 0; i < length; i++)
				inFile >> array[i];
			tree = makeTree(array, length);
		}
		else
			cout << "Undefined Command!" << command << endl;
		inFile >> command;
	}
	cout << "Testing completed." << endl;

	return 0;
}

// Helper recursive function for makeTree
// The balanced tree will be contained within the tree variable
// Start and end are the indexes of a subset of arr
void makeTreeHelper(int arr[], int start, int end, TreeType<int> &tree)
{
	if (end - start < 0)
		return;

	// Middle index of the subset
	int middle = (end + start) / 2;

	// Puts middle item into the tree
	tree.PutItem(arr[middle]);

	// Recursivly divides arr into two subsets and adds them to the tree
	makeTreeHelper(arr, start, middle - 1, tree);
	makeTreeHelper(arr, middle + 1, end, tree);
}

// Creates a balanced BST from a sorted array
TreeType<int> makeTree(int arr[], int size)
{
	TreeType<int> balancedTree;
	makeTreeHelper(arr, 0, size - 1, balancedTree);

	return balancedTree;
}