#include <iostream>
using namespace std;
#ifndef _LINKEDLIST
#define _LINKEDLIST

#include"..\Restaurant\Generic_DS\Node.h"
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	int count;
public:
	LinkedList()
	{
		Head = nullptr;
		count = 0;
	}


	~LinkedList()
	{

	}
	//checking if the list is empty or not
	bool IsEmpty() {
		if (!Head) {
			return true;
		}
		return false;
	}
	//inserting a new node at the start of the list
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;
	}
	//inserts a new node at end if the list
	void InsertEnd(const T& data, int i) {
		Node<T>* Ptr = Head;
		Node<T>* New = new Node<T>(data, i);
		//if the list is empty
		if (!Head) {
			Head = New;
			count++;
			return;
		}
		//setting the last node at Ptr
		while (Ptr->getNext()) {
			Ptr = Ptr->getNext();
		}
		Ptr->setNext(New);
		New->setNext(NULL);
		count++;
	};
	//delete first node
	void DeleteFirst() {
		Node<T>* P = Head;
		Head = Head->getNext();
		P->setNext(NULL);
		delete P;
		P = NULL;
		count--;
	};
	//delete last node
	void DeleteLast() {
		if (!Head) return;
		if (!Head->getNext()) {
			delete Head;
			Head = nullptr;
			count--;
			return;
		}
		Node<T>* cur = Head;
		while (cur->getNext() && cur->getNext()->getNext() != nullptr) cur = cur->getNext();
		delete cur->getNext();
		cur->setNext(nullptr);
		count--;
	};
	//deleting a node
	bool DeleteNode(const T& value) {
		Node<T>* Prev = Head;
		Node<T>* Curr;
		Node<T>* Last = Head;
		bool Exit = true;
		//checking if it is the first node
		if (Head->getItem() == value) {
			DeleteFirst();
			return true;
		}
		while (Last->getNext()) {
			Last = Last->getNext();
		}
		if (Last->getItem() == value) {
			DeleteLast();
			return true;
		}
		while (Prev && Exit && (Prev != Last)) {
			if (Prev->getNext()->getItem() == value) {
				Exit = false;
			}
			else {
				Prev = Prev->getNext();
			}
		}
		if (Exit) {
			return false;
		}
		Curr = Prev->getNext();
		Prev->setNext(Curr->getNext());
		Curr->setNext(NULL);
		delete Curr;
		Curr = NULL;
		if (!Exit) {
			count--;
			return true;
		}
	};
	//deleting node from its ID
	bool Delete(int i) {
		Node<T>* Prev = Head;
		Node<T>* Curr;
		Node<T>* Last = Head;
		bool Exit = true;
		if (!Head)
			return false;
		//checking if it is the first node
		if (Head->GetID() == i) {
			DeleteFirst();
			return true;
		}
		while (Last->getNext()) {
			Last = Last->getNext();
		}
		if (Last->GetID() == i) {
			DeleteLast();
			return true;
		}
		while (Prev && Exit && (Prev != Last)) {
			if (Prev->getNext()->GetID() == i) {
				Exit = false;
			}
			else {
				Prev = Prev->getNext();
			}
		}
		if (Exit) {
			return false;
		}
		Curr = Prev->getNext();
		Prev->setNext(Curr->getNext());
		Curr->setNext(NULL);
		delete Curr;
		Curr = NULL;
		if (!Exit) {
			count--;
			return true;
		}
	};

	//to return the itemtype from it's id
	T GetFromID(int ID) {
		Node<T>* ptr = Head;
		while (ptr) {
			if (ptr->GetID() == ID) {
				return ptr->getItem();
			}
			ptr = ptr->getNext();
		}
		return NULL;
	}

	//get the number of the list items
	int getCount() const {
		return count;
	}

	T* toArray() {
		if (!Head) return nullptr;
		Node<T>* p = Head;
		if (count < 0)
			return nullptr;
		T* Arr = new T[count];
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	bool peekHead(T& data) {  //as a queue did.
		if (!Head) return false;
		data = Head->getItem();
		DeleteFirst();
		return true;
	}

	//bool dequeueFirst(T& data)
	//{
	//	if (Head)
	//	{
	//		data = Head->getItem();
	//		if (Head->getNext())
	//		{

	//			Node<T>* nptr = Head;
	//			Head = Head->getNext();
	//			nptr->setNext(nullptr);
	//			delete nptr;

	//		}
	//		else
	//			Head = nullptr;
	//		return true;
	//	}
	//	return false;
	//}
};




#endif

