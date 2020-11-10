#include <iostream>
using namespace std;
#include "TreeType.h"
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

TreeType::TreeType(const TreeType &originalTree)
{
}

void Destroy(TreeNode *&tree);

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

int CountNodes(TreeNode *tree);

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

void Retrieve(TreeNode *tree, ItemType &item, bool &found);

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

void Insert(TreeNode *&tree, ItemType item);

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

void DeleteNode(TreeNode *&tree);

void Delete(TreeNode *&tree, ItemType item);

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

void GetPredecessor(TreeNode *tree, ItemType &data);

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

void preOrderPrintHelper(const TreeNode* tree) {
  if(tree == NULL) return;
  cout << tree->info << ' ';
  preOrderPrintHelper(tree->left);
  preOrderPrintHelper(tree->right);
}

void TreeType::PreOrderPrint() const
{ 
  preOrderPrintHelper(root);
  cout << '\n';
}

void postOrderPrintHelper(const TreeNode* tree) {
  if(tree == NULL) return;
  postOrderPrintHelper(tree->left);
  postOrderPrintHelper(tree->right);
  cout << tree->info << ' ';
}

void TreeType::PostOrderPrint() const
{
  postOrderPrintHelper(root);
  cout << '\n';
}

void PrintAncestorsHelper(const TreeNode* tree, int value) {
  if(tree->info == value) {
    return;
  }

  cout << tree->info << ' ';

  if(tree->info > value) {
    PrintAncestorsHelper(tree->left, value);
  } else {
    PrintAncestorsHelper(tree->right, value);
  }
}

void TreeType::PrintAncestors(int value)
{
  if(root->info == value)
    cout << value << " is the root value, No ancestor" << endl;

  bool hasItem = true;
  GetItem(value, hasItem);
  if(hasItem) {
    PrintAncestorsHelper(root, value);
    cout << endl;
  } else {
    cout << value << " is not in the tree" << endl;
  }
}

TreeNode* TreeType::ptrToSuccessor(TreeNode*& tree) const {
  if(tree == NULL)
    return NULL;

  if(tree->left == NULL) 
    return tree;

  return ptrToSuccessor(tree->left);
}

TreeNode* findItem(TreeNode* tree, int value) {
  if(tree == NULL)
    throw ItemNotFound();

  if(tree->info == value)
    return tree;

  if(tree->info > value)
    return findItem(tree->left, value);

  return findItem(tree->right, value);
}

int TreeType::GetSuccessor(int value)
{
  TreeNode* item = findItem(root, value);

  if(item->right == NULL)
    return NULL;

  TreeNode* successor = ptrToSuccessor(item->right);
  return successor->info;
}

// helper function for Mirror Image
void mirror(TreeNode *&copy, const TreeNode *originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{ 
  if(originalTree == NULL) return;

  copy->info = originalTree->info;
  if(originalTree->right != NULL) {
    copy->left = new TreeNode;
    mirror(copy->left, originalTree->right);
  } else {
    copy->left = NULL;
  }

  if(originalTree->left != NULL) {
    copy->right = new TreeNode;
    mirror(copy->right, originalTree->left);
  } else {
    copy->right = NULL;
  }
}

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

void CopyTree(TreeNode *&copy,
              const TreeNode *originalTree)
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

void LevelOrderPrintHelper(const TreeNode* tree, int offset) {
  if(tree == NULL) return;
  offset += 1;
  LevelOrderPrintHelper(tree->right, offset);

  for(int i = 1; i < offset; i++) {
    cout << '\t';
  }

  cout << tree->info << endl;
  LevelOrderPrintHelper(tree->left, offset);
}

void TreeType::LevelOrderPrint() const
{
  LevelOrderPrintHelper(root, 0);
}