/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>
#include <list>
#include <vector>

#include "automata.h"
#include "graph.h"


template <class NeighborListType>
int edgeCount(NeighborListType nl) {
  return nl.end() - nl.begin();
}

typedef std::vector<NFA::VertexDescriptor> List;
typedef std::vector<List> Lists;

template <class GraphType>
void add_edges(GraphType& graph, const std::vector<std::pair<typename GraphType::VertexDescriptor, typename GraphType::VertexDescriptor>> pairs) {
  for (std::pair<typename GraphType::VertexDescriptor, typename GraphType::VertexDescriptor> p : pairs) {
     graph.addEdge(p.first, p.second);
  }
}

Lists listsConcatenator(std::vector<Lists> vector_lists) {
  Lists ret;
  for (Lists lists : vector_lists) {
    for (List list : lists) {
      if (list.size() > 0) {
        ret.push_back(list);
      }
    }
  }
  return ret;
}

bool listContains(List l, NFA::VertexDescriptor node) {
  return std::find(l.begin(), l.end(), node) != l.end();
}


Lists depthFirstSearch(
  NFA::VertexDescriptor startingNode, 
  NFA::VertexDescriptor endingNode, 
  const NFA& graph,
  Lists lists = Lists{},
  List list = List{}) {

    //check if we hit node we've already visited
    if (listContains(list, startingNode)) {
      return lists;
    }

    // Add our current starting node
    list.push_back(startingNode);

    //If we hit our goal, add our current list to our list and end
    if (startingNode == endingNode) {
      lists.push_back(list);
      return lists;
    }

    std::vector<Lists> allLists;

    const NFA::NeighborList nl(graph.outVertices(startingNode));
    List outputNodes(nl.begin(), nl.end());

    // If there are any nodes to explore to
    for (unsigned int i = 0; i < outputNodes.size(); i++) {
      NFA::VertexDescriptor currentNode = outputNodes[i];
      allLists.push_back(depthFirstSearch(currentNode, endingNode, graph, lists, list));
    }

    return listsConcatenator(allLists);
  }


template<typename T>
bool containsSubset(const std::vector<T>& vectorToSearch, const std::vector<T>& vertices) {
  unsigned int range = vectorToSearch.size() - vertices.size();

  if (range == 0) {
    for (unsigned int i = 0; i < vectorToSearch.size(); i++) {
      if (vectorToSearch[i] != vertices[i]) {
        return false;
      }
    }
    return true;
  }

  for (unsigned int i = 0; i <= range; i++) {
    if (vectorToSearch[i] == vertices[0]) {
      for(unsigned int j = 1; j < vertices.size(); j++) {
        if (vectorToSearch[i + j] != vertices[j]) {
          return false;
        }
      }
      return true;
    }
    if (i == range) {
      return false;
    }
  }

  return true;
}

List dominantPath(  
  NFA::VertexDescriptor startingNode, 
  NFA::VertexDescriptor endingNode, 
  const NFA& graph) {
        
  Lists pos(depthFirstSearch(startingNode, endingNode, graph));

  int n = pos.size();

  List s = pos[0];
  int len = s.size();

  List res = {};

  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j <= len; j++) {
      List stem(s.begin() + i, s.begin() + j);
      int k = 1;

      for (k = 1; k < n; k++) {
        if (!containsSubset<NFA::VertexDescriptor>(pos[k], stem)) {
          break;
        }
      }

      if (k == n && res.size() < stem.size()) {
        res = stem;
      }
    }
  }

  return res;
}
