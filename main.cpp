#include <iostream>
#include "JumpList.h"
using namespace std;

int main() {
	JumpList list;
	cout << "Empty list:" << endl;
	cout << list.size() << endl;
	cout << list.find("a") << endl;
	cout << list.get(0) << endl;
	cout << list.print() << endl;

	cout << "------------------------" << endl;

	cout << "insert to empty list:" << endl;
	list.insert("b");
	list.insert("a");
	list.insert("d");
	list.insert("c");
	list.insert("e");
	cout << list.size() << endl;
	cout << list.find("b") << endl;
	cout << list.find("f") << endl;
	cout << list.get(6) << endl;
	cout << list.print() << endl;

	list.insert("f");
	cout << list.print() << endl;

	cout << "------------------------" << endl;

	cout << "erase from running example:" << endl;
	JumpList example(10);
	cout << example.print() << endl;
	example.erase("blah");
	cout << example.print() << endl;

	return 0;

}