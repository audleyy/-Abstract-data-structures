#include "forwardList.h"

namespace singly_linked_list {

void addToHead(Node* &head, const string& value) {
	Node* newNode = new Node{value, nullptr};

	newNode->next = head;
	head = newNode;
}

void addToTail(Node* &head, const string& value) {
	Node* newNode = new Node{value, nullptr};
	Node* current = head;

	if (head == nullptr) {
		head = newNode;
		return;
	}

	while (current->next != nullptr) {
		current = current->next;
	}

	current->next = newNode;
}

void addAfter(Node* nodeFound, const string& value) {
	Node* newNode = new Node{value, nullptr};

	newNode->next = nodeFound->next;
	nodeFound->next = newNode;
}

void addBefore(Node* &head, Node* nodeFound, const string& value) {
	Node* newNode = new Node{value, nullptr};
	Node* current = head;

	if (nodeFound == head) {
		newNode->next = nodeFound;
		head = newNode;
		return;
	}

	while (current->next != nodeFound) {
		current = current->next;
	}

	newNode->next = nodeFound;
	current->next = newNode;
}

Node* findNode(Node* head, const string& val) {
	Node* current = head;

	while (current != nullptr) {
		if (current->value == val) return current;

		current = current->next;
	}
	return nullptr;
}

void deleteHead(Node* &head) {
	if (head == nullptr) return;

	Node* toDelete = head;

	head = toDelete->next;
	delete toDelete;
}

void deleteTail(Node* &head) {
	if (head == nullptr) return;

	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}

	Node* toDelete = head;

	while (toDelete->next->next != nullptr) {
		toDelete = toDelete->next;
	}

	Node* tail = toDelete->next;
	toDelete->next = nullptr;
	delete tail;
}

void deleteBefore(Node* &head, Node* nodeFound) {
	if (head->next == nodeFound) {
		Node* toDelete = head;
		head = nodeFound;
		delete toDelete;
		return;
	}

	Node* temp = head;

	while (temp->next->next != nodeFound) {
		temp = temp->next;
	}

	Node* toDelete = temp->next;

	temp->next = nodeFound;
	delete toDelete;
}

void deleteAfter(Node* nodeFound) {
	if (nodeFound->next == nullptr) return;

	Node* toDelete = nodeFound->next;
	nodeFound->next = nodeFound->next->next;
	delete toDelete;
}

void deleteCurrent(Node* &head, Node* nodeFound) {
	if (nodeFound == head) {
		Node* toDelete = head;
		head = nodeFound->next;
		delete toDelete;
		return;
	}

	Node* temp = head;

	while (temp->next != nodeFound) {
		temp = temp->next;
	}
	temp->next = nodeFound->next;
	delete nodeFound;
}

void printRegular(Node* head) {
	Node* current = head;

	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}

	cout << endl;
}

void printReverse(Node* head) {
	if (head == nullptr) return;

	printReverse(head->next);
	cout << head->value << " ";
}

void printIndex(Node* head, int index) {
	Node* current = head;

	for (int i = 0; i < index && current != nullptr; ++i) {
		current = current->next;
	}

	if (current != nullptr) cout << current->value << endl;
}

void init(Node* &head) {
	head = nullptr;
}

}