#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include "ArgumentManager.h"
#include <ctype.h>
#include <stdio.h>
using namespace std;

template <class T>
struct Node
{
  T data;
  int height;
  Node <T> *left, *right;
};

template <class T>
class binary_tree
{
	private:
  	Node <T> * root;
  	bool Mirror;
  	void deleteBST(Node<T>* node)
		{
    	if(node == nullptr) { return; }
    	deleteBST(node->left);
    	deleteBST(node->right);
    	delete node;
  	}
	public:
  	binary_tree()
		{
    	root = nullptr;
    	Mirror = false;
  	}
  	~binary_tree() { deleteBST(root); }
  	Node<T>* getRoot() { return root; }
  	Node<T>* Insert(Node <T> * t, T value, int height = 0)
		{
    	if(t == nullptr)
			{
     		Node<T>* temp = new Node<T>();
      	temp->data = value;
      	temp->height = height;
      	temp->left = nullptr;
      	temp->right = nullptr;
      	if(root == nullptr) { root = temp; }
      	return temp;
    	}
    	if(value < t->data) { t->left = Insert(t->left, value, height+1); }
			else if(value > t->data) { t->right = Insert(t->right, value, height+1); }
  	  return t;
  	}
  	void MirrorX()
		{
    	if(Mirror == false) { Mirror = true; }
			else { Mirror = false; }
  	}
	  void Inorder(Node <T> * node, ostream& os)
		{
    	if(node == nullptr) { return; }
    	if(Mirror == false)
			{
      	Inorder(node->left, os);
      	os << node->data << " ";
      	Inorder(node->right, os);
    	}
			else
			{
      	Inorder(node->right, os);
      	os << node->data << " ";
      	Inorder(node->left, os);
    	}
  	}
  	void Print_height(Node<T>* root, int height, ostream& os)
		{
   		if(root == nullptr)
			{
      	os << "Does Not Exist!" << endl;
      	return;
    	}
			int numbers = -1;
    	queue<Node<T>*> q;
    	q.push(root);
    	while (!q.empty())
			{
      	int sizeOfheight = q.size();
      	for (int i = 0; i < sizeOfheight; i++)
				{
        	Node<T>* current = q.front();
        	q.pop();
        	if(current->height == height)
					{
          	numbers++;
          	os << current->data << " ";
        	}
        	if(Mirror == false)
					{
          	if (current->left != nullptr) { q.push(current->left); }
          	if (current->right != nullptr) { q.push(current->right); }
        	} else {
          	if (current->right != nullptr) { q.push(current->right); }
          	if (current->left != nullptr) { q.push(current->left); }
        	}
      	}
    	}
  		if(numbers == -1) { os << "Does Not Exist!"; }
    	os << endl;
  }
};

int main(int argc, char* argv[]) {
  
  ArgumentManager am(argc, argv);
  ifstream in(am.get("input"));
  ofstream out(am.get("output"));
  binary_tree<string> a;
  string thread;
  string stamp;
  while(in >> thread)
	{
    if(thread.find("Insert") != string::npos){
      stamp = thread.substr(thread.find("(") + 1, thread.find(")") - thread.find("(") - 1);
      a.Insert(a.getRoot(), stamp);
    }else if(thread.find("PrintLR") != string::npos){
      a.Inorder(a.getRoot(), out);
      out << endl;
    }else if(thread.find("PrintLevel") != string::npos){
      stamp = thread.substr(thread.find("(") + 1, thread.find(")") - thread.find("(") - 1);
      a.Print_height(a.getRoot(), stoi(stamp), out);
    }else if(thread.find("Mirror") != string::npos){
      a.MirrorX();
    }
  }
}