#pragma once

#include <functional>

#include "AdjacencyList.h"
#include "Queue.h"

namespace TraversalUtils
{
	template<typename T>
	void ProcessVertex(AdjacencyVertex<T>& vertex, Queue<AdjacencyVertex<T>*>& queue, std::function<void(const T&)> ProcessFunc)
	{
		if (VertexStatus::Processed == vertex.m_status)
			return;

		ListNode<AdjacencyVertex<T>*>* currentNode = vertex.m_edges.Start();
		while (currentNode)
		{
			if(currentNode->Data()->m_status == VertexStatus::Undiscovered)
			{
				queue.Push(currentNode->Data());
				currentNode->Data()->m_status = VertexStatus::Discovered;
			}

			currentNode = currentNode->Next();
		}

		ProcessFunc(vertex.m_data);
		vertex.m_status = VertexStatus::Processed;
	}
}

template<typename T>
void BFS(AdjacencyList<T>& graph, std::function<void(const T&)> ProcessFunc, const int rootInd = 0)
{
	if (!graph.GetVerticesArray().size())
		return;

	Queue<AdjacencyVertex<T>*> queue;
	TraversalUtils::ProcessVertex(graph.GetVerticesArray()[rootInd], queue, ProcessFunc);
	
	while (!queue.IsEmpty())
	{
		ListNode<AdjacencyVertex<T>*>* currentVertex = queue.Pop();
		TraversalUtils::ProcessVertex(*currentVertex->Data(), queue, ProcessFunc);
	}

}
