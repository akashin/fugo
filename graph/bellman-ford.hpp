#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

namespace fugo {

class BellmanFordFinder
{
 public:
  BellmanFordFinder(const std::vector<std::vector<std::pair<int, int>>>& G) : G(G) {}

  void init()
  {
    distance.assign(G.size(), 1000000000);
  }

  std::vector<int> find(int source)
  {
    distance[source] = 0;
    pchange.assign(G.size(), 0);
    pchange[source] = 1;
    for(int it = 0; it < G.size() - 1; it++)
    {
      change.assign(G.size(), 0);
      for(int v = 0; v < G.size(); v++)
      {
        if (!pchange[v])
          continue;
        for(const auto& edge : G[v])
        {
          if (distance[edge.first] > distance[v] + edge.second)
          {
            distance[edge.first] = distance[v] + edge.second;
            change[edge.first] = 1;
          }
        }
      }
      pchange = change;
    }
    return distance;
  }
 private:
  const std::vector<std::vector<std::pair<int, int>>>& G;
  std::vector<int> distance;
  std::vector<char> change;
  std::vector<char> pchange;

};

} // namespace fugo
