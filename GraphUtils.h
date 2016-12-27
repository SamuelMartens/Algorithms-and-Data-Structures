#pragma once

#include <functional>
#include <map>
#include <vector>
#include <limits>

#include "AdjacencyList.h"
#include "Queue.h"
#include "List.h"

namespace GraphUtils
{

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

	template<typename T>
	void PrimAlgorithm(AdjacencyList<T>& graph, std::vector<List<const AdjacencyVertex<T>*>>& path, const int startInd = 0)
	{
		graph.UndiscoverAll();
		// Assume that Undiscovered vertex is not in list. So Discovered is already in list
		std::vector<unsigned> weightToVertex(graph.GetVerticesArray().size(), std::numeric_limits<unsigned>::max());
		path.clear();
		path.resize(graph.GetVerticesArray().size(), List<const AdjacencyVertex<T>*>());
		weightToVertex[startInd] = 0;

		AdjacencyVertex<T>* currentVert = &graph.GetVerticesArray()[startInd];

		while (VertexStatus::Undiscovered == currentVert->m_status)
		{
			currentVert->m_status = VertexStatus::Discovered;

			ListNode<AdjacencyVertex<T>*>* neighbourVert = currentVert->m_edges.Start();
			unsigned edgesCounter = 0;

			while (neighbourVert)
			{
				if (neighbourVert->Data()->m_status == VertexStatus::Undiscovered 
					&& currentVert->m_edgesWeight[edgesCounter] + weightToVertex[graph.GetIndex(currentVert)] < weightToVertex[graph.GetIndex(neighbourVert->Data())])
				{
					weightToVertex[graph.GetIndex(neighbourVert->Data())] = currentVert->m_edgesWeight[edgesCounter] + weightToVertex[graph.GetIndex(currentVert)];
					path[graph.GetIndex(neighbourVert->Data())].PushBack(currentVert);
				}

				++edgesCounter;
				neighbourVert = neighbourVert->Next();
			}

			edgesCounter = startInd;
			unsigned minWeight = std::numeric_limits<unsigned>::max();

			for (unsigned i = 0; i < weightToVertex.size(); ++i)
			{
				if (VertexStatus::Undiscovered == graph.GetVerticesArray()[i].m_status && weightToVertex[i] < minWeight)
				{
					minWeight = weightToVertex[i];
					edgesCounter = i;
				}
			}
			
			//path[graph.GetIndex(currentVert)].PushBack(&graph.GetVerticesArray()[edgesCounter]);
			currentVert = &graph.GetVerticesArray()[edgesCounter];
		}

	}

}