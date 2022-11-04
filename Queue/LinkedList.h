//
// Created by chanw on 28/09/2022.
//

#ifndef DSTR_ASSIGNMENT_LINKEDLIST_H
#define DSTR_ASSIGNMENT_LINKEDLIST_H

//preprocessor directive
#include <iostream>
#include <stdexcept>
#include "Ticket.h"
#include <string.h>

using namespace std;

template<class T>
class LLNode{
public:
    T val;
    LLNode<T> * next;
};

template<class T>
class LinkedList{
public:
    LLNode<T> * head;
    LLNode<T> * tail;
    int size;

    LinkedList()
    {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

//    Methods
    T get(int index)
    {
        LLNode<T> * targetNode = atIndex(index);
        return targetNode->val;
    }

    T getFirst()
    {
        return head->val;
    }

    T getLast()
    {
        return tail->val;
    }

    int getSize()
    {
        return size;
    }

    void insertFirst(T data)
    {
        auto * newNode = new LLNode<T>;
        newNode->val = data;
        newNode->next = head;
        head = newNode;
        size ++;
        if (tail == nullptr)
            tail = newNode;
    }

    void insertLast(T data)
    {
        auto * newNode = new LLNode<T>;
        newNode->val = data;
        newNode->next = nullptr;

        if(head == nullptr)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size ++;
    }

    void insertAt(int index, T data)
    {
        if (index == 0)
        {
            insertFirst(data);
            return;
        }
        else
        {
            LLNode<T> * currentNode = atIndex(index);
            LLNode<T> * prevNode = atIndex(index - 1);

            auto newNode = new LLNode<T>;
            newNode->val = data;
            newNode->next = currentNode;
            prevNode->next = newNode;
            size ++;
            return;
        }
    }

    void deleteFirst()
    {
        if (size <= 0) throw invalid_argument("Linked list is empty");
        LLNode<T> * targetNode = head;
        head = head->next;
        delete targetNode;
        size --;
        if (head == nullptr)
            tail = nullptr;
    }

    void deleteLast()
    {
        if (size <= 0) throw invalid_argument("Linked list is empty");
        LLNode<T> * targetNode = head;
        while (targetNode->next != nullptr)
        {
            tail = targetNode;
            targetNode = targetNode->next;
        }
        delete targetNode;
        tail->next = nullptr;
        size --;
    }

    void deleteAt(int index)
    {
        if (size <= 0) throw invalid_argument("Linked list is empty");
        if (index == 0)
        {
            deleteFirst();
            return;
        }
        else if (index == size - 1)
        {
            deleteLast();
            return;
        }
        else
        {
            LLNode<T> * currentNode = atIndex(index);
            LLNode<T> * prevNode = atIndex(index - 1);

            prevNode->next = currentNode->next;
            delete currentNode;
            size --;
            return;
        }
    }

    void show()
    {
        LLNode<T> * currentNode = head;
        while (currentNode != nullptr)
        {
            cout << currentNode->val << ", ";
            currentNode = currentNode->next;
        }
    }

    //Method overload, method body defined outside of class, NEW
    int getIndex(string TransID){return 0;}

    //Method overload, method body defined outside of class
    void showByCusID(int CusID){};

    //Method overload, method body defiend outside of class
    void sortNameAsc(){};

    //Method overload, method body defined outside of class
    void sortByTransID(){};

    //Method overload, method body defined outside of class
    void Modify(string TransID, string source, string dest, double amount, string dt){};

private:
    LLNode<T> * atIndex(int index)
    {
        LLNode<T> * targetNode = head;

        if (index < 0 || index > size - 1) throw invalid_argument("Invalid index provided");

        if (index == 0) return targetNode;

        while (index > 0)
        {
            targetNode = targetNode->next;
            index --;
        }
        return targetNode;
    }
};

// template<> void LinkedList<Song>::show()
// {
//     LLNode<Song> * curr = head;
//     while (curr != nullptr)
//     {
//         cout << curr->val.artist << ", " << curr->val.name << ", " << curr->val.genre << endl;
//         curr = curr->next;
//     }
// }


//To view all Transaction and Ticket Details (for admins)
template<>
void LinkedList<Ticket>::show()
{
	LLNode<Ticket> * curr = head;
	while (curr != nullptr)
	{
		cout << curr->val.getTrID() << "\t\t" << curr->val.getTkID() << "\t\t" << curr->val.getSource() << "\t" << curr->val.getDest() << "\t"
				<< curr->val.getAmount() << "\t\t" << curr->val.getDepartT() << "\t\t" <<curr->val.getCusID() << "\t\t" << curr->val.getCusName()
				<< "\t\t" << curr->val.getCusIC() << "\t\t" << curr->val.getTransDT();
		curr=curr->next;
	}
}

//To view all Transaction and Ticket Details by Customer ID
template<>
void LinkedList<Ticket>::showByCusID(int CusID)
{
	bool found = false;
	LLNode<Ticket> * curr = head;
	while (curr != nullptr)
	{
		if (curr->val.getCusID()==CusID)
		{
			found=true;
			cout << curr->val.getTrID() << "\t\t" << curr->val.getTkID() << "\t\t" << curr->val.getSource() << "\t" << curr->val.getDest() << "\t"
					<< curr->val.getAmount() << "\t\t" << curr->val.getDepartT() << "\t\t" << curr->val.getCusID() << "\t\t" << curr->val.getCusName()
					<< "\t\t" << curr->val.getCusIC() << "\t\t" << curr->val.getTransDT();
		}
		curr=curr->next;
	}
	if (found==false){
		cerr << "Customer ID not found " <<endl;
	}
}

//To find the index of specific transaction using Transaction ID
template<>
int LinkedList<Ticket>::getIndex(string TransID)
{
	int index=0;
	LLNode<Ticket> * curr=head;
	while (curr!=nullptr)
	{
		if(curr->val.getTrID()==TransID)
		{
			return index;
		}
		curr=curr->next;
		index++;
	}
	//If Transaction not found
	return -1;
}

//To sort the Ticket linked list in ascending order of Name
template<>
void LinkedList<Ticket>::sortNameAsc()
{
	LLNode<Ticket> * curr = new LLNode<Ticket>;
	Ticket Temp;
	LLNode<Ticket> * index = new LLNode<Ticket>;
	if(head==nullptr)
	{
		return;
	}else
	{
		for (curr = head; curr->next != nullptr; curr = curr->next)
		{
			for (index = curr->next; index != nullptr; index = index->next)
			{
				string str1 = curr->val.getCusName();
				string str2 = index->val.getCusName() ;
				int result = str1.compare(str2);
				if(result>0)
				{
					Temp = curr->val;
					curr->val = index->val;
					index->val = Temp;
				}
			}
		}
	}
}

//To sort the Ticket Linked List in ascending order of Transaction ID
template<>
void LinkedList<Ticket>::sortByTransID()
{
	LLNode<Ticket> * curr = new LLNode<Ticket>;
	Ticket Temp;
	LLNode<Ticket> * index = new LLNode<Ticket>;
	if(head==nullptr)
	{
		return;
	}else
	{
		for (curr = head; curr->next != nullptr; curr = curr->next)
		{
			for (index = curr->next; index != nullptr; index = index->next)
			{
				string str1 = curr->val.getTrID();
				string str2 = index->val.getTrID() ;
				int result = str1.compare(str2);
				if(result>0)
				{
					Temp = curr->val;
					curr->val = index->val;
					index->val = Temp;
				}
			}
		}
	}
}


//To Modify Ticket details
template<>
void LinkedList<Ticket>::Modify(string TransID, string source, string dest, double amount, string dt)
{
	bool found = false;
	LLNode<Ticket> * curr = head;
	while (curr != nullptr)
	{
		if(curr->val.getTrID()==TransID)
		{
			found=true;
			curr->val.setSource(source);
			curr->val.setDest(dest);
			curr->val.setTAmount(amount);
			curr->val.setDepartT(dt);
			cout << "Ticket Details Modified" << endl;
			break;
		}
		curr=curr->next;
	}
	if (found==false){
		cerr << "Ticket Not Found" << endl;
	}
}

#endif //DSTR_ASSIGNMENT_LINKEDLIST_H
