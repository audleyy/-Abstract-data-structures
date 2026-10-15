#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

using namespace std;

namespace doubly_linked_list {

struct Node {
	string value;
	Node* next;
	Node* prev;
};

struct List {
	Node* head;
	Node* tail;
};

void init(List* list);

void addTail(List* list, const string& value);
void addHead(List* list, const string& value);
Node* findNode(Node* list, const string& val);
void addAfter(List* list, Node* nodeFound, const string& value);
void addBefore(List* list, Node* nodeFound, const string& value);
void delHead(List* list);
void delTail(List* list);
void delAfter(List* list, Node* nodeFound);
void delBefore(List* list, Node* nodeFound);
void printRegular(List* list);
void printReverse(List* list);
void printIndex(List* list, int index);

}

#endif
