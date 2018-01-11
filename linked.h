/*
 * An implementation of a generic LinkedList class which constructs a doubly linked list
 * where each Node of the Linked List is the generic Node class defined in the headers.
 * This Linked List consists of 2 fields:
 * size -> The current size of the Linked List.
 * head -> The pointer to the head Node of this Linked List.
 * @author Deepak Kakad
 */

#pragma once
#include "node.h"
#include "node.cpp"

template <typename T>
class LinkedList {
	/*
	 * A private helper member function.
	 */
	Node<T> *getLast();

	/*
	 * The number of Nodes in the Linked List.
	 */
	int size;
public:
	/*
	 * The head Node of the Linked List.
	 */
	Node<T> *head;
	LinkedList();
	void insertEnd(Node<T> *newNode);
	void insertStart(Node<T> *newNode);
	void insertMiddle(Node<T> *toInsert, Node<T> *atPosition);
	void deleteEnd();
	void deleteStart();
	void deleteMiddle(Node<T> *atPosition);
	void removeDups(bool space);
	Node<T> *kToLast(int k);
	int getSize();
	void partition(T data);
	void reverse();
	void printList();
};