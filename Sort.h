#pragma once
#include <iterator>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Pyramid.h"

namespace
{
	template <typename T>
	void MergeSort(typename std::vector<T>::iterator start,typename std::vector<T>::iterator end, std::vector<T>& newVec)
	{
		if (start == end)
		{
			newVec.push_back(*start);
			return;
		}

		std::vector<T> sorted1, sorted2;
		
		const int midElemDistance = std::distance(start, end) / 2;

		sorted1.reserve(std::distance(start, start + midElemDistance));
		sorted2.reserve(std::distance(start + midElemDistance + 1, end));
		// Divided sorted parts
		MergeSort(start, start + midElemDistance, sorted1);
		MergeSort(start + midElemDistance + 1, end, sorted2);
		
		unsigned insertedFrom1 = 0;
		unsigned insertedFrom2 = 0;

		// Merging
		while (insertedFrom1 != sorted1.size() || insertedFrom2 != sorted2.size())
		{
			if (insertedFrom1 == sorted1.size())
			{
				newVec.push_back(std::move(sorted2[insertedFrom2++]));
			}
			else if (insertedFrom2 == sorted2.size())
			{
				newVec.push_back(std::move(sorted1[insertedFrom1++]));
			}
			else if (sorted1[insertedFrom1] < sorted2[insertedFrom2])
			{
				newVec.push_back(std::move(sorted1[insertedFrom1++]));
			}
			else
			{
				newVec.push_back(std::move(sorted2[insertedFrom2++]));
			}
		}
	};

	template<typename T>
	void ShuffleVec(std::vector<T>& vec)
	{
		// Use current time as seed for generation
		std::srand(std::time(0));

		for (unsigned i = 0; i < vec.size() / 2; ++i)
		{
			std::iter_swap(vec.begin() + std::rand() % vec.size(), vec.begin() + i );
		}

	};

	template<typename T>
	void QuickSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, std::vector<T>& vec)
	{
		if (0 >= std::distance(start, end))
			return;

		unsigned divideItemPos = 0;
		unsigned iterIndex = 0;
		typename std::vector<T>::iterator currIter;

		while (iterIndex < std::distance(start, end) )
		{
			currIter = start + iterIndex;

			if (*currIter < *end)
			{
				std::iter_swap(currIter, start + divideItemPos);
				++divideItemPos;
			}
			++iterIndex;
		}
		std::iter_swap(end, start + divideItemPos);

		QuickSort<T>(start + divideItemPos + 1, end, vec);
		QuickSort<T>(start, start + divideItemPos - 1, vec);
		
	}
}


template<typename T>
void PyramidSort(std::vector<T>& arr)
{
	Pyramid<T> pyramid;
	pyramid.Init(arr);

	for (unsigned i = 0; i < arr.size(); ++i)
	{
		arr[i] = pyramid.Pop();
	}
}

template<typename T>
void MergeSort(std::vector<T>& vec)
{
	if (vec.empty())
		return;

	std::vector<T> sortedVec;
	sortedVec.reserve(vec.size());

	MergeSort(vec.begin(), vec.end() - 1, sortedVec);
	vec.swap(sortedVec);
}

template<typename T>
void QuickSort(std::vector<T>& vec)
{
	// Shuffle our vec to avoid worst case
	ShuffleVec(vec);

	QuickSort<T>(vec.begin(), vec.end() - 1, vec);
}
