/*
 * Queue.h
 *
 *  Created on: 31 Oct 2022
 *      Author: shaun
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>

using namespace std;

template<typename T> //abstract type
class QueueNode {
public:
	T data;
	QueueNode<T> *link;
};
template<typename T>
class Queue {
	QueueNode<T> *QueueFront; //queue's first element/node(head)
	QueueNode<T> *QueueRear; //queue's last element/node (tail)
	int count; //the number of elements in the queue
public:
	Queue() {
		QueueFront = NULL;
		QueueRear = NULL;
		count = 0;
	}
	void enqueue(T elem) {
		QueueNode<T> *newNode = new QueueNode<T>;
		if (QueueRear == NULL) {
			newNode->link = NULL;
			QueueRear->link = newNode;
			QueueFront = QueueRear;
			count = count + 1;
		} else {
			newNode->link = NULL;
			QueueRear->link = newNode;
			QueueRear = newNode;
			count = count + 1;
		}
	}
	void dequeue() {
		QueueNode<T> *Temp = QueueFront;
		if (QueueFront == NULL) {
			cout << "The list is empty" << endl;
			return;
		} else if (Temp->link != NULL) {
			Temp = Temp->link;
			cout << "Element deleted from queue is : " << QueueFront->data
					<< endl;
			QueueFront = Temp;
			count = count - 1;
		} else {
			cout << "Element deleted from queue is : " << QueueFront->data
					<< endl;
			QueueFront = NULL;
			QueueRear = NULL;
			count = count - 1;
		}
	}
	void ShowQueue() {
		QueueNode<T> *Temp = QueueFront;
		if ((QueueFront == NULL) && (QueueRear == NULL)) {
			cout << "Queue is Empty" << endl;
			return;
		}
		cout << "Queue elements are : ";
		while (Temp != NULL) {
			cout << Temp->data << endl;
			Temp = Temp->link;
		}
	}
	int size() {
		return count;
	}
};


#endif /* QUEUE_H_ */
