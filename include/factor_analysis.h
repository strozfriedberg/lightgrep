/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <algorithm>
#include <list>
#include <vector>
#include <queue>


#include "automata.h"

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

// A Path object represents a "traversed" path (path) and a log of whether or not a node has been visited (visited).
class Path {
  public:
    std::vector<NFA::VertexDescriptor> path;
    std::vector<bool> visited;

    Path(std::vector<NFA::VertexDescriptor> p, std::vector<bool> v) {
      path = p;
      visited = v;
    }
};

//updates given queue based on given parameters
void updateQueue(
  std::queue<Path> *bfsQueue,
  const std::vector<NFA::VertexDescriptor> &path,
  const std::vector<bool> &visited,
  const NFA::VertexDescriptor &startingNode,
  const NFA::VertexDescriptor &currentNode,
  const bool &recursOnItself) {
    //make mutable copy of path
    std::vector<NFA::VertexDescriptor> pathCopy(path);
    pathCopy.reserve(path.size() + 2);

    //If recurs on itself, continue with thread that includes self recursion and thread that doesn't
    // as acceptable paths to cover all cases
    if (recursOnItself) {
      pathCopy.insert(pathCopy.end(), {startingNode, currentNode});
      bfsQueue->push(Path(pathCopy, visited));
      //delete added elements
      pathCopy.erase(pathCopy.begin() + path.size(), pathCopy.end());
    }

    //push back current node to end of path
    pathCopy.push_back(currentNode);
    bfsQueue->push(Path(pathCopy, visited));
}

Lists breadthFirstSearch(
  NFA::VertexDescriptor startingNode, 
  const NFA& graph) {

    //Create empty queue
    std::queue<Path> bfsQueue;

    //initialize variables
    std::vector<NFA::VertexDescriptor> path;
    path.reserve(graph.verticesSize() * 2);
    std::vector<bool> visited(graph.verticesSize(), false);

    //add starting node to path and add path to queue
    path.push_back(startingNode);
    Path pathObject(path, visited);
    bfsQueue.push(pathObject);
    Lists acceptablePaths = Lists{};

    //recur while the queue isn't empty
    while (!bfsQueue.empty()) {
      //get the pathObject at the front of our queue
      pathObject = bfsQueue.front();
      bfsQueue.pop();

      //update our variables
      path = pathObject.path;
      visited = pathObject.visited;

      //get our ending node and use that as starting point
      startingNode = path[path.size() - 1];
      visited[startingNode] = true;

      //if our node is an accept state, return our current path to acceptablePaths
      if (graph[startingNode].IsMatch){
        acceptablePaths.push_back(path);
      }
      else {
        // get output nodes
        const NFA::NeighborList nl(graph.outVertices(startingNode));
        List outputNodes(nl.begin(), nl.end());

        // check if starting node recurs on itself
        bool recursOnItself = listContains(outputNodes, startingNode);

        //check if current node can be in dominant region
        std::string label = (graph[startingNode]).label();
        bool invalidCharacter = (label.length() > 1);

        // If there are any nodes to explore to
        for (unsigned int i = 0; i < outputNodes.size(); i++) {
          NFA::VertexDescriptor currentNode = outputNodes[i];
          //if node is unvisited
          if (!visited[currentNode]) {
            //if node can't be in dominant region, replace with non-existant node
            if (invalidCharacter) {
              path[path.size() - 1] = -1;
              updateQueue(&bfsQueue, path, visited, -1, currentNode, recursOnItself);
              path[path.size() - 1] = -2;
              updateQueue(&bfsQueue, path, visited, -2, currentNode, recursOnItself);
            }
            else {
              updateQueue(&bfsQueue, path, visited, startingNode, currentNode, recursOnItself);
            }
          }
        }
      }
    }

    return acceptablePaths;
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

List getShortestPath(Lists pos) {
  int n = pos.size();
  int minimum = -1;
  int tempSize;
  List s;

  for (int i = 0; i < n; i++) {
    tempSize = pos[i].size();
    if (minimum == -1 || tempSize < minimum) {
      minimum = tempSize;
      s = pos[i];
    }
  }

  return s;
}

List dominantPath(  
  NFA::VertexDescriptor startingNode,
  const NFA& graph) {
        
  Lists pos(breadthFirstSearch(startingNode, graph));

  int n = pos.size();

  List s = getShortestPath(pos);

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

      if (k == n && res.size() <= stem.size()) {
        res = stem;
      }
    }
  }

  return res;
}

std::string analyze(const NFA& nfa, int minLength) {
  List res = dominantPath(0, nfa);
  std::string s = "";

  for (auto vi : res) {
    if (vi == 0) {
      continue;
    }
    s += (nfa)[vi].Trans->label();
  }

  return (int)s.length() >= minLength ? s : "";
}
