#include "Data.h"

template <class T>
Node<T>* createNodeList(std::vector<T> data) {
	auto head = new Node<T>();

	auto current = head;
	for (int i = 0; i < data.size(); i++) {
		current->data = data.at(i);
		if (i < data.size() - 1) {
			current->next = new Node();
			current->next->previous = current;
		}
		current = current->next;
	}

	return head;
}