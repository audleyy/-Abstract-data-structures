#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

namespace stack {

struct Node {
	string value;
	Node* next;
};

struct Stack {
	Node* head;
};

void initStack(Stack* stack);
bool isEmpty(Stack* stack);
void push(Stack* stack, const string& value);
void pop(Stack* stack);
void print(Stack* stack);

}

#endif
