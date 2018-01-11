#include "linked.h"
#include "linked.cpp"

/* 
 * Start of main Function
 */


int main() {
	LinkedList<int> *l = new LinkedList<int>();
	Node<int> *n1 = new Node<int>(3);
	Node<int> *n2 = new Node<int>(5);
	Node<int> *n3 = new Node<int>(8);
	Node<int> *n4 = new Node<int>(5);
	Node<int> *n5 = new Node<int>(10);
	Node<int> *n6 = new Node<int>(2);
	Node<int> *n7 = new Node<int>(1);
	l->insertEnd(n1);
	l->insertEnd(n2);
	l->insertEnd(n3);
	l->insertEnd(n4);
	l->insertEnd(n5);
	l->insertEnd(n6);
	l->insertEnd(n7);

	l->partition(5);
	

	l->printList();
	l->reverse();
	printf("Printing Reversed Linked List \n");
	l->printList();

	return 0;
}