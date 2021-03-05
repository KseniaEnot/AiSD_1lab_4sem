#include "RedBlackTree.h"
#include <iostream>
using namespace std;

int main()
{
    RedBlackTree<int,char> tree = RedBlackTree<int, char>();
	int inK;
	char inV; 
	for (size_t i = 0; i < 5; i++)
	{
		cout << "<key value>:";
		cin >> inK >> inV;
		tree.insert(inK, inV);
	}
	int* keys = tree.get_keys();
	for (size_t i = 0; i < tree.getSize(); i++)
		cout << keys[i] << " ";
	cout << endl;
	char* values = tree.get_values();
	for (size_t i = 0; i < tree.getSize(); i++)
		cout << values[i] << " ";
	cout << endl;
	tree.print();
	cout << "Remove <key>:";
	cin >> inK;
	tree.remove(inK);
	tree.print();
	cout << "Find <key>:";
	cin >> inK;
	cout << tree.find(inK);
}
