#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

namespace doubly_linked_list {

struct Node {
	int value;
	Node* next;
	Node* prev;
};

struct List {
	Node* head;
	Node* tail;
};

void addTail(List* list, int value);
void addHead(List* list, int value);
Node* findNode(Node* list, int val);
void addAfter(List* list, Node* nodeFound, int value);
void addBefore(List* list, Node* nodeFound, int value);
void delHead(List* list);
void delTail(List* list);
void delAfter(List* list, Node* nodeFound);
void delBefore(List* list, Node* nodeFound);
void printRegular(List* list);
void printReverse(List* list);
void printIndex(List* list, int index);

}

#endif