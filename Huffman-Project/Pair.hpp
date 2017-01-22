#pragma once
#include <iostream>

template <typename FirstType = char, typename SecondType = std::size_t>
struct Pair
{
	FirstType firstArgument;
	SecondType secondArgument;

	Pair(const FirstType &firstArgument = FirstType(), const SecondType &secondArgument = SecondType())
		: firstArgument(firstArgument), secondArgument(secondArgument) { }
	Pair(const Pair<FirstType, SecondType> &other);

	Pair<FirstType, SecondType> &operator=(const Pair<FirstType, SecondType> &other);

	template <typename FriendFirstType, typename FriendSecondType>
	friend std::ostream &operator<<(std::ostream &out, const Pair<FriendFirstType, FriendSecondType> &src);

private:
	void copy(const FirstType &firstArgument, const SecondType &secondArgument);
};

template<typename FirstType, typename SecondType>
inline void Pair<FirstType, SecondType>::copy(const FirstType & firstArgument, const SecondType & secondArgument)
{
	this->firstArgument = firstArgument;
	this->secondArgument = secondArgument;
}

template<typename FirstType, typename SecondType>
inline Pair<FirstType, SecondType>::Pair(const Pair<FirstType, SecondType>& other)
{
	this->copy(other.firstArgument, other.secondArgument);
}

template<typename FirstType, typename SecondType>
inline Pair<FirstType, SecondType> & Pair<FirstType, SecondType>::operator=(const Pair<FirstType, SecondType>& other)
{
	// DO: operator=
	if (this != &other)
	{
		this->copy(other.firstArgument, other.secondArgument);
	}

	return *this;
}

template <typename FriendFirstType, typename FriendSecondType>
std::ostream &operator<<(std::ostream &out, const Pair<FriendFirstType, FriendSecondType> &src)
{
	out << src.firstArgument << " " << src.secondArgument;

	return out;
}