#include <iostream>
#include <algorithm>
using namespace std;
#include "TreeType.h"

void CopyTree(TreeNode *&copy, const TreeNode *originalTree);
int CountNodes(TreeNode *tree);
void DeleteNode(TreeNode *&tree);
void Delete(TreeNode *&tree, ItemType item);
void Destroy(TreeNode *&tree);
TreeNode *findItem(TreeNode *tree, int value);
void GetPredecessor(TreeNode *tree, ItemType &data);
int height(const TreeNode *tree);
void inOrderTraverse(TreeNode *tree);
void Insert(TreeNode *&tree, ItemType item);
void mirror(TreeNode *&copy, const TreeNode *originalTree);
void PrintAncestorsHelper(const TreeNode *tree, int value);
void postOrderPrintHelper(const TreeNode *tree);
int pow(int a, int b);
void preOrderPrintHelper(const TreeNode *tree);
void Retrieve(TreeNode *tree, ItemType &item, bool &found);

struct TreeNode
{
  ItemType info;
  TreeNode *left;
  TreeNode *right;
};

TreeType::TreeType()
{
  root = NULL;
}

TreeType::TreeType(const TreeType &originalTree) {}

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

bool TreeType::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
  TreeNode *location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch (std::bad_alloc exception)
  {
    return true;
  }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
  return CountNodes(root);
}

int CountNodes(TreeNode *tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

ItemType TreeType::GetItem(ItemType item, bool &found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

// helper function for GetItem
void Retrieve(TreeNode *tree,
              ItemType &item, bool &found)
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

void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
void Insert(TreeNode *&tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item); // Insert in left subtree.
  else
    Insert(tree->right, item); // Insert in right subtree.
}

void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << " is not in tree\n";
}

void Delete(TreeNode *&tree, ItemType item)
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

void DeleteNode(TreeNode *&tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode *tempPtr;

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
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data); // Delete predecessor node.
  }
}

//Helper function for DeleteNode
void GetPredecessor(TreeNode *tree, ItemType &data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

// Helper function for Print
void inOrderTraverse(TreeNode *tree)
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    inOrderTraverse(tree->left); // Print left subtree.
    cout << tree->info << "  ";
    inOrderTraverse(tree->right); // Print right subtree.
  }
}

void TreeType::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}

// Recursive helper for preOrderPrint
void preOrderPrintHelper(const TreeNode *tree)
{
  if (tree == NULL)
    return;
  cout << tree->info << ' ';
  preOrderPrintHelper(tree->left);
  preOrderPrintHelper(tree->right);
}

// Prints the elements in the tree in pre-order order seperated by spaces
void TreeType::PreOrderPrint() const
{
  preOrderPrintHelper(root);
  cout << '\n';
}

// Recursive helper for postOrderPrint
void postOrderPrintHelper(const TreeNode *tree)
{
  if (tree == NULL)
    return;
  postOrderPrintHelper(tree->left);
  postOrderPrintHelper(tree->right);
  cout << tree->info << ' ';
}

// Prints the elements in the tree in post-order order seperated by spaces
void TreeType::PostOrderPrint() const
{
  postOrderPrintHelper(root);
  cout << '\n';
}

// Recursive helper for PrintAncestors
// Walks the tree printing the ancestors until we find value
void PrintAncestorsHelper(const TreeNode *tree, int value)
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
void TreeType::PrintAncestors(int value)
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

TreeNode *TreeType::ptrToSuccessor(TreeNode *&tree) const
{
  if (tree == NULL)
    return NULL;

  if (tree->left == NULL)
    return tree;

  return ptrToSuccessor(tree->left);
}

// Recursive function to find the ptr of a node in the tree
// Walks the tree until value is found else throws error
TreeNode *findItem(TreeNode *tree, int value)
{
  if (tree == NULL)
    throw ItemNotFound();

  if (tree->info == value)
    return tree;

  if (tree->info > value)
    return findItem(tree->left, value);

  return findItem(tree->right, value);
}

int TreeType::GetSuccessor(int value)
{
  TreeNode *item = findItem(root, value);

  if (item->right == NULL)
    return NULL;

  TreeNode *successor = ptrToSuccessor(item->right);
  return successor->info;
}

// helper function for Mirror Image
void mirror(TreeNode *&copy, const TreeNode *originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{
  if (originalTree == NULL)
    return;

  copy->info = originalTree->info;
  if (originalTree->right != NULL)
  {
    copy->left = new TreeNode;
    mirror(copy->left, originalTree->right);
  }
  else
  {
    copy->left = NULL;
  }

  if (originalTree->left != NULL)
  {
    copy->right = new TreeNode;
    mirror(copy->right, originalTree->left);
  }
  else
  {
    copy->right = NULL;
  }
}

// Prints the mirror of t
void TreeType::mirrorImage(TreeType &t)
{
  t.root = new TreeNode;
  mirror(t.root, root);
}

void Destroy(TreeNode *&tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}

void CopyTree(TreeNode *&copy, const TreeNode *originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}

void TreeType::operator=(const TreeType &originalTree)
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
int height(const TreeNode *tree)
{
  if (tree == NULL)
    return 0;

  return 1 + max(height(tree->left), height(tree->right));
}

// Returns a^b
int pow(int a, int b)
{
  if (b == 0)
    return 1;
  if (b == 1)
    return a;

  return a * pow(a, b - 1);
}

// Prints a 2d visulization of the tree
void TreeType::LevelOrderPrint() const
{
  if (root == NULL)
    return;

  int treeHeight = height(root); // height of the tree
  int length = GetLength();      // Amount of nodes in the tree
  int nodesPrinted = 1;          // Amount of nodes printed including nulls '-'
  int nodes = 0;                 // Amount of nodes in the tree printed
  int level = 0;                 // Current level being printed
  QueType<TreeNode *> queue;

  queue.Enqueue(root);

  TreeNode *node;
  while (!queue.IsEmpty())
  {
    if (nodes >= length)
      break;
    
    // Addes correct left offset before the leftmost node in each level
    if (nodesPrinted == pow(2, level))
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
    if (nodesPrinted == pow(2, level + 1) - 1)
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