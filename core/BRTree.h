#ifndef BRTREE_H
#define BRTREE_H

#include <iostream>

using namespace std;

namespace red_black_tree {

struct Node {
	int value;
	bool isRed;
	Node* left;
	Node* right;
};

bool isRed(Node* root);
void rotateLeft(Node* &root);
void rotateRight(Node* &root);
void balance(Node* &root);
void insertRecursive(Node*& root, int value);
void insert(Node* &root, int value);
bool balanceAfterDeleteLeft(Node*& root);
bool balanceAfterDeleteRight(Node* &root);
bool removeRecursive(Node* &root, int val, bool &blackHeightDecreased);
bool removeElement(Node*& root, int value);
Node* searchElement(Node* root, int val);
void printTree(Node* root);

}
#endif