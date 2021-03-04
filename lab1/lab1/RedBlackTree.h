#pragma once
#include "Stack.h"
#include <iostream>
using namespace std;

template <typename K, typename V>
class RedBlackTree
{
private:
	class Node
	{
	public:
		Node(K key, V value, bool color = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) {
			this->key = key;
			this->value = value;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		}
		~Node();
		K key;
		V value;
		Node* left;
		Node* right;
		Node* parent;
		bool color; // black = 0, red = 1
	};
	class dft_Iterator // depth-first traverse
	{
	private:
		Stack<Node*> stack;
		Node* current;
		Node* nil;
	public:
		dft_Iterator(Node* root = nullptr,Node* nil=nullptr) {
			//stack = new Stack<Node*>();
			this->nil = nil;
			current = root;
			stack.push(current);
		}
		Node* next() {
			if (!has_next()) {
				throw "No more elements";
			}
			Node* temp = current;
			if (current->right != nil)
			{
				stack.push(current->right);
			}
			if (current->left != nil)
			{
				current = current->left;
			}else{
				current = stack.pop();
			}
			return temp;
		}
		bool has_next() {
			if (!stack.isEmpty())
				return true;
			else
				return false;
		}
		~dft_Iterator() {};
	};
	Node* root;
	Node* nil = new Node(' ', ' ', 0);;
	int count;
public:
	void insert(K insKey, V insValue) // добавление элемента с ключом и значением
	{
		if (root == nullptr)
		{
			root = new Node(insKey, insValue, false, nil,nil,nil);
			count++;
		}
		else {
			Node* newNode = new Node(insKey, insValue, true, nil, nil, nil);
			Node* parent = root;
			Node* leaf = nullptr;
			while (parent != nil)// спускаемся вниз, пока не дойдем до подходящего листа
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
				leaf->left = newNode;\
			coloring(newNode);
			count++;
		}
	};
	void coloring(Node* node) {
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
	void LeftRotation(Node* node) {
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
	};
	void RightRotation(Node* node) {
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
	void remove(K remKey) // удаление элемента дерева по ключу
	{
		count--;
		Node* node = root;
	Node* nodeA, nodeB;
	while (root->key != remKey)// спускаемся вниз, пока не дойдем до подходящего листа
	{
		if (node == nil)
		{
			throw out_of_range("Element not found");
		}
		if (node->key < remKey)
			node = node->right;
		else
			node = node->left;
	}
	if ((node->left == nil)||(node->right == nil))
		nodeA = node;
	else {
		nodeA = node->right;
		while (nodeA->left != nil) nodeA = nodeA->left;
	}
	if (nodeA->left != nil)
		nodeB = nodeA->left;
	else
		nodeB = nodeA->right;

	nodeB->parent = nodeA->parent;
	if (nodeA->parent != nil)
	{
		if (nodeA == nodeA->parent->left)
			nodeA->parent->left = nodeB;
		else
			nodeA->parent->right = nodeB;
	}
	else {
		root = nodeB;
	}
	if (nodeA != node)
	{
		node->key = nodeA->key;
		node->value = nodeA->value;
	}
	if (nodeA->color == false)
	{
		removeFix(nodeB);
	}
	delete nodeA;
	};
	void removeFix(Node* node) {
		Node* brother;
		while ((node != root) && (node->color == false))
		{
			if (node == node->parent->left)
			{
				brother = node->parent->right;
				if (brother->color)
				{
					brother->color = false;
					node->parent->color = true;
					LeftRotation(node->parent);
					brother = node->parent->right;
				}
				if ((brother->left->color == false)&&(brother->right->color == false))
				{
					brother->color = true;
					node = node->parent;
				}
				else {
					if (brother->right->color == false)
					{
						brother->left->color = false;
						brother->color = true;
						RightRotation(brother);
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->right->color = false;
					LeftRotation(node->parent);
					node = root;
				}
			}
			else {
				brother = node->parent->left;
				if (brother->color)
				{
					brother->color = false;
					node->parent->color = true;
					RightRotation(node->parent);
					brother = node->parent->left;
				}
				if ((brother->right->color == false) && (brother->left->color == false))
				{
					brother->color = true;
					node = node->parent;
				}
				else {
					if (brother->lrft->color == false)
					{
						brother->right->color = false;
						brother->color = true;
						LeftRotation(brother);
						brother = node->parent->left;
					}
					brother->color = node->parent->color;
					node->parent->color = false;
					brother->left->color = false;
					RightRotation(node->parent);
					node = root;
				}
			}
		}
		node->color = false;
	};
	V find(K finKey) // поиск элемента по ключу
	{
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
	void clear() // очищение ассоциативного массива
	{
		while ((roor != nil)||(root != nullptr))
			remove(root->key);
		root = nil;
		count = 0;
	};
	int getSize() {
		return cout;
	};
	K* get_keys() // возвращает список ключей
	{
		dft_Iterator i(root, nil);
		K* arr = new K[count];
		int arrI = 0;
		Node* cur;
		while (i.has_next())
		{
			cur = i.next();
			arr[arrI] = cur->key;
		}
		return arr;
	};
	V* get_values() // возвращает список значений
	{
		dft_Iterator i(root, nil);
		V* arr = new V[count];
		int arrI = 0;
		Node* cur;
		while (i.has_next())
		{
			cur = i.next();
			arr[arrI] = cur->value;
		}
		return arr;
	};
	void print() // вывод в консоль
	{
		dft_Iterator i(root, nil);
		Node* cur;
		while (i.has_next())
		{
			cur = i.next();
			cout << cur->value << "  ";
		}
		cout << endl;
	};

	RedBlackTree(Node* root=nil, int count=0) {
		this->root = root;
		this->count = count;
	}
	~RedBlackTree() {
		clear();
		delete root;
	}
};

#include "Stack.cpp"

