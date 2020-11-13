#include <iostream>
// #include <algorithm>
using namespace std;
#include "TreeType.h"

template<class T>
void CopyTree(TreeNode<T> *&copy, const TreeNode<T> *originalTree);
template<class T>
int CountNodes(TreeNode<T> *tree);
template<class T>
void DeleteNode(TreeNode<T> *&tree);
template<class T>
void Delete(TreeNode<T> *&tree, T item);
template<class T>
void Destroy(TreeNode<T> *&tree);
template<class T>
TreeNode<T> *findItem(TreeNode<T> *tree, T value);
template<class T>
void GetPredecessor(TreeNode<T> *tree, T &data);
template<class T>
int height(const TreeNode<T> *tree);
template<class T>
void inOrderTraverse(TreeNode<T> *tree);
template<class T>
void Insert(TreeNode<T> *&tree, T item);
template<class T>
void mirror(TreeNode<T> *&copy, const TreeNode<T> *originalTree);
template<class T>
void PrintAncestorsHelper(const TreeNode<T> *tree, T value);
template<class T>
void postOrderPrintHelper(const TreeNode<T> *tree);
int pow(int a, int b);
template<class T>
void preOrderPrintHelper(const TreeNode<T> *tree);
template<class T>
TreeNode<T>* ptrToSuccessorHelper(TreeNode<T>*& tree);
template<class T>
void Retrieve(TreeNode<T> *tree, T &item, bool &found);

template<class T>
struct TreeNode
{
  T info;
  TreeNode *left;
  TreeNode *right;
};

template<class T>
TreeType<T>::TreeType()
{
  root = NULL;
}

template<class T>
TreeType<T>::TreeType(const TreeType &originalTree) 
{
  CopyTree(root, originalTree.root);
}

template<class T>
TreeType<T>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

template<class T>
bool TreeType<T>::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
  TreeNode<T> *location;
  try
  {
    location = new TreeNode<T>;
    delete location;
    return false;
  }
  catch (std::bad_alloc exception)
  {
    return true;
  }
}

template<class T>
bool TreeType<T>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

template<class T>
int TreeType<T>::GetLength() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
  return CountNodes(root);
}

template<class T>
int CountNodes(TreeNode<T> *tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template<class T>
T TreeType<T>::GetItem(T item, bool &found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

// helper function for GetItem
template<class T>
void Retrieve(TreeNode<T> *tree, T &item, bool &found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false; // item is not found.
  else if (item < tree->info)
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found); // Search right subtree.
  else
  {
    item = tree->info; // item is found.
    found = true;
  }
}

template<class T>
void TreeType<T>::PutItem(T item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
template<class T>
void Insert(TreeNode<T> *&tree, T item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode<T>;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item); // Insert in left subtree.
  else
    Insert(tree->right, item); // Insert in right subtree.
}

template<class T>
void TreeType<T>::DeleteItem(T item)
// Calls recursive function Delete to delete item from tree.
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << " is not in tree\n";
}

template<class T>
void Delete(TreeNode<T> *&tree, T item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item); // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item); // Look in right subtree.
  else
    DeleteNode(tree); // Node found; call DeleteNode.
}

template<class T>
void DeleteNode(TreeNode<T> *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
  T data;
  TreeNode<T> *tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    TreeNode<T>* succesor = ptrToSuccessorHelper(tree->right);
    tree->info = succesor->info;
    Delete(tree->right, succesor->info); // Delete predecessor node.
  }
}

//Helper function for DeleteNode
template<class T>
void GetPredecessor(TreeNode<T> *tree, T &data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

// Helper function for Print
template<class T>
void inOrderTraverse(TreeNode<T> *tree)
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left); // Print left subtree.
    cout << tree->info << "  ";
    inOrderTraverse(tree->right); // Print right subtree.
  }
}

template<class T>
void TreeType<T>::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}

// Recursive helper for preOrderPrint
template<class T>
void preOrderPrintHelper(const TreeNode<T> *tree)
{
  if (tree == NULL)
    return;
  cout << tree->info << ' ';
  preOrderPrintHelper(tree->left);
  preOrderPrintHelper(tree->right);
}

// Prints the elements in the tree in pre-order order seperated by spaces
template<class T>
void TreeType<T>::PreOrderPrint() const
{
  preOrderPrintHelper(root);
  cout << '\n';
}

// Recursive helper for postOrderPrint
template<class T>
void postOrderPrintHelper(const TreeNode<T> *tree)
{
  if (tree == NULL)
    return;
  postOrderPrintHelper(tree->left);
  postOrderPrintHelper(tree->right);
  cout << tree->info << ' ';
}

// Prints the elements in the tree in post-order order seperated by spaces
template<class T>
void TreeType<T>::PostOrderPrint() const
{
  postOrderPrintHelper(root);
  cout << '\n';
}

// Recursive helper for PrintAncestors
// Walks the tree printing the ancestors until we find value
template<class T>
void PrintAncestorsHelper(const TreeNode<T> *tree, T value)
{
  if (tree->info == value)
  {
    return;
  }

  cout << tree->info << ' ';

  if (tree->info > value)
  {
    PrintAncestorsHelper(tree->left, value);
  }
  else
  {
    PrintAncestorsHelper(tree->right, value);
  }
}

// Prints the ancestors of value from parent->grandparent->...
template<class T>
void TreeType<T>::PrintAncestors(T value)
{
  // Checks if the root is the value we are looking for
  if (root->info == value)
    cout << value << " is the root value, No ancestor" << endl;

  // Checks if the item is in the tree
  bool hasItem = true;
  GetItem(value, hasItem);
  if (hasItem)
  {
    PrintAncestorsHelper(root, value);
    cout << endl;
  }
  else
  {
    cout << value << " is not in the tree" << endl;
  }
}

template<class T>
TreeNode<T>* ptrToSuccessorHelper(TreeNode<T>*& tree) {
  if (tree == NULL)
    return NULL;

  if (tree->left == NULL)
    return tree;

  return ptrToSuccessorHelper(tree->left);
}

template<class T>
TreeNode<T> *TreeType<T>::ptrToSuccessor(TreeNode<T> *&tree) const
{
  return ptrToSuccessorHelper(tree);
}

// Recursive function to find the ptr of a node in the tree
// Walks the tree until value is found else throws error
template<class T>
TreeNode<T> *findItem(TreeNode<T> *tree, T value)
{
  if (tree == NULL)
    throw ItemNotFound();

  if (tree->info == value)
    return tree;

  if (tree->info > value)
    return findItem(tree->left, value);

  return findItem(tree->right, value);
}

template<class T>
T TreeType<T>::GetSuccessor(T value)
{
  TreeNode<T> *item = findItem(root, value);

  if (item->right == NULL)
    return NULL;

  TreeNode<T> *successor = ptrToSuccessor(item->right);
  return successor->info;
}

// helper function for Mirror Image
template<class T>
void mirror(TreeNode<T> *&copy, const TreeNode<T> *originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{
  if (originalTree == NULL)
    return;

  copy->info = originalTree->info;
  if (originalTree->right != NULL)
  {
    copy->left = new TreeNode<T>;
    mirror(copy->left, originalTree->right);
  }
  else
  {
    copy->left = NULL;
  }

  if (originalTree->left != NULL)
  {
    copy->right = new TreeNode<T>;
    mirror(copy->right, originalTree->left);
  }
  else
  {
    copy->right = NULL;
  }
}

// Prints the mirror of t
template<class T>
void TreeType<T>::mirrorImage(TreeType<T> &t)
{
  t.root = new TreeNode<T>;
  mirror(t.root, root);
}

template<class T>
void Destroy(TreeNode<T> *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

template<class T>
void TreeType<T>::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}

template<class T>
void CopyTree(TreeNode<T> *&copy, const TreeNode<T> *originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode<T>;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

template<class T>
void TreeType<T>::operator=(const TreeType<T> &originalTree)
// Calls recursive function CopyTree to copy originalTree
// into root.
{
  {
    if (&originalTree == this)
      return;      // Ignore assigning self to self
    Destroy(root); // Deallocate existing tree nodes
    CopyTree(root, originalTree.root);
  }
}

// Calculates the height of the tree
template<class T>
int height(const TreeNode<T> *tree)
{
  if (tree == NULL)
    return 0;

  return 1 + max(height(tree->left), height(tree->right));
}

// Returns a^b
int power(int a, int b)
{
  if (b == 0)
    return 1;
  if (b == 1)
    return a;

  return a * power(a, b - 1);
}

// Prints a 2d visulization of the tree
template<class T>
void TreeType<T>::LevelOrderPrint() const
{
  if (root == NULL)
    return;

  int treeHeight = height(root); // height of the tree
  int length = GetLength();      // Amount of nodes in the tree
  int nodesPrinted = 1;          // Amount of nodes printed including nulls '-'
  int nodes = 0;                 // Amount of nodes in the tree printed
  int level = 0;                 // Current level being printed
  QueType<TreeNode<T> *> queue;

  queue.Enqueue(root);

  TreeNode<T> *node;
  while (!queue.IsEmpty())
  {
    if (nodes >= length)
      break;
    
    // Addes correct left offset before the leftmost node in each level
    if (nodesPrinted == power(2, level))
    {
      for (int i = 0; i < treeHeight - level; i++)
      {
        cout << ' ';
      }
    }

    queue.Dequeue(node);

    // If node is not null, prints value then level order adds node's children to the queue
    // else prints '-' for all null nodes
    if (node != NULL)
    {
      cout << node->info << ' ';
      queue.Enqueue(node->left);
      queue.Enqueue(node->right);

      nodes++;
    }
    else
    {
      cout << '-' << ' ';
    }

    // if printed all nodes for current level
    if (nodesPrinted == power(2, level + 1) - 1)
    {
      cout << endl;

      // stops printing if rightmost node is last node
      if (nodes >= length)
        return;

      // adds correct left offset for node arrows
      for (int i = 0; i < treeHeight - level - 1; i++)
      {
        cout << ' ';
      }

      // draws arrows pointing to children
      for (int i = 0; i < level + 1; i++)
      {
        cout << "/ \\ ";
      }

      cout << endl;
      level++;
    }

    nodesPrinted++;
  }

  cout << endl;
}