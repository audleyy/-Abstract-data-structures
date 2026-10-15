#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

namespace dynamic_array {

struct Array {
	int* data;
	int size;
};

void initArray(Array& arr);
void pushIndex(Array& arr, int index, int value);
void pushBack(Array& arr, int value);
int get(Array& arr, int index) ;
void remove(Array& arr, int index);
void replace(Array& arr, int index, int value);
int length(Array& arr);
void destroy(Array& arr);
void print(Array arr);

}

#endif 