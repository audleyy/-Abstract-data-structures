#include "queue.h"

namespace queue {

void initQueue(Queue* queue) {
	queue->head = nullptr;
	queue->tail = nullptr;
}

void enqueue(Queue* queue, const string& value) {
	Node* newNode = new Node{value, nullptr};
	if (queue->head == nullptr) {
		newNode->next = queue->head;
		queue->head = newNode;
		queue->tail = newNode;
		return;
	}

	queue->tail->next = newNode;
	queue->tail = newNode;
}

void dequeue(Queue* queue) {
	if (queue->head == nullptr) return;

	Node* toDelete = queue->head;
	queue->head = toDelete->next;

	if (queue->head == nullptr) {
		queue->tail = nullptr;
	}

	delete toDelete;
}

void print(Queue* queue) {
	Node* current = queue->head;

	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}

	cout << endl;
}

}
