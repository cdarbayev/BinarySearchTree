#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Tree {
	Node<T> *root;
	unsigned int counter;
	void insertIntoSubtree(Node<T> *&r, T &data);
	void printSubtree(Node<T>* r) const;
	void cleanSubtree(Node<T>* r);
	Node<T>* findInSubtree(Node<T>* r, Node<T>*& parent, T& data);
	void removeLeaf(Node<T>* leaf, Node<T>* parent);
	void removeInBranch(Node<T>* branch, Node<T>* parent);
	void createBalanceTree(vector<T>& data, int start, int end);
public:
	Tree() : root(nullptr), counter(0) {}
	~Tree() { clean(); }
	void clean() {
		cleanSubtree(root);
		root = nullptr;
		counter = 0;
	}
	void insert(T data) {
		insertIntoSubtree(root, data);
	}
	void print() const {
		printSubtree(root);
	}
	bool exists(T data) {
		Node<T>* dummy = nullptr;
		return findInSubtree(root, dummy, data);
	}
	bool remove(T data);
	T maximum() const;
	void balance(vector<T>& data);
};

template<typename T>
void Tree<T>::balance(vector<T>& data)
{
	if (data.empty()) {
		return;
	}
	sort(data.begin(), data.end());
	data.erase(unique(data.begin(), data.end()), data.end());
	createBalanceTree(data, 0, data.size() - 1);
	
}

template<typename T>
void Tree<T>::createBalanceTree(vector<T>& data, int start, int end)
{
	//pouzil jsem nasi metodu insertIntoSubtree, kterou jsme delali na cviceni.
	if (start > end) {
		return;
	}
	int middle = start + (end - start) / 2;
	insertIntoSubtree(root, data[middle]);
	createBalanceTree(data, start, middle - 1);
	createBalanceTree(data, middle + 1, end);
}

template<typename T>
void Tree<T>::printSubtree(Node<T>* r) const{
	if (r) {
		printSubtree(r->left);
		r->printLn();
		printSubtree(r->right);
	}
}

template<typename T>
void Tree<T>::cleanSubtree(Node<T>* r) {
	if (r) {
		cleanSubtree(r->left);
		cleanSubtree(r->right);
		delete r;
	}
}

template<typename T>
Node<T>* Tree<T>::findInSubtree(Node<T>* r, Node<T>*& parent, T& data)
{
	if (!r) {
		return nullptr;
	}
	if (r->data == data) {
		return r;
	}
	parent = r;
	if (r->data < data) {
		return findInSubtree(r->right, parent, data);
	}
	else {
		return findInSubtree(r->left, parent, data);
	}
}

template<typename T>
void Tree<T>::removeLeaf(Node<T>* leaf, Node<T>* parent)
{
	if (leaf == root) {
		delete root;
		return;
	}
	if (parent->left == leaf) {
		parent->left = nullptr;
	}
	else {
		parent->right = nullptr;
	}
	delete leaf;
}

template<typename T>
void Tree<T>::removeInBranch(Node<T>* branch, Node<T>* parent)
{
	Node<T>* child = branch->left ? branch->left : branch->right;
	if (!parent) {
		delete root;
		root = child;
		return;
	}
	if (parent->left == branch) {
		parent->left = child;
	}
	else {
		parent->right = child;
	}
	delete branch;
}

template<typename T>
bool Tree<T>::remove(T data)
{
	Node<T>* n, * parent = nullptr;
	n = findInSubtree(root, parent, data);
	if (!n) {
		return false;
	}
	if (!n->left && !n->right) {
		this->removeLeaf(n, parent);
		return true;
	}
	if (!n->left || !n->right) {
		this->removeInBranch(n, parent);
		return true;
	}
	if (n->left && n->right) {
		parent = n;
		Node<T>* q = n->right;
		while (q->left) {
			parent = q;
			q = q->left;
		}
		n->data = q->data;
		if (!q->right) {
			removeLeaf(q, parent);
		}
		else {
			removeInBranch(q, parent);
		}
	}
	counter--;
	return true;
}

template<typename T>
inline T Tree<T>::maximum() const
{
	if (!root) {
		throw std::logic_error("Cannot find max value as tree is empty");
	}
	Node<T>* r = root;
	while (r->right) {
		r = r->right;
	}
	return r->data;
}

template<typename T>
void Tree<T>::insertIntoSubtree(Node<T>* &r, T& data) {
	if (!r) {
		r = new Node<T>(data);
		counter++;
		return;
	}
	if (r->getData() < data) {
		insertIntoSubtree(r->right, data);
	}
	else if (r->getData() > data) {
		insertIntoSubtree(r->left, data);
	}
	else {
		throw std::invalid_argument("Value is already present in the tree");
	}
}
#endif