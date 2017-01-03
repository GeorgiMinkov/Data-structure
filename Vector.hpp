#pragma once
#include <iostream>

template <typename Type>
class Vector
{
	Type *container;
	std::size_t currentSize;
	std::size_t capacity;

	void resize();
	void copy(const Type *container, const std::size_t &currentSize, const std::size_t &capacity);
	void destroy();

	const std::size_t defaultValue = 8;
public:
	Vector();
	Vector(const Type *container, const int &size, const int &capacity);
	Vector(const Vector<Type> &other);
	~Vector();

	Vector<Type> &operator=(const Vector<Type> &other);

	// Capacity
	int size() const;
	bool empty() const;

	// Element access
	Type &operator[](const int  &index);
	Type &at(const int &index);
	Type &front();
	Type &back();

	// Modifiers
	void push_back(const Type &value);
	void pop_back();
};

template<typename Type>
inline void Vector<Type>::resize()
{
	int newCapacity = 2 * this->capacity;
	Type *tmpContainer = new Type[newCapacity];

	for (std::size_t index = 0; index < this->capacity; ++index)
	{
		tmpContainer[index] = this->container[index];
	}

	delete[] this->container;

	this->container = tmpContainer;
	this->capacity = newCapacity;
}

template<typename Type>
inline void Vector<Type>::copy(const Type * container, const std::size_t & currentSize, const std::size_t & capacity)
{
	this->container = new Type[capacity];
	this->currentSize = currentSize;
	this->capacity = capacity;

	for (std::size_t index = 0; index < currentSize; ++index)
	{
		this->container[index] = container[index];
	}
}

template<typename Type>
inline void Vector<Type>::destroy()
{
	delete[] this->container;
}

template<typename Type>
inline Vector<Type>::Vector()
{
	this->container = new Type[this->defaultValue];
	this->currentSize = 0;
	this->capacity = this->defaultValue;
}

template<typename Type>
inline Vector<Type>::Vector(const Type * container, const int & size, const int & capacity)
{
	this->copy(container, size, capacity);
}

template<typename Type>
inline Vector<Type>::Vector(const Vector<Type>& other)
{
	this->copy(other.container, other.currentSize, other.capacity);
}

template<typename Type>
inline Vector<Type>::~Vector()
{
	delete[] this->container;
}

template<typename Type>
inline Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other)
{
	// DO: operator=
	if (this != &other)
	{
		this->destroy();

		this->copy(other.container, other.currentSize, other.capacity);
	}

	return *this;
}

template<typename Type>
inline int Vector<Type>::size() const
{
	return this->currentSize;
}

template<typename Type>
inline bool Vector<Type>::empty() const
{
	return this->currentSize == 0;
}

template<typename Type>
inline Type & Vector<Type>::operator[](const int & index)
{
	// DO: operator[]
	if (index < 0 || index >= this->currentSize)
	{
		throw "IndexException";
	}

	return this->container[index];
}

template<typename Type>
inline Type & Vector<Type>::at(const int & index)
{
	// DO: function .at()
	if (index < 0 || index >= this->currentSize)
	{
		throw "IndexException";
	}

	return this->container[index];
}

template<typename Type>
inline Type & Vector<Type>::front()
{
	if (this->currentSize == 0)
	{
		throw "EmptyVectorException";
	}

	return this->container[0];
}

template<typename Type>
inline Type & Vector<Type>::back()
{
	if (this->currentSize == 0)
	{
		throw "EmptyVectorException";
	}

	return this->container[this->currentSize - 1];
}

template<typename Type>
inline void Vector<Type>::push_back(const Type & value)
{
	if (this->currentSize == this->capacity)
	{
		this->resize();
	}

	this->container[this->currentSize++] = value;
}

template<typename Type>
inline void Vector<Type>::pop_back()
{
	if (this->currentSize == 0 || this->currentSize == -1)
	{
		throw "EmptyVectorException";
	}

	--(this->size);
}
