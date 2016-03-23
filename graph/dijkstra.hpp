#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

namespace fugo {

class DijkstraFinder
{
 public:
  DijkstraFinder(const std::vector<std::vector<std::pair<int, int>>>& G) : G(G) {}

  void init()
  {
    while (!Q.empty())
      Q.pop();
    distance.assign(G.size(), 1000000000);
  }

  std::vector<int> find(int source)
  {
    distance[source] = 0;
    Q.push( std::make_pair(-distance[source], source) );
    while (!Q.empty())
    {
      std::pair<int, int> qtop = Q.top();
      Q.pop();
      if (-qtop.first != distance[qtop.second])
        continue;
      int v = qtop.second;
      for(const auto& edge : G[v])
      {
        int to = edge.first;
        int len = edge.second;
        if (distance[to] > distance[v] + len)
        {
          distance[to] = distance[v] + len;
          Q.push(std::make_pair(-distance[to], to));
        }
      }
    }
    return distance;
  }
 private:
  const std::vector<std::vector<std::pair<int, int>>>& G;
  std::priority_queue<std::pair<int,int>> Q;
  std::vector<int> distance;
};

} // namespace fugo
