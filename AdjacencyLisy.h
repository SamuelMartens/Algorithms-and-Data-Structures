#pragma once

#include <vector>
#include <cassert>

#include "List.h"


template<typename T>
struct AdjacencyVertex
{
	AdjacencyVertex(const T& newData, unsigned id) :
			m_data(newData)
		, m_id(id)
	{};

	~AdjacencyVertex() = default;

	T m_data;
	const unsigned m_id;
	List<AdjacencyVertex<T>*> m_edges;
};

template<typename T>
class AdjacencyList
{
	using AV = AdjacencyVertex<T>;

public:

	AdjacencyList() :
		currentId(0)
	{};

	~AdjacencyList() = default;

	void AddVertex(const T& newVertex)
	{
		m_vertices.push_back(AdjacencyVertex(newVertex, GenerateId()));
	}

	void AddEdge(AV& firstV, AV& secondV)
	{
		firstV.m_edges.PushBack(secondV);
		secondV.m_edges.PushBack(firstV);
	}

	void RemoveEdge(AV& firstV, AV& secondV, bool removeOnlySecond = false)
	{
		assert(GetNodeById(firstV, secondV.m_id) && GetNodeById(secondV, firstV.m_id));
		firstV.m_edges.Delete(GetNodeById(firstV, secondV.m_id));
		if (!removeOnlySecond)
			secondV.m_edges.Delete(GetNodeById(secondV, firstV.m_id));
	}

	void RemoveVertex(AV& removableVertex)
	{
		ListNode<AV*>* currentNode = removableVertex.m_edges.Start();
		while (currentNode)
		{
			RemoveEdge(*currentNode->Data(), removableVertex, true);
			currentNode = currentNode->Next();
		}

		m_vertices.erase(GetNodeById(removableVertex.m_id));
	}

	bool CheckEdge(const AV& firstV, const AV& secondV) const
	{
		return GetNodeById(firstV, secondV.m_id) && GetNodeById(secondV, firstV.m_id);
	}

	int GetVertexDegree(int index) const { return m_vertices[i].m_edges.Size(); };
	int GetVertexDegree(const AV& vertex) const { return vertex.m_edges.Size(); };

	const std::vector<AdjacencyVertex<T>>&  GetVerticesArray() const { return m_vertices; };

private:

	unsigned GenerateId() noexcept { return m_currentId++; }

	typename std::vector<AdjacencyVertex<T>>::iterator GetIteratorById(unsigned id) const
	{
		typename std::vector<AdjacencyVertex<T>>::iterator iter = m_vertices.begin();

		while (iter != m_vertices.end())
		{
			if (iter->m_id == id)
				break;
		}

		return iter;
	}

	ListNode<AV*>* GetNodeById(const AV& vertex ,unsigned id) const
	{
		ListNode<AV*>* currentNode = vertex.m_edges.Start();

		while (currentNode)
		{
			if (currentNode->Data()->m_id == id)
				return currentNode;

			currentNode = currentNode->Next();
		}

		return nullptr;
	}

	unsigned m_currentId = 0;
	std::vector<AdjacencyVertex<T>> m_vertices;
};



