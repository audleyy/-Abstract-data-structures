#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <string>

using namespace std;

namespace singly_linked_list {

struct Node {
	string value;
	Node* next;
};

void addToHead(Node* &head, const string& value);
void addToTail(Node* &head, const string& value);
void addAfter(Node* nodeFound, const string& value);
void addBefore(Node* &head, Node* nodeFound, const string& value);
Node* findNode(Node* head, const string& val);
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
