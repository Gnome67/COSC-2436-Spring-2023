#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
#include <ctype.h>
#include <stdio.h>
using namespace std;
template <typename T> 
struct Node
{
  T data;
  int level;
  Node<T> *leftChild;
  Node<T> *rightChild;
};

template <typename T> 
class BST
{
	public:
  	BST();
  	Node<T> *Insert(Node<T> *node, T element);
  	Node<T> *InsertHelper(Node<T> *node, T element);
  	void PrintLR(Node<T> *root, ofstream& out); 
  	void PrintLevel(Node<T> *root, int level,ofstream& out);
  	void Mirror(Node<T> *node);
  	Node<T> *getRoot();  
	private:
  	Node<T> *root;
};

template <typename T> 
BST<T>::BST() { root = nullptr; }

template <typename T> 
Node<T>* BST<T>::getRoot() { return root; } 

template <typename T> 
Node<T> *BST<T>::Insert(Node<T> *node, T element)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = element;
	newNode->level = 0;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;
  if (node == nullptr)
	{
    if (root == nullptr)
		{
      root = newNode;
      return root;
		}
  	node = newNode;
	}
  else if (element < node->data) { node->leftChild = Insert(node->leftChild, element); } 
  else if (element > node->data) { node->rightChild = Insert(node->rightChild, element); }
  return node;
}

template <typename T> 
Node<T> *BST<T>::InsertHelper(Node<T> *node, T element)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = element;
	newNode->level = 0;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;
  if (node == nullptr)
	{
    if (root == nullptr)
		{
      root = newNode;
      return root;
    }
  	node = newNode;
	}
  else if (element < node->data) { node->rightChild = InsertHelper(node->rightChild, element); } 
  else if (element > node->data) { node->leftChild = InsertHelper(node->leftChild,element); }
  return node;
}

template <typename T> 
void ::BST<T>::Mirror(Node<T> *root)
{
  if (root == nullptr) { return; }
  Mirror(root->leftChild);
  Mirror(root->rightChild);
  swap(root->leftChild, root->rightChild);
}

template <typename T> 
void BST<T>::PrintLR(Node<T> *root, ofstream &out)
{
  if (root != nullptr)
	{
    PrintLR(root->leftChild,out);
    out << root->data << " ";
    PrintLR(root->rightChild,out);
  }
}

template <typename T>
void ::BST<T>::PrintLevel(Node<T> *root, int level, ofstream &out)
{
  if (root == nullptr)
	{
    out << "Does not exist!" << endl;
    return;
  }
  queue <Node<T>*> levelQueue;
  levelQueue.push(root);
  for (int s = 0; s < level; s++)
	{
    int levelsize = levelQueue.size();
    for (int i = 0; i < levelsize; i++)
		{
      Node <T> *currentNode = levelQueue.front();
      levelQueue.pop();
      if (currentNode->leftChild != nullptr) { levelQueue.push(currentNode->leftChild); }
      if (currentNode->rightChild != nullptr) { levelQueue.push(currentNode->rightChild); }
    }
    if (levelQueue.empty())
		{
			out << "Does not Exist!" << endl;
      return;
    }
  }
  while (!levelQueue.empty())
	{
    Node <T> *currentNode = levelQueue.front();
    levelQueue.pop();
    out << currentNode->data << " ";
  }
  out << endl;
}

int main(int argc, char *argv[])
{
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream out(am.get("output"));

	string line;
	string val = "";
	BST<string> stringTree;
	BST<int> intTree;
	bool ifTrueCheck = true;

  while (input >> line)
	{
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    if (line.find("Insert") != string::npos)
		{
      val = line.substr(7, line.find(")") - line.find("(") - 1);
      if (isalpha(val[0]))
			{
        if(ifTrueCheck) { stringTree.Insert(stringTree.getRoot(), val); }
        else { stringTree.InsertHelper(stringTree.getRoot(),val); }
      } else {
        if(ifTrueCheck) { intTree.Insert(intTree.getRoot(), stoi(val)); }
        else { intTree.InsertHelper(intTree.getRoot(),stoi(val)); }
      }
    } else if (line.find("PrintLR") != string::npos) {
      if(intTree.getRoot() != nullptr)
			{
        intTree.PrintLR(intTree.getRoot(),out);
        out << endl;;
      }
      else
			{
        stringTree.PrintLR(stringTree.getRoot(), out);
        out << endl;
      }
    } else if (line.find("PrintLevel") != string::npos) {
      val = line.substr(11, line.find(")") - line.find("(") - 1);
      if(intTree.getRoot() != nullptr) { intTree.PrintLevel(intTree.getRoot(), stoi(val), out); }
      else { stringTree.PrintLevel(stringTree.getRoot(),stoi(val), out); }
    }

    else if (line.find("Mirror") != string::npos)
		{
      if(intTree.getRoot() != nullptr)
			{ intTree.Mirror(intTree.getRoot()); }
      else { stringTree.Mirror(stringTree.getRoot()); }
      if(ifTrueCheck) { ifTrueCheck = false; }
      else { ifTrueCheck = true; }
    }
  }
}