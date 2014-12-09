#include <osmium/geom/haversine.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "RoutePlanner.h"

RoutePlanner::RoutePlanner(const GraphBuilder& gb,
                           const osmium::Location& start,
                           const osmium::Location& dest)
  : gb(gb), start(start), destination(dest)
{
  auto graph = gb.get_graph();
  auto vertex_map = gb.get_vertex_map();

  NearestNode startNode(start, gb.get_locations());
  osmium::apply(gb.get_buffer(), startNode);
  Vertex startVertex = vertex_map[startNode.get()];

  NearestNode destNode(dest, gb.get_locations());
  osmium::apply(gb.get_buffer(), destNode);
  Vertex destVertex = vertex_map[destNode.get()];

  std::vector<Vertex> predecessors(boost::num_vertices(graph));

  boost::dijkstra_shortest_paths(
    graph, startVertex, boost::predecessor_map(predecessors.data())
    .weight_map(boost::get(&EdgeProperty::length, graph))
  );

  if (destVertex != predecessors[destVertex])
  {
    Vertex u = destVertex;

    for (auto v = destVertex; v != startVertex; v = predecessors[v])
    {
      route.emplace_back(graph[v].loc);

      if (u != destVertex)
      {
        osmium::geom::Coordinates coord(graph[v].loc);
        osmium::geom::Coordinates prev_coord(graph[u].loc);

        double d = osmium::geom::haversine::distance(coord, prev_coord);
        distances.emplace_back(d);
      }
      u = v;
    }

    route.emplace_back(graph[startVertex].loc);
    distances.emplace_back(osmium::geom::haversine::distance(
                             graph[startVertex].loc, graph[u].loc));

    std::reverse(route.begin(), route.end());
    std::reverse(distances.begin(), distances.end());
  }
  else
    std::cout << "Route not found" << std::endl;
}
