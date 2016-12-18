#pragma once

#include <vector>
#include <cassert>

template <typename T>
class AdjacencyMatrix
{
	void AddVertex(const T& newVertex)
	{
		m_data.push_back(newVertex);
		for (unsigned i = 0; i < m_matrix.data; ++i)
		{
			m_matrix[i].push_back(false);
		}
		m_matrix.push_back(std::vector<bool>());
		m_matrix.back().resize(m_matrix.front().size());
	}
	
	void RemoveVertex(const T& removableVert)
	{
		const int removeInd = GetIdInMatrix(removableVert);
		assert(removeInd < m_matrix.size());

		std::swap(m_data.back(), m_data[removeInd]);
		m_data.pop_back();

		std::swap(m_matrix.back(), m_matrix[removeInd]);
		m_matrix.pop_back();

		for (unsigned i = 0; i < m_matrix.size(); ++i)
		{
			assert(removeInd < m_matrix[i].size());
			std::swap(m_matrix[i].back(), m_matrix[i][removeInd]);
			m_matrix[i].pop_back();
		}
	}

	void AddEdgeByIndices(int indVert1, int indVert2)
	{
		assert(indVert1 < m_matrix.size() && indVert2 < m_matrix.size());
		assert(indVert1 < m_matrix[indVert2].size() && indVert2 < m_matrix[indVert1].size());

		m_matrix[indVert1][indVert2] = true;
		m_matrix[indVert2][indVert1] = true;
	}

	void RemoveEdgeByIndices(int indVert1, int indVert2)
	{
		assert(indVert1 < m_matrix.size() && indVert2 < m_matrix.size());
		assert(indVert1 < m_matrix[indVert2].size() && indVert2 < m_matrix[indVert1].size());

		m_matrix[indVert1][indVert2] = false;
		m_matrix[indVert2][indVert1] = false;
	}

	int GetIdInMatrix(const T& vert) const
	{
		typename std::vector<T>::iterator vertIter = std::find(m_data.begin(), m_data.end(), vert);
		assert(vertIter != m_data.end());

		return std::distance(m_data.begin(), vertIter);
	}

	void AddEdge(const T& firstV, const T& secondV)
	{
		AddEdgeByIndices(GetIdInMatrix(firstV), GetIdInMatrix(secondV));
	}

	void RemoveEdge(const T& firstV, const T& secondV)
	{
		RemoveEdgeByIndices(GetIdInMatrix(firstV), GetIdInMatrix(secondV));
	}

	bool CheckEdge(const T& firstV, const T& secondV) const
	{
		assert(m_matrix[GetIdInMatrix(secondV)][GetIdInMatrix(firstV)] == m_matrix[GetIdInMatrix(firstV)][GetIdInMatrix(secondV)]);
		return m_matrix[GetIdInMatrix(firstV)][GetIdInMatrix(secondV)];
	}

private:
	// Index in data is index in matrix
	std::vector<std::vector<bool>> m_matrix;
	std::vector<T> m_data;

};