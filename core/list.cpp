#include "list.h"

namespace doubly_linked_list {

void addTail(List* list, const string& value) {
	Node* newNode = new Node{value, nullptr, nullptr};

	if (list->head == nullptr) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
	}
}

void addHead(List* list, const string& value) {
	Node* newNode = new Node{value, nullptr, nullptr};

	if (list->head == nullptr) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}
}

Node* findNode(Node* list, const string& val) {
	Node* current = list;

	while (current != nullptr) {
		if (current->value == val) return current;
		current = current->next;
	}

	return nullptr;
}

void addAfter(List* list, Node* nodeFound, const string& value) {
	Node* newNode = new Node{value, nullptr, nullptr};

	if (nodeFound->next == nullptr) {
		nodeFound->next = newNode;
		newNode->prev = nodeFound;
		list->tail = newNode;
	} else {
		newNode->next = nodeFound->next;
		newNode->prev = nodeFound;

		nodeFound->next->prev = newNode;
		nodeFound->next = newNode;
	}
}

void addBefore(List* list, Node* nodeFound, const string& value) {
	Node* newNode = new Node{value, nullptr, nullptr};

	if (nodeFound->prev == nullptr) {
		newNode->next = nodeFound;
		nodeFound->prev = newNode;
		list->head = newNode;
	} else {
		newNode->next = nodeFound;
		newNode->prev = nodeFound->prev;

		nodeFound->prev->next = newNode;
		nodeFound->prev = newNode;
	}
}

void delHead(List* list) {
	if (list->head == nullptr) return;

	Node* toDelete = list->head;

	if (list->head->next == nullptr) {
		list->head = nullptr;
		list->tail = nullptr;
		delete toDelete;
		return;
	}
	list->head = list->head->next;
	list->head->prev = nullptr;

	delete toDelete;
}

void delTail(List* list) {
	if (list->tail == nullptr) return;

	if (list->head == list->tail) {
	Node* toDelete = list->tail;

		list->head = nullptr;
		list->tail = nullptr;
		delete toDelete;
		return;
	}

	Node* toDelete = list->tail;
	list->tail = toDelete->prev;
	list->tail->next = nullptr;

	delete toDelete;
}

void delAfter(List* list, Node* nodeFound) {
	if (nodeFound->next == nullptr) return;
	if (nodeFound->next == list->tail) {
		delTail(list);
		return;
	}

	Node* toDelete = nodeFound->next;

	nodeFound->next->prev = nodeFound;
	nodeFound->next = toDelete->next;
	delete toDelete;
}

void delBefore(List* list, Node* nodeFound) {
	if (nodeFound->prev == nullptr) return;

	if (nodeFound->prev == list->head) {
		delHead(list);
		return;
	}

	Node* toDelete = nodeFound->prev;

	nodeFound->prev->next = nodeFound;
	nodeFound->prev = toDelete->prev;

	delete toDelete;
}

void printRegular(List* list) {
	Node* current = list->head;

	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}

	cout << endl;
}

void printReverse(List* list) {
  if (list == nullptr) return;

  Node* current = list->tail;
  while (current != nullptr) {
    cout << current->value << " ";
    current = current->prev;
  }
  cout << endl;
}

void printIndex(List* list, int index) {
	Node* current = list->head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}

	if (current != nullptr) cout << current->value << endl;
}

void init(List* list) {
	if (list == nullptr) return;

	list->head = nullptr;
	list->tail = nullptr;
}

}

