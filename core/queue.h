#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

namespace	queue {

struct Node {
	int value;
	Node* next;
};

struct Queue {
	Node* head;
	Node* tail;
};

void initQueue(Queue* queue);
void enqueue(Queue* queue, int value);
void dequeue(Queue* queue);
void print(Queue* queue);

}

#endif