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
  }
}

void GraphBuilder::way(const osmium::Way& way)
{
  const char *highway = way.tags()["highway"];

  if (highway)
  {
    osmium::NodeRef prevNode;
    Vertex u, v;

    for (const auto& node : way.nodes())
    {
      if (prevNode.positive_ref())
      {
        auto VertexIters = boost::vertices(g);

        for (auto it = VertexIters.first; it != VertexIters.second; ++it)
        {
          if (g[*it].id == node.positive_ref())
          {
            v = *it;
            osmium::geom::Coordinates coord(locations.get(node.positive_ref()));
            osmium::geom::Coordinates prev_coord(locations.get(prevNode.positive_ref()));

            double d = osmium::geom::haversine::distance(coord, prev_coord);
            auto edge = boost::add_edge(u, v, g);
            g[edge.first].length = d;
            break;
          }
        }
      }

      u = v;
      prevNode = node;
    }
  }

  //  osmium::NodeRef prevref;

  //  for (const osmium::NodeRef& actref : way.nodes())
  //  {
  //    id_map_t::iterator pos;
  //    bool inserted;
  //    boost::tie(pos, inserted) = idMap.emplace(actref.positive_ref(), Vertex());

  //    if (inserted)
  //    {
  //      v = boost::add_vertex(actref.positive_ref(), g);
  //      pos->second = v;
  //    }

  //    else
  //    {
  //      v = idMap[actref.positive_ref()];
  //    }

  //    if (prevref.positive_ref())
  //    {
  //      osmium::geom::Coordinates cord(locations.get(actref.positive_ref()));
  //      osmium::geom::Coordinates prev_cord(locations.get(prevref.positive_ref()));
  //      Weight w = osmium::geom::haversine::distance(cord, prev_cord);
  //      boost::add_edge(u, v, w, g);
  //    }

  //    prevref = actref;
  //    u = v;
  //  }

}
