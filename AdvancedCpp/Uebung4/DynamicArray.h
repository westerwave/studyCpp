#pragma once
#include <iostream>
#include <exception>

template <typename T>
class DynamicArray
{
	const int m_defaultSize = 10;
	T* m_data;

	int m_reservedSize;
	int m_length;

	void copy(DynamicArray<T> other)
	{
		if (this != &other)
		{
			delete m_data;
			m_data = other.m_data;
			m_length = other.m_length;
			m_reservedSize = other.m_reservedSize;
		}
	};

	void move(DynamicArray<T> other)
	{
		if (this != &other)
		{
			delete m_data;
			m_data = other.m_data;
			m_length = other.m_length;
			m_reservedSize = other.m_reservedSize;

			other.m_length = 0;
			other.m_reservedSize = 0;
			delete other.m_data;
		}
	};

	void stackUp(int index)
	{
		T* buffer = new T[m_length - 1];
		int srcIndex = 0;
		int targetIndex = 0;
		while (srcIndex < m_length)
		{
			if (srcIndex != index)
			{
				buffer[targetIndex] = m_data[srcIndex];
				++srcIndex;
				++targetIndex;
			}
			else if (srcIndex == index)
			{
				++srcIndex;
			}
		}
		for (int i = 0; i < m_length - 1; i++)
		{
			m_data[i] = buffer[i];
		}
		delete buffer;
	};

public:
	DynamicArray() : m_data(new T[m_defaultSize]), m_reservedSize(m_defaultSize)
	{
	};

	DynamicArray(const int size) : m_data(new T[size]), m_reservedSize(size)
	{
	};

	DynamicArray(const DynamicArray<T>& other)
	{
		copy(other);
	};

	DynamicArray(DynamicArray<T>&& other)
	{
		move(other);
	};

	DynamicArray operator=(const DynamicArray<T>& other)
	{
		copy(other);
		return *this;
	};

	DynamicArray operator=(DynamicArray<T>&& other)
	{
		move(other);
		return *this;
	};

	T operator[](int index)
	{
		if (index >= m_length || index < 0)
		{
			throw std::runtime_error("Index out of bounds!");
		}
		return m_data[index];
	};

	int getLength() const
	{
		return m_length;
	};

	int getReservedLength() const
	{
		return m_reservedSize;
	};

	void add(const T toAdd)
	{
		std::cout << "Add element" << toAdd << std::endl;
		if (m_reservedSize == m_length)
		{
			reserveSpace();
		}
		m_data[m_length] = toAdd;
		++m_length;
	};

	void remove(int index)
	{
		if (index > m_length - 1 || index < 0)
		{
			return;
		}
		if (index != m_length - 1)
		{
			stackUp(index);
		}
		--m_length;
	};

	void remove(const T element)
	{
		for (int index = 0; index < m_length; index++)
		{
			if (m_data[index] == element)
			{
				remove(index);
				return;
			}
		}
	};

	void reserveSpace(int elements = 10)
	{
		std::cout << "Reserve space for more Elements:" << elements << std::endl;
		const int oldLength = m_length;
		const int oldReservedSize = m_reservedSize;
		const int newReservedSize = m_reservedSize + elements;

		T* buffer = new T[oldLength];
		for (int i = 0; i < oldLength; i++)
		{
			buffer[i] = m_data[i];
		}
		delete m_data;
		m_data = new T[newReservedSize];
		for (int i = 0; i < oldLength; i++)
		{
			m_data[i] = buffer[i];
		}
		m_reservedSize = newReservedSize;
		delete buffer;
	};

	~DynamicArray()
	{
		delete m_data;
	};
};

