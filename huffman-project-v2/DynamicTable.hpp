#pragma once
#include "Pair.hpp"
#include "Vector.hpp"

template <typename FirstType = char, typename SecondType = std::size_t>
class DynamicTable
{
	Vector<Pair<FirstType, SecondType>> container;

	const std::size_t defaultASCII = 256;
public:
	DynamicTable()
	{
		Pair<FirstType, SecondType> *container = new Pair<FirstType, SecondType>[defaultASCII];

		Vector<Pair<FirstType, SecondType>> tmp(container, defaultASCII, defaultASCII);

		this->container = tmp;
	}
	DynamicTable(const Vector<Pair<FirstType, SecondType>> &container) 
		: container(container) { }

	DynamicTable &operator=(const DynamicTable<FirstType, SecondType> &other);

	Pair<FirstType, SecondType> &operator[](const int &index);
	Pair<FirstType, SecondType> at(const int &index) const;
	
	std::size_t getSize() const;

	void deleteZeros(); // идеята на динамичната таблиза е, че след направата на честотна таблица всички нули ще изчезнат
	void deleteNullStr();
	void putCharsAndZeros();
	void putCharsAndBlank();
};

template<typename FirstType, typename SecondType>
inline DynamicTable<FirstType, SecondType> & DynamicTable<FirstType, SecondType>::operator=(const DynamicTable<FirstType, SecondType>& other)
{
	// DO: operator=
	if (this != &other)
	{
		this->container = other.container;
	}

	return *this;
}

template<typename FirstType, typename SecondType>
inline Pair<FirstType, SecondType> & DynamicTable<FirstType, SecondType>::operator[](const int & index)
{
	// DO: operator[]
	return this->container[index]; // Не са нужни изключения заради предефиницията на оператор[] във вектор
}

template<typename FirstType, typename SecondType>
inline Pair<FirstType, SecondType> DynamicTable<FirstType, SecondType>::at(const int & index) const
{
	return this->container[index];
}

template<typename FirstType, typename SecondType>
inline std::size_t DynamicTable<FirstType, SecondType>::getSize() const
{
	return this->container.size();
}

template<typename FirstType, typename SecondType>
inline void DynamicTable<FirstType, SecondType>::deleteZeros()
{
	std::size_t tmpIndex = 0;

	Pair<FirstType, SecondType> *container;

	// find how many non-zeros there are
	for (std::size_t index = 0; index < this->container.size(); ++index)
	{
		if (this->container[index].secondArgument != 0)
		{
			++tmpIndex;
		}
	}

	container = new Pair<FirstType, SecondType>[tmpIndex];

	Vector<Pair<FirstType, SecondType>> tmp(container, tmpIndex, tmpIndex);

	tmpIndex = 0;

	for (std::size_t index = 0; index < this->container.size(); ++index)
	{
		if (this->container[index].secondArgument != 0)
		{
			tmp[tmpIndex++] = this->container[index];
		}
	}

	this->container = tmp;
}

template<typename FirstType, typename SecondType>
inline void DynamicTable<FirstType, SecondType>::deleteNullStr()
{
	std::size_t tmpIndex = 0;

	Pair<FirstType, SecondType> *container;

	// find how many non-zeros there are
	for (std::size_t index = 0; index < this->container.size(); ++index)
	{
		if (this->container[index].secondArgument != "")
		{
			++tmpIndex;
		}
	}

	container = new Pair<FirstType, SecondType>[tmpIndex];

	Vector<Pair<FirstType, SecondType>> tmp(container, tmpIndex, tmpIndex);

	tmpIndex = 0;

	for (std::size_t index = 0; index < this->container.size(); ++index)
	{
		if (this->container[index].secondArgument != "")
		{
			tmp[tmpIndex++] = this->container[index];
		}
	}

	this->container = tmp;
}

template<typename FirstType, typename SecondType>
inline void DynamicTable<FirstType, SecondType>::putCharsAndZeros()
{
	if (typeid(FirstType) != typeid(char))
	{
		return;
	}

	for (std::size_t index = 0; index < this->defaultASCII; ++index)
	{
		this->container[index].firstArgument = (char)index;
		this->container[index].secondArgument = 0;
	}
}

template<typename FirstType, typename SecondType>
inline void DynamicTable<FirstType, SecondType>::putCharsAndBlank()
{
	if (typeid(FirstType) != typeid(char) || typeid(SecondType) != typeid(std::string))
	{
		return;
	}

	for (std::size_t index = 0; index < this->defaultASCII; ++index)
	{
		this->container[index].firstArgument = (char)index;
		this->container[index].secondArgument = "";
	}
}
