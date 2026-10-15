#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>

using namespace std;

namespace singly_linked_list {

struct Node {
	int value;
	Node* next;
};

void addToHead(Node* &head, int value);
void addToTail(Node* &head, int value);
void addAfter(Node* nodeFound, int value);
void addBefore(Node* &head, Node* nodeFound, int value);
Node* findNode(Node* head, int val);
void deleteHead(Node* &head);
void deleteTail(Node* &head);
void deleteBefore(Node* &head, Node* nodeFound);
void deleteAfter(Node* nodeFound);
void deleteCurrent(Node* &head, Node* nodeFound);
void printRegular(Node* head);
void printReverse(Node* head);
void printIndex(Node* head, int index);

}

#endif