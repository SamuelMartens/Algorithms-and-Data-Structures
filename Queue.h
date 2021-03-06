#pragma once

#include "List.h"

template <typename T>
class Queue
{
public:
	void Push(const T& elem) { m_data.PushBack(elem); };
	ListNode<T>* Pop() { return m_data.PopStart(true); };
	int Size() const noexcept { return m_data.Size(); };
	bool IsEmpty() const noexcept { return !static_cast<bool>(m_data.Size()); };


private:
	List<T> m_data;
};