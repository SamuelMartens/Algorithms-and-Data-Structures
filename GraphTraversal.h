#pragma once

#include <functional>

#include "AdjacencyList.h"
#include "Queue.h"

namespace TraversalUtils
{
	template<typename T>
	void ProcessVertexBFS(AdjacencyVertex<T>& vertex, Queue<AdjacencyVertex<T>*>& queue, std::function<void(const T&)> ProcessFunc)
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


	template<typename T>
	void ProcessVertexDFS(AdjacencyVertex<T>& vertex, std::function<void(const T&)> ProcessFunc)
	{
		if (VertexStatus::Processed == vertex.m_status)
			return;

		vertex.m_status = VertexStatus::Discovered;

		ListNode<AdjacencyVertex<T>*>* currentNode = vertex.m_edges.Start();
		while (currentNode)
		{
			if(currentNode->Data()->m_status == VertexStatus::Undiscovered)
			{
				//currentNode->Data()->m_status = VertexStatus::Discovered;
				ProcessVertexDFS(*currentNode->Data(), ProcessFunc);
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
	TraversalUtils::ProcessVertexBFS(graph.GetVerticesArray()[rootInd], queue, ProcessFunc);
	
	while (!queue.IsEmpty())
	{
		ListNode<AdjacencyVertex<T>*>* currentVertex = queue.Pop();
		TraversalUtils::ProcessVertexBFS(*currentVertex->Data(), queue, ProcessFunc);
	}

}

template<typename T>
void DFS(AdjacencyList<T>& graph, std::function<void(const T&)> ProcessFunc, const int rootInd = 0)
{
	if (!graph.GetVerticesArray().size())
		return;

	TraversalUtils::ProcessVertexDFS(graph.GetVerticesArray()[rootInd], ProcessFunc);

}
