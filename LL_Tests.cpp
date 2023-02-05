//just a file to test linked list methods.

#include <iostream>
#include "LL.h"

void printList(LL<int> l)
{
	for (auto i = l.begin(); i != l.end(); i++)
		std::cout << *i << " ";

	std::cout << "\n";

	return;
}

int main()
{
	LL<int> list1;

	for (int i = 0; i < 5; i++)
		list1.tailInsert(i + 1);

	LL<int> list2(list1);

	list1.headInsert(12);
	list2.tailInsert(11);

	printList(list1);
	printList(list2);

	LL<int> list3;

	list3 = list2;

	list3.tailInsert(33);
	list2.headInsert(16);

	printList(list2);
	printList(list3);

	list1 = list2;

	list1.headInsert(18);

	printList(list1);
	printList(list2);

	return 0;
}