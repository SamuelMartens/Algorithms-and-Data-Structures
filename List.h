#pragma once
#include <cassert>




template <typename T>
class ListNode
{
public:
	ListNode() :
		m_nextElem(nullptr)
		, m_data(0)
	{};

	ListNode(ListNode<T>* nextElem, const T& data) :
		  m_nextElem(nextElem)
		, m_data(data)
	{};
	ListNode(const T& data) :
		  m_nextElem(nullptr)
		, m_data(data)
	{};

	ListNode<T>* Next() { return m_nextElem; };
	const T& Data() const noexcept { return m_data; };

	void SetNext(ListNode<T>* nextElem) { m_nextElem = nextElem; };
	void SetData(const T& data) { m_data = data; };


private:
	ListNode<T>* m_nextElem;
	T m_data;
};


template <typename T>
class List
{
public:
	List() :
		  m_start(nullptr)
		, m_end(nullptr)
		, m_size(0)
	{};


	const T& operator[](int i)
	{
		return GetNodeWithIndex(i)->Data();
	}

	void Insert(const T& data , ListNode<T>* afterInsertNode)
	{
		ListNode<T>* newNode = new ListNode<T>(data, afterInsertNode->Next());
		afterInsertNode->SetNext(newNode);
	}

	void PushBack(const T& elem)
	{
		ListNode<T>* newNode = new ListNode<T>(elem);
		if (!m_start && !m_end)
		{
			m_start = m_end = newNode;
		}
		else
		{
			m_end->SetNext(newNode);
			m_end = newNode;
		}

		++m_size;
	}

	void PushStart(const T& elem)
	{
		ListNode<T>* newNode = new ListNode<T>(elem);
		if (!m_start && !m_end)
		{
			m_start = m_end = newNode;
		}
		else
		{
			newNode->SetNext(m_start);
			m_start = newNode;
		}

		++m_size;
	}

	ListNode<T>* PopBack(bool returnElem = false)
	{
		ListNode<T>* currNode = m_start;

		while (currNode->Next() && currNode->Next() != m_end)
		{
			currNode = currNode->Next();
		}
		if (!currNode->Next())
			return nullptr;

		delete currNode->Next();
		--m_size;

		m_end = currNode;

		if (returnElem)
			return currNode->Next();
		else
		{
			delete currNode->Next();
			return nullptr;
		}
			
	}

	ListNode<T>* PopStart(bool returnElem = false)
	{
		if (m_start)
		{
			ListNode<T>* tempPointer = m_start;

			if (m_end == m_start)
			{
				m_start = m_end = nullptr;
			}
			else
			{
				m_start = tempPointer->Next();
			}

			--m_size;
			
			if (returnElem)
				return tempPointer;
			else
				delete tempPointer;
		}

		return nullptr;
	}

	void Delete(ListNode<T>* deleteNode)
	{
		if (deleteNode == m_start)
		{
			m_start = deleteNode->Next();
			delete deleteNode;
			return;
		}

		ListNode<T>* currNode = m_start;
		while (currNode->Next() && currNode->Next() != deleteNode)
		{
			currNode = currNode->Next();
		}
		assert(currNode->Next());

		currNode->SetNext(deleteNode->Next());
		
		if (!deleteNode->Next())
			m_end = currNode;

		delete deleteNode;
	}

	const ListNode<T>* Search(const T& searchItem)
	{
		ListNode<T>* currNode = this->Start();

		while (currNode)
		{
			if (currNode->Data() == searchItem)
				return currNode;

			currNode = currNode->Next();
		}

		return currNode;
	}

	int Size() const noexcept { return m_size; };

	~List()
	{
		ListNode<T>* currElem = m_start;
		ListNode<T>* nextElem = nullptr;

		while(currElem)
		{
			nextElem = currElem->Next();
			delete currElem;
			currElem = nextElem;
		}

	}

	ListNode<T>* Start() { return m_start; };
	ListNode<T>* End() { return m_end; };

	void SetStart(ListNode<T>* start) { m_start = start; };
	void SetEnd(ListNode<T>* end) { m_end = end; };

private:

	ListNode<T>* GetNodeWithIndex(int i)
	{
		assert(i < m_size);
		int counter = 0;
		ListNode<T>* currNode = m_start;

		if (i == m_size - 1)
			return m_end;

		while (counter < i)
		{
			currNode = currNode.Next();
			++counter;
		}

		return currNode;
	}


	ListNode<T>* m_start;
	ListNode<T>* m_end;
	int m_size;
};