#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <cassert>

#include "List.h"

unsigned HashString(const std::string& s, int hashTableSize)
{
	constexpr float hashConstant = 1.61803398874989;
	long float result = 0;

	for (unsigned i = 0; i < s.size(); ++i)
	{
		result += std::powf(hashConstant, i) * static_cast<int>(s[i]);
	}

	
	return static_cast<unsigned>(std::fmod(result, hashTableSize));
}

template <typename T>
struct HashTableNode
{
	HashTableNode(const std::string& key, const T& data) :
		  m_key(key)
		, m_data(data)
	{};

	std::string m_key;
	T m_data;
};

template <typename T>
class HashTable
{
	using t_Node = typename HashTableNode<T>;
	using t_HashBucket = typename List<t_Node>;

public:
	HashTable() :
		m_filledPlaces(0)
	{
		m_array.resize(m_initSize);
	};

	int Size() const noexcept { return m_filledPlaces; };

	void Insert(const std::string& key, const T& value)
	{
		t_Node newNode(key, value);

		m_array[HashString(key, m_array.size())].PushBack(newNode);
		++m_filledPlaces;
		if (m_topLoadFactor > m_filledPlaces / Size())
			Rebuild(Size() * 2);
	}

	void Rebuild(int newSize)
	{
		assert(newSize >= m_filledPlaces);

		std::vector<t_HashBucket> newVec;
		newVec.resize(newSize);

		for (unsigned i = 0; i < m_array.size(); ++i)
		{
			if (m_array[i].Size())
			{
				ListNode<t_Node>* currNode = m_array[i].Start();

				while (currNode)
				{
					newVec[HashString(currNode->Data().m_key, newVec.size())].PushBack(currNode->Data());
					currNode = currNode->Next();
				}
			}
		}
		m_array.swap(newVec);
	}

	const t_Node* Search(const std::string& key)
	{

		ListNode<t_Node>* searchNode = FindNodeWithKey(key);
		if (searchNode)
			return &(searchNode->Data())
	}

	void Delete(const std::string& key )
	{
	
		ListNode<t_Node>* searchNode = FindNodeWithKey(key);
		assert(searchNode);

		m_array[HashString(key, m_array.size())].Delete(searchNode);
		--m_filledPlaces;

		if (m_filledPlaces/m_array.size() < m_bottomLoadFactor)
		{
			Rebuild(Size() * 4);
		}
	}


private:

	ListNode<t_Node>* FindNodeWithKey(const std::string& key)
	{
		int hashKey = HashString(key, m_array.size());
		if (!m_array[hashKey].Size())
			return nullptr;

		ListNode<T>* searchNode = m_array[hashKey].Start();
		while (searchNode)
		{
			if (searchNode->Data().m_key == key)
				return searchNode;
		}

		return nullptr;
	}

	std::vector<t_HashBucket> m_array;
	int m_filledPlaces;

	static constexpr unsigned m_initSize = 50;
	static constexpr float m_topLoadFactor = 0.75;
	static constexpr float m_bottomLoadFactor = 0.00001;
};
