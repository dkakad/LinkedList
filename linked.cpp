/*
* An implementation of a generic LinkedList class which constructs a doubly linked list
* where each Node of the Linked List is the generic Node class defined in the headers.
* This Linked List consists of 2 fields:
* size -> The current size of the Linked List.
* head -> The pointer to the head Node of this Linked List.
* @author Deepak Kakad
*/

#include "linked.h"
#include <set>

template class LinkedList<int>;
template class Node<int>;
/*
 * Default constructor of the LinkedList class.
 */
template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	size = 0;
}

/*
 * A private helper function that returns the tail of the Linked List.
 * This function assumes that the next Node of tail is nullptr.
 * @return temp -> The tail of the Linked List.
 */
template <typename T>
Node<T>* LinkedList<T>::getLast() {
	Node<T> *temp = head;
	while (temp->getNext() != nullptr) {
		temp = temp->getNext();
	}
	return temp;
}

/*
 * A function that inserts a Node at the end of the Linked List.
 * @param newNode -> A pointer to the node to be inserted.
 */
template <typename T>
void LinkedList<T>::insertEnd(Node<T> *newNode) {
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node<T> *temp = getLast();
		temp->setNext(newNode);
		newNode->setNext(nullptr);
		newNode->setPrev(temp);
	}
	size++;
}

/*
 * A function that inserts a Node at the start of the Linked List.
 * @param newNode -> A pointer to the node to be inserted.
 */
template <typename T>
void LinkedList<T>::insertStart(Node<T> *newNode) {
	if (head == nullptr) {
		head = newNode;
		return;
	}
	newNode->setNext(head);
	newNode->setPrev(nullptr);
	head->setPrev(newNode);
	head = newNode;
	size++;
}

/*
 * A function that inserts a Node at the middle of the Linked List.
 * @param toInsert -> A pointer to the node to be inserted.
 * @param atPosition -> A pointer to the node AFTER which we want to insert.
 */
template <typename T>
void LinkedList<T>::insertMiddle(Node<T> *toInsert, Node<T> *atPosition) {
	if (atPosition == head) {
		insertStart(toInsert);
		size++;
		return;
	}
	Node<T> *temp = getLast();
	if (atPosition == temp) {
		insertEnd(toInsert);
		size++;
		return;
	}
	Node<T> *nextNode = atPosition->getNext();
	atPosition->setNext(toInsert);
	toInsert->setPrev(atPosition);
	toInsert->setNext(nextNode);
	nextNode->setPrev(toInsert);
	size++;
}

/*
 * A function that deletes the last Node of the Linked List.
 */
template <typename T>
void LinkedList<T>::deleteEnd() {
	if (head == nullptr) {
		return;
	}
	Node<T> *end = getLast();
	if (end == head) {
		head = nullptr;
		size--;
		return;
	}
	Node<T> *prevNode = end->getPrev();
	prevNode->setNext(nullptr);
	delete end;
	size--;
}

/*
 * A function that deletes the first Node of the Linked List.
 */
template <typename T>
void LinkedList<T>::deleteStart() {
	if (head == nullptr) {
		return;
	}
	Node<T> *end = getLast();
	if (end == head) {
		head = nullptr;
		size--;
		return;
	}
	Node<T> *nextNode = head->getNext();
	nextNode->setPrev(nullptr);
	delete head;
	size--;
	head = nextNode;
}

/*
 * A function that deletes a Node in the middle of the Linked List.
 * @param atPosition -> The Node that is to be deleted.
 */
template <typename T>
void LinkedList<T>::deleteMiddle(Node<T> *atPosition) {
	if (head == nullptr || atPosition == nullptr) {
		return;
	}
	Node<T> *end = getLast();
	if (end == head) {
		head = nullptr;
		size--;
		return;
	}
	if (atPosition == head) {
		deleteStart();
		size--;
		return;
	}
	if (atPosition == end) {
		deleteEnd();
		size--;
		return;
	}
	Node<T> *prevNode = atPosition->getPrev();
	Node<T> *nextNode = atPosition->getNext();
	prevNode->setNext(nextNode);
	nextNode->setPrev(prevNode);
	size--;
	delete atPosition;
}

/*
 * A function that removes the duplicate nodes (by data) in the Linked List.
 * @param space -> A variable to select the mode of removing dups; 
 *				  true for space optimization, false for speed.
 */
template <typename T>
void LinkedList<T>::removeDups(bool space) {
	/*
	* Using sets for computational speed
	*/
	std::set<T> unique;
	Node<T> *temp = head;
	if (!space) {
		while (temp != nullptr) {
			if (unique.count(temp->getData()) == 0) {
				unique.insert(temp->getData());
			}
			else {
				Node<T> *temp1 = temp->getPrev();
				deleteMiddle(temp);
				temp = temp1;
			}
			temp = temp->getNext();
		}
	}
	/*
	* For space efficiency
	*/
	else {
		while (temp != nullptr) {
			Node<T> *temp1 = temp->getNext();
			while (temp1 != nullptr) {
				if (temp1->getData() == temp->getData()) {
					Node<T> *temp2 = temp1->getPrev();
					deleteMiddle(temp1);
					temp1 = temp2;
				}
				temp1 = temp1->getNext();
			}
			temp = temp->getNext();
		}
	}
}

/*
 * A function that returns the number of Nodes in the Linked List.
 * @return size -> The size of the Linked List.
 */
template <typename T>
int LinkedList<T>::getSize() {
	Node<T> *temp = head;
	int size = 0;
	while (temp != nullptr) {
		size++;
		temp = temp->getNext();
	}
	return size;
}

/*
 * A function that returns the k'th element from last of the Linked List.
 * @param k -> The number of Nodes before the last element to be returned.
 * @return head -> The k'th element from last.
 */
template <typename T>
Node<T> * LinkedList<T>::kToLast(int k) {
	Node<T> *temp = head;
	int size = getSize();
	if (k > size) {
		printf("k greater than size. Returning nullptr \n");
		return nullptr;
	}
	for (int i = 0; i < k; i++) {
		temp = temp->getNext();
	}
	Node<T> *runner = temp;
	temp = head;
	while (runner != nullptr) {
		head = head->getNext();
		runner = runner->getNext();
	}
	return head;
}

/*
 * A function that partitions the Linked List around a data value such that 
 * the nodes whose data value is less than the given value are always before the
 * nodes that are greater than the given value in the Linked List.
 * @param data -> The data value around which we want to partition the Linked List.
 */
template <typename T>
void LinkedList<T>::partition(T data) {
	Node<T> *temp = head;
	for (int i = 0; i < getSize(); i++) {
		if (temp->getData() < data) {
			Node<T> *curr = new Node<T>(temp->getData());
			Node<T> *temp1 = temp;
			temp = temp->getNext();
			deleteMiddle(temp1);
			insertStart(curr);
		}
		else {
			Node<T> *curr = new Node<T>(temp->getData());
			Node<T> *temp1 = temp;
			temp = temp->getNext();
			deleteMiddle(temp1);
			insertEnd(curr);
		}
	}
}

/*
 * A function that reverses the Linked List.
 */
template <typename T>
void LinkedList<T>::reverse() {
	if (head == nullptr) {
		printf("Head is nullptr. Returning nullptr \n");
		return;
	}
	Node<T> *start = head;
	Node<T> *curr = head;
	Node<T> *succ = curr->getNext();

	while (succ != nullptr) {
		Node<T> *temp = new Node<T>(curr->getData());
		insertStart(temp);
		deleteMiddle(curr);
		curr = succ;
		succ = curr->getNext();
	}
	Node<T> *temp = new Node<T>(curr->getData());
	insertStart(temp);
	deleteMiddle(curr);
}

/*
* A function that prints the Linked List. Note that we can use printf only
* because it clearly defines a method to print integers. To truly create a function
* for printing a generic node data, we must use cout and onverload the "<<" operator
* to define the way in which we want the Linked List to be printed.
*/
template <typename T>
void LinkedList<T>::printList() {
	Node<T> *n = head;
	if (n == nullptr) {
		printf("NULL \n");
	}
	while (n->getNext() != nullptr) {
		printf("%d -> ", n->getData());
		n = n->getNext();
	}
	printf("%d -> NULL \n", n->getData());
	printf("Size of Linked List is: %d \n", getSize());
}
