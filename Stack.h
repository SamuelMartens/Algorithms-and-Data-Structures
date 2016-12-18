#pragma once
#include <vector>

template <typename T>
class Stack
{
public:
	Stack() = default;
	~Stack() = default;

	const T& operator[](int i) { return m_array[i]; };

	int Size() const noexcept { return m_array.size(); };
	void Push(const T& element) { m_array.push_back(element); };
	T* Pop()
	{
		if (!Size())
			return nullptr;

		T* pointerToLastElem = new T(m_array[Size() - 1]);
		m_array.pop_back();

		return pointerToLastElem;
	}

private:
	std::vector<T> m_array;
};

