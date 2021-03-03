#include "Stack.h"
using namespace std;

template <class T>
void Stack<T>::push(T add)
{
	if (size == 0) //if list is empty
	{
		head = new Node(add); //create head
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->before = tail;
		tail->next = curr;
		tail = curr;  //set new tail
	}
	size++;
}

template <class T>
size_t Stack<T>::get_size()
{
	return size;
}

template <class T>
T Stack<T>::pop()
{
	T cont;
	if (size == 1)
	{
		size = 0;  //setup zero position
		cont = tail->content;
		head = NULL;
		tail = NULL;

	}
	else if (size > 1) //if list is not empty
	{
		cont = tail->content;
		tail = tail->before; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	else  //else return error
		throw out_of_range("Segmentation fault");
	return cont;
}

template <class T>
void Stack<T>::clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all item
		{
			head = head->next;
			delete head->before;
		}
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}
