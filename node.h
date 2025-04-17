#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
class Node {
private:
	Node<T>* left;
	Node<T>* right;
	//Node<T>* parent;
	T data;
public:
	Node(T payload) : left(nullptr), right(nullptr), data(payload) {}
	T getData() const { return data; }
	void setData(const T& newData) { data = newData; }
	void print() const {
		cout << getData();
	}
	void printLn() const {
		print();
		cout << endl;
	}
	template<typename X> friend class Tree;
};
#endif
