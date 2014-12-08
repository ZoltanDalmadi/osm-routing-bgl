#pragma once

#include <set>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>
#include <osmium/index/map/vector.hpp>
typedef osmium::index::map::VectorBasedSparseMap<osmium::unsigned_object_id_type,
        osmium::Location, std::vector> index_type;

#include <boost/graph/adjacency_list.hpp>

struct VertexProperty
{
  osmium::unsigned_object_id_type id;
  osmium::Location loc;
};

struct EdgeProperty
{
  double length;
};

typedef boost::adjacency_list
<boost::listS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty>
Graph;

typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;

/*
 * Builds a graph from the buffer passed in the constructor.
 */
class GraphBuilder : public osmium::handler::Handler
{
  const osmium::memory::Buffer& buffer;
  const index_type& locations;
  const std::set<osmium::unsigned_object_id_type>& nodeSet;
  Graph g;

public:
  GraphBuilder(const osmium::memory::Buffer& buffer, const index_type&,
               const std::set<osmium::unsigned_object_id_type>&);
  void way(const osmium::Way&);
  Graph& get_graph();
};

inline Graph& GraphBuilder::get_graph()
{
  return g;
}
