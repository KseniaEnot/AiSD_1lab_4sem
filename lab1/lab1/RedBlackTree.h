#pragma once
#include "Stack.h"

template <class K, class V>
class RedBlackTree
{
private:
	class Node
	{
	private:
		K key;
		V value;
		Node* left;
		Node* right;
		Node* parent;
		bool color; // black = 0, red = 1
	public:
		Node(K key, V value,bool color = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) {
			this->key = key;
			this->value = value;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		}
		~Node();
	};
	class dft_Iterator // depth-first traverse
	{
	private:
		Stack<Node*> stack;
		Node* current;
	public:
		dft_Iterator() {
			stack = new Stack();
			current = root;
			stack->push(current);
			if (current->right != nil)
				stack->push(current->right);
		};
		Node* next() {
			if (!has_next()) {
				throw "No more elements";
			}
			Node* temp = current;
			if (current->right != nil)
			{
				stack->push(current->right);
			}
			if (current->left != nil)
			{
				current = current->left;
			}
			if (current == temp)
			{
				if (!stack->isEmpty())
				{
					current = stack->pop();
				}
			}
			return temp;
		}
		bool has_next() {
			if (!stack->isEmpty() || (current->left != nil) || (current->right != nil))
				return true;
			else
				return false;
		}
		~dft_Iterator();
	};
	Node* root;
	Node* nil = new Node(' ',' ',0);
	int count;
public:
	void insert(K, V); // добавление элемента с ключом и значением
	void coloring(Node*);
	void LeftRotation(Node*);
	void RightRotation(Node*);
	void remove(K); // удаление элемента дерева по ключу
	V find(K); // поиск элемента по ключу
	void clear(); // очищение ассоциативного массива
	K* get_keys(); // возвращает список ключей
	V* get_values(); // возвращает список значений
	void print(); // вывод в консоль\


	RedBlackTree(Node* root=nullptr, int count=0) {
		this->root = root;
		this->count = count;
	}
	~RedBlackTree() {

	}
};

