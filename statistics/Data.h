#pragma once

#include <vector>

template <class T>
struct Node {
	Node* next;
	Node* previous;
	T data;
};

template <class T>
Node<T>* createNodeList(std::vector<T> data);
