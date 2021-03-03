#include "RedBlackTree.h"
#include <iostream>
using namespace std;

template <typename K, typename V>
void RedBlackTree<K, V>::insert(K insKey, V insValue) {
	if (root == nullptr)
	{
		root = new Node(insKey, insValue, 0, nil);
		count++;
	}
	else {
		Node* newNode = new Node(insKey, insValue, true);
		Node* parent = root;
		Node* leaf = nullptr;
		while (parent != nullptr)// спускаемся вниз, пока не дойдем до подходящего листа
		{
			leaf = parent;
			if (parent->key < newNode->key)
				parent = parent->right;
			else
				parent = parent->left;
		}
		newNode->parent = leaf; // добавляем новый элемент красного цвета 
		if (leaf->key < newNode->key)
			leaf->right = newNode;
		else
			leaf->left = newNode;
		coloring(newNode);
		count++;
	}
}

template <typename K, typename V>
void RedBlackTree<K, V>::LeftRotation(Node* node) {
	Node* child = node->right;
	node->right = child->left;
	if (child->left != nil)
		child->left->parent = node;
	if (child != nil)
		child->parent = node->parent;
	if (node->parent != nil)
	{
		if (node == node->parent->left)
			node->parent->left = child;
		else
			node->parent->right = child;
	}
	else
		root = child;
	child->left = node;
	if (node != nil)
		node->parent = child;
}

template <typename K, typename V>
void RedBlackTree<K, V>::RightRotation(Node* node) {
	Node* child = node->left;
	node->left = child->right;
	if (child->right != nil)
		child->right->parent = node;
	if (child != nil)
		child->parent = node->parent;
	if (node->parent != nil)
	{
		if (node == node->parent->right)
			node->parent->right = child;
		else
			node->parent->left = child;
	}
	else
		root = child;
	child->right = node;
	if (node != nil)
		node->parent = child;
};

template <typename K, typename V>
void RedBlackTree<K, V>::coloring(Node* node) {
	if (node == root)
	{
		node->color = 0;
		return;
	}
	Node* uncle;
	while (node->parent->color) //"отец" красный 
	{
		if (node->parent == node->parent->parent->left) //отец левый сын
		{
			uncle = node->parent->parent->right;
			if (uncle->color) //если дядя красный
			{
				node->parent->color = false;
				uncle->color = false;
				node->parent->parent->color = true;
				node = node->parent->parent;
			}
			else { //если дядя черный
				if (node == node->parent->right) {
					node = node->parent;
					LeftRotation(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				RightRotation(node->parent->parent);
			}
		}
		else {
			uncle = node->parent->parent->left;
			if (uncle->color) //если дядя красный
			{
				node->parent->color = false;
				uncle->color = false;
				node->parent->parent->color = true;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					RightRotation(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				LeftRotation(node->parent->parent);
			}
		}
	}
	root->color = false;
};

template <typename K, typename V>
V RedBlackTree<K, V>::find(K finKey) {
	Node* node = root;
	while (root->key != finKey)// спускаемся вниз, пока не дойдем до подходящего листа
	{
		if (node == nil)
		{
			throw out_of_range("Element not found");
		}
		if (node->key < finKey)
			node = node->right;
		else
			node = node->left;
	}
	return node->value;
};

template <typename K, typename V>
void RedBlackTree<K, V>::remove(K remKey) {

}

template <typename K, typename V>
void RedBlackTree<K, V>::clear() {

};

template <typename K, typename V>
K* RedBlackTree<K, V>::get_keys() {

};

template <typename K, typename V>
V* RedBlackTree<K, V>::get_values() {

};

template <typename K, typename V>
void RedBlackTree<K, V>::print() {
	dft_Iterator i(root, nil);
	Node* cur;
	while (i.has_next())
	{
		cur = i.next();
		cout << cur->value << "  ";
	}
	cout << endl;
}
