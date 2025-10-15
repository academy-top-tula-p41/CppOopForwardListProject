#pragma once
#include <exception>
#include "IIterator.h"

template <typename T>
struct Node
{
	T value;
	Node<T>* next;
};

template <typename T>
class ForwardList;

template <typename T>
class ForwardListIterator : public IIterator<T>
{
	ForwardList<T>* forwardList;
	Node<T>* current;
public:
	ForwardListIterator(ForwardList<T>* forwardList)
		: forwardList{ forwardList } 
	{
		this->current = this->forwardList->Head();
	}

	void Setup() override;
	bool Next() override;
	T Current() override;
	bool IsEnd() override;

	Node<T>* CurrentNode();
	ForwardListIterator<T> operator+(size_t index);
};



template <typename T>
class ForwardList
{
	Node<T>* head;
	size_t size;
public:
	friend class ForwardListIterator<T>;

	ForwardList() : head{ nullptr }, size{} {}

	const size_t& Size() const;
	Node<T>* Head() const;

	void PushFront(T value);
	T PopFront();
	ForwardListIterator<T> Find(T value);
	ForwardListIterator<T> Insert(
		ForwardListIterator<T> iterator,
		T value);
	T Erase(ForwardListIterator<T> iterator);

	ForwardListIterator<T> GetIterator();

	void Clear();

	~ForwardList();
};

template<typename T>
inline const size_t& ForwardList<T>::Size() const
{
	return size;
}

template<typename T>
inline Node<T>* ForwardList<T>::Head() const
{
	return this->head;
}

template<typename T>
inline void ForwardList<T>::PushFront(T value)
{
	Node<T>* node = new Node<T>;
	node->next = head;
	node->value = value;

	head = node;
	size++;
}

template<typename T>
inline T ForwardList<T>::PopFront()
{
	if (size <= 0)
		throw new std::exception("empty forward list");

	T value = head->value;

	Node<T>* node = head;
	head = head->next;
	delete node;
	size--;

	return value;
}

template<typename T>
inline ForwardListIterator<T> ForwardList<T>::Find(T value)
{
	ForwardListIterator<T> iterator(this);
	for (; !iterator.IsEnd(); iterator.Next())
		if (iterator.Current() == value)
			return iterator;

	return iterator;
}

template<typename T>
inline ForwardListIterator<T> ForwardList<T>::Insert(ForwardListIterator<T> iterator, T value)
{
	Node<T>* node = new Node<T>;
	node->value = value;
	node->next = iterator.CurrentNode()->next;
	iterator.CurrentNode()->next = node;
	
	size++;
	iterator.Next();

	return iterator;
}

template<typename T>
inline T ForwardList<T>::Erase(ForwardListIterator<T> iterator)
{
	T value = iterator.CurrentNode()->next->value;
	Node<T>* node = iterator.CurrentNode()->next;
	iterator.CurrentNode()->next = iterator.CurrentNode()->next->next;

	delete node;
	size--;

	return value;
}

template<typename T>
inline ForwardListIterator<T> ForwardList<T>::GetIterator()
{
	return ForwardListIterator<T>(this);
}

template<typename T>
inline void ForwardList<T>::Clear()
{
	Node<T>* node;

	while (head)
	{
		node = head;
		head = head->next;
		delete node;
	}

	size = 0;
}

template<typename T>
inline ForwardList<T>::~ForwardList()
{
	Clear();
}


template<typename T>
inline void ForwardListIterator<T>::Setup()
{
	this->current = this->forwardList->Head();
}

template<typename T>
inline bool ForwardListIterator<T>::Next()
{
	this->current = this->current->next;		
	
	return this->current;
}

template<typename T>
inline T ForwardListIterator<T>::Current()
{
	return this->current->value;
}

template<typename T>
inline bool ForwardListIterator<T>::IsEnd()
{
	return !this->current;
}

template<typename T>
inline Node<T>* ForwardListIterator<T>::CurrentNode()
{
	return current;
}

template<typename T>
inline ForwardListIterator<T> ForwardListIterator<T>::operator+(size_t index)
{
	while (!this->IsEnd() && index) 
	{
		this->Next();
		index--;
	}
		
	return *this;
}
