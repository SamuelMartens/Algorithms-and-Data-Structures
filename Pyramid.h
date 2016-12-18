#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

template<typename T>
class Pyramid
{
public:

	void Init(const std::vector<T>& vec)
	{
		m_array.clear();
		m_array.reserve(vec.size());

		for (unsigned i = 0; i < vec.size(); ++i)
			Insert(vec[i]);

	}

	void Insert(const T& element)
	{
		m_array.push_back(element);
		BulbUp(m_array.size() - 1);
	}

	T Pop()
	{
		assert(!m_array.empty());

		T returnVal = m_array.front();

		m_array.front() = std::move(m_array.back());
		m_array.pop_back();
		
		//if (!m_array.empty())
			BulbDown(0);

		return returnVal;
	}

private:
	
	int GetParent(int index) const noexcept { return (index - 1) / 2.0; };
	int GetChild_1(int index) const noexcept { return index * 2 + 1; };
	int GetChild_2(int index) const noexcept { return index * 2 + 2; };
	int GetMinChildInd(int index) const noexcept
	{
		const int child_1 = GetChild_1(index);
		const int child_2 = GetChild_2(index);

		if (child_1 >= m_array.size())
			return -1;
		if (child_2 >= m_array.size())
			return child_1;
		
		return m_array[child_1] < m_array[child_2] ? child_1 : child_2;
	}

	int BulbUp(int index)
	{
		if (!index)
			return 0;

		const int parentInd = GetParent(index);

		if (m_array[index] < m_array[parentInd])
		{
			std::iter_swap(m_array.begin() + index, m_array.begin() + parentInd);
			index = BulbUp(parentInd);
		}

		return index;
	}

	int BulbDown(int index)
	{
		if (GetChild_1(index) >= m_array.size())
			return index;

		const int minChildInd = GetMinChildInd(index);
		if (m_array[minChildInd] < m_array[index] )
		{
			std::iter_swap(m_array.begin() + index, m_array.begin() + minChildInd);
			index = BulbDown(minChildInd);
		}

		return index;
	}

	std::vector<T> m_array;

};
