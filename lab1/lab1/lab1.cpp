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
		cout << endl;
		tree.insert(inK, inV);
		tree.print();
	}
}
