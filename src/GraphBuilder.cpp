#include <osmium/geom/haversine.hpp>
#include "GraphBuilder.h"

GraphBuilder::GraphBuilder(const osmium::memory::Buffer& buffer,
                           const index_type& locs,
                           const std::set<osmium::unsigned_object_id_type>& nodeSet)
  : buffer(buffer), locations(locs), nodeSet(nodeSet)
{
  // add vertices to graph
  for (const auto& node : nodeSet)
  {
    auto v = boost::add_vertex(g);
    g[v].id = node;
    g[v].loc = locations.get(node);
    vertexMap.emplace(node, v);
  }
}

void GraphBuilder::way(const osmium::Way& way)
{
  const char *highway = way.tags()["highway"];

  if (highway)
  {
    osmium::NodeRef prevNode;
    Vertex u = 0;
    Vertex v = 0;

    for (const auto& node : way.nodes())
    {
      v = vertexMap.at(node.positive_ref());

      if (prevNode.positive_ref())
      {
        v = vertexMap.at(node.positive_ref());
        osmium::geom::Coordinates coord(locations.get(node.positive_ref()));
        osmium::geom::Coordinates prev_coord(locations.get(prevNode.positive_ref()));

        double d = osmium::geom::haversine::distance(coord, prev_coord);
        auto edge = boost::add_edge(u, v, g);
        g[edge.first].length = d;
      }

      u = v;
      prevNode = node;
    }
  }
}
