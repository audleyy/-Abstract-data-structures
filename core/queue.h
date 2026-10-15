#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

using namespace std;

namespace queue {

struct Node {
	string value;
	Node* next;
};

struct Queue {
	Node* head;
	Node* tail;
};

void initQueue(Queue* queue);
void enqueue(Queue* queue, const string& value);
void dequeue(Queue* queue);
void print(Queue* queue);

}

#endif
