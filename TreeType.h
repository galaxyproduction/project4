#ifndef TREETYPEH
#define TREETYPEH
#include <string>
#include <fstream>

template<class T>
struct TreeNode;
class ItemNotFound {};
class NullSuccessor {};

#include "QueType.cpp"

template<class T>
class TreeType
{
public:
  TreeType();                             // constructor
  TreeType(const TreeType &originalTree); // copy constructor
  ~TreeType();                            // destructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;
  T GetItem(T item, bool &found);
  void PutItem(T item);
  void DeleteItem(T item);
  void operator=(const TreeType &originalTree);
  void Print() const;
  void LevelOrderPrint() const;
  void PrintAncestors(T value);
  void PreOrderPrint() const;
  void PostOrderPrint() const;
  T GetSuccessor(T value);
  void mirrorImage(TreeType &t);

private:
  TreeNode<T> *ptrToSuccessor(TreeNode<T> *&tree) const;

  TreeNode<T> *root;
};

#endif