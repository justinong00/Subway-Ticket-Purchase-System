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
		QueueFront = nullptr;
		QueueRear = nullptr;
		count = 0;
	}
	void enqueue(T elem) {
		QueueNode<T> *newNode = new QueueNode<T>;
		newNode->data=elem;
		newNode->link=nullptr;
		if (QueueRear == nullptr) {
			QueueFront=QueueRear=newNode;
		}else {
			QueueRear->link = newNode;
			QueueRear = newNode;
		}
		count++;
	}
	void dequeue() {
		QueueNode<T> *Temp = QueueFront;
		if (QueueFront == NULL) {
			cout << "The list is empty" << endl;
			return;
		} else if (Temp->link != NULL) {
			Temp = Temp->link;
			QueueFront = Temp;
			count = count - 1;
		} else {
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
	T getHead(){
		if(QueueFront==nullptr){
			cerr << "Queue is Empty" << endl;
		}else{
			return QueueFront->data;
		}
	}
};


#endif /* QUEUE_H_ */
