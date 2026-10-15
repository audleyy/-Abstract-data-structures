#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

namespace stack {

struct Node {
	int value;
	Node* next;
};

struct Stack {
	Node* head;
};

void initStack(Stack* stack);
bool isEmpty(Stack* stack);
void push(Stack* stack, int value);
void pop(Stack* stack);
void print(Stack* stack);

}

#endif