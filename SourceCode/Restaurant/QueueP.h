#ifndef __QUEUEP_H_
#define __QUEUEP_H_
#include "NodeP.h"

template <typename T>
class QueueP
{
private:

    NodeP<T>* frontPtr;
public:
    QueueP();
    bool isEmpty() const;
    void enqueue(T& it, int pr);
	int getCount();
    bool dequeue(T& frntEntry);
    bool peekFront(T& frntEntry)  const;
    T* toArray();
    ~QueueP();
};

template <typename T>
void QueueP<T>::enqueue(T& it, int pr)
{
	NodeP<T>* newNodePtr = new NodeP<T>;
	newNodePtr->setItem(it);
	newNodePtr->setp(pr);
	if(frontPtr == nullptr || pr < frontPtr->getp())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else {
		NodeP <T>* ptr = frontPtr;
		while (ptr ->getNext () != nullptr && pr <= ptr->getNext()->getp())
		  ptr = ptr->getNext();   
		newNodePtr->setNext(ptr->getNext());
		ptr->setNext(newNodePtr);
	}
}

template <typename T>
QueueP<T>::QueueP()
{
    frontPtr = nullptr;

}

template <typename T>
bool QueueP<T>::isEmpty() const
{
    if (frontPtr == nullptr)
        return true;
    else
        return false;
}
template <typename T>
bool QueueP<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodeP<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	delete nodeToDeletePtr;
	return true;

}
template <typename T>
bool QueueP<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;
	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
QueueP<T>::~QueueP()
{
}

template <typename T>
T* QueueP<T>::toArray()
{
	int count = 0;
	if (!frontPtr)
		return nullptr;
	NodeP<T>* ptr = frontPtr;
	while (ptr)
	{
		count++;
		ptr = ptr->getNext();
	}
	T* Arr = new T[count];
	ptr = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = ptr->getItem();
		ptr = ptr->getNext();
	}
	return Arr;
}

template <typename T>
int QueueP<T>::getCount() {
	int count = 0;
	NodeP<T>* ptr = frontPtr;
	while (ptr)
	{
		count++;
		ptr = ptr->getNext();
	}
	return count;
}
#endif