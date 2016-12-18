#pragma once

#include <functional>

#include "AdjacencyLisy.h"
#include "Queue.h"

namespace TraversalUtils
{
	enum class VertexStatus
	{
		Undiscovered,
		Discovered,
		Processed
	};

	// VTN - Vertex Traversal Node
	template<typename T>
	struct VTN
	{
		VTN() :
			  m_status(VertexStatus::Undiscovered)
			, m_vertex(nullptr)
		{};

		VTN(const List<T*>* initNode) :
			  m_status(VertexStatus::Undiscovered)
			, m_vertex(initNode)
		{};

		VertexStatus m_status;
		const List<T*>* m_vertex;
	};

	template<typename T>
	void InitVTNGraph(const AdjacencyList<T>& graph, AdjacencyList<VTN<T>>& newGraph)
	{
		for (unsigned i = 0; i < graph.GetVerticeArray().size(); ++i)
		{
			

		}
	}

	template<typename T>
	void ProcessVertex(VTN<T>& vertex, Queue<VTN<T>>& queue)
	{
		
	}

};

template<typename T>
void BFS(const AdjacencyList<T>& graph, std::function<void(const T&)> processFunc, const int rootInd = 0)
{
	if (!graph.GetVerticeArray().size())
		return;

	List<T>* currentVert = graph.GetVerticeArray()[rootInd];
	Queue<TraversalUtils::VTN<T>> queue;


}
