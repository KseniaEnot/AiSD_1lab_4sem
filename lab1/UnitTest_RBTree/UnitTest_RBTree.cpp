#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/RedBlackTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRBTree
{
	TEST_CLASS(UnitTestRBTree)
	{
	public:
		RedBlackTree<int, char> tree;
		int* keys;
		int* keysTree;
		char* values;
		char* valuesTree;
		
		TEST_METHOD(insert_1)
		{
			tree.insert(1, 'c');
			keys = new int[1]{1};
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		TEST_METHOD(insert_5)
		{
			tree.insert(5, 'c');
			tree.insert(4, 'a');
			tree.insert(3, 'b');
			tree.insert(7, 'k');
			tree.insert(9, 'l');
			keys = new int[5]{4,3,7,5,9};
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		TEST_METHOD(insert_6)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			keys = new int[6]{ 2,1,4,3,5,6 };
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		TEST_METHOD(remove_from6_1)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			tree.remove(5);
			keys = new int[5]{ 2,1,4,3,6 };
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		
		TEST_METHOD(remove_from6_2)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			tree.remove(5);
			tree.remove(4);
			keys = new int[4]{ 2,1,6,3 };
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		TEST_METHOD(remove_error)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			try
			{
				tree.remove(5);
				tree.remove(5);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Element not found", e.what());
			}
		}
		TEST_METHOD(remove_errorfromempty)
		{
			try
			{
				tree.remove(10);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Element not found", e.what());
			}
		}
		TEST_METHOD(find_from6)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			values = new char[6]{ 'c','a','b','k','l','z'};
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(tree.find(i+1), values[i]);
			}
		}
		TEST_METHOD(find_error)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			try
			{
				tree.find(7);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Element not found", e.what());
			}
		}
		TEST_METHOD(find_errorfromempty)
		{
			try
			{
				tree.find(0);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Element not found", e.what());
			}
		}
		TEST_METHOD(get_keys_6)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			keys = new int[6]{ 2,1,4,3,5,6 };
			keysTree = tree.get_keys();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(keys[i], keysTree[i]);
			}
		}
		TEST_METHOD(get_values_6)
		{
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			values = new char[6]{ 'a','c','k','b','l','z' };
			valuesTree = tree.get_values();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(values[i], valuesTree[i]);
			}
		}
		TEST_METHOD(clear_2)
		{
			tree.insert(5, 'c');
			tree.insert(4, 'a');
			tree.insert(3, 'b');
			tree.insert(7, 'k');
			tree.insert(9, 'l');
			tree.clear();
			tree.insert(7, 'k');
			tree.insert(9, 'l');
			values = new char[2]{ 'k','l'};
			valuesTree = tree.get_values();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(values[i], valuesTree[i]);
			}
		}
		TEST_METHOD(clear_6)
		{
			tree.insert(5, 'c');
			tree.insert(4, 'a');
			tree.insert(3, 'b');
			tree.insert(7, 'k');
			tree.insert(9, 'l');
			tree.clear();
			tree.insert(1, 'c');
			tree.insert(2, 'a');
			tree.insert(3, 'b');
			tree.insert(4, 'k');
			tree.insert(5, 'l');
			tree.insert(6, 'z');
			values = new char[6]{ 'a','c','k','b','l','z' };
			valuesTree = tree.get_values();
			for (size_t i = 0; i < tree.getSize(); i++)
			{
				Assert::AreEqual(values[i], valuesTree[i]);
			}
		}

	};
}
