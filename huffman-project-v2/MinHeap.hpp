#pragma once
#include "Vector.hpp"

template <typename Type>
class MinHeap
{
	Vector<Type> container;

	void heapDown(int index);
	void heapUp(int index);
	void heapify();

	void swap(Type &lhs, Type &rhs);
	// bool compare(const Type &lhs, const Type &rhs);
public:
	MinHeap() { };
	MinHeap(const Type *arr, const std::size_t &size);
	MinHeap(const Vector<Type> &src);

	Type top() const;

	void pop();
	void push(const Type &element);
	
	std::size_t size() const;
};

template <typename Type>
bool compare(Type *lhs, Type *rhs)
{
	return *lhs > *rhs;
}

template<typename Type>
inline void MinHeap<Type>::heapDown(int index)
{
	std::size_t size = this->container.size();
	std::size_t leftChildIndex = 2 * index + 1, rightChildIndex = 2 * index + 2;

	if (leftChildIndex >= size) // when the element on that index is leaf
	{
		return;
	}

	int minIndex = index;

	if (compare(this->container[minIndex], this->container[leftChildIndex]))
	{
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex < size) && compare(this->container[minIndex], this->container[rightChildIndex]))
	{
		minIndex = rightChildIndex;
	}

	if (minIndex != index)
	{
		this->swap(this->container[minIndex], this->container[index]);

		this->heapDown(minIndex);
	}
}

template<typename Type>
inline void MinHeap<Type>::heapUp(int index)
{
	if (index == 0) // this is top so no need for change, base for recursion
	{
		return;
	}

	std::size_t parentIndex = (index - 1) / 2;

	if (compare(this->container[parentIndex], this->container[index]))
	{
		this->swap(this->container[parentIndex], this->container[index]);

		this->heapUp(parentIndex);
	}
}

template<typename Type>
inline void MinHeap<Type>::heapify()
{
	for (int index = this->container.size() - 1; index >= 0; --index)
	{
		this->heapDown();
	}
}

template<typename Type>
inline void MinHeap<Type>::swap(Type & lhs, Type & rhs)
{
	Type tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}
//
//template<typename Type = Node>
//inline bool MinHeap<Type>::compare(Type * lhs, Type * rhs)
//{
//	return *lhs > *rhs;
//}

//template<typename Type>
//inline bool MinHeap<Type>::compare(const Type & lhs, const Type & rhs)
//{
//	return lhs > rhs;
//}

template<typename Type>
inline MinHeap<Type>::MinHeap(const Type * arr, const std::size_t &size)
{
	for (std::size_t index = 0; index < size; ++index)
	{
		this->container[index] = arr[index];
	}

	this->heapify();
}

template<typename Type>
inline MinHeap<Type>::MinHeap(const Vector<Type>& src) : container(src)
{
	this->heapify();
}

template<typename Type>
inline Type MinHeap<Type>::top() const
{
	if (this->container.empty())
	{
		throw "EmptyHeapException";
	}

	return this->container[0];
}

template<typename Type>
inline void MinHeap<Type>::pop()
{
	if (this->container.empty())
	{
		throw "EmptyHeapException";
	}

	this->container[0] = this->container[this->container.size() - 1];

	this->container.pop_back();

	this->heapDown(0);
}

template<typename Type>
inline void MinHeap<Type>::push(const Type & element)
{
	std::size_t size = this->container.size();

	this->container.push_back(element);

	this->heapUp(size);
}

template<typename Type>
inline std::size_t MinHeap<Type>::size() const
{
	return this->container.size();
}
