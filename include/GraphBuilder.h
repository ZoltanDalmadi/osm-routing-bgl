#pragma once

#include <set>
#include <map>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>
#include <osmium/index/map/vector.hpp>
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

typedef osmium::index::map::VectorBasedSparseMap<osmium::unsigned_object_id_type,
        osmium::Location, std::vector> index_type;

typedef boost::adjacency_list <boost::listS, boost::vecS, boost::undirectedS,
        VertexProperty, EdgeProperty> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::map<osmium::unsigned_object_id_type, Vertex> vertex_map_t;

/*
 * Builds a graph from the buffer passed in the constructor.
 */
class GraphBuilder : public osmium::handler::Handler
{
  const osmium::memory::Buffer& buffer;
  const index_type& locations;
  const std::set<osmium::unsigned_object_id_type>& nodeSet;
  Graph g;
  vertex_map_t vertexMap;

public:
  GraphBuilder(const osmium::memory::Buffer& buffer, const index_type&,
               const std::set<osmium::unsigned_object_id_type>&);
  void way(const osmium::Way&);
  const osmium::memory::Buffer& get_buffer() const;
  const index_type& get_locations() const;
  const Graph& get_graph() const;
  const vertex_map_t& get_vertex_map() const;
};

inline const osmium::memory::Buffer& GraphBuilder::get_buffer() const
{
  return buffer;
}

inline const index_type& GraphBuilder::get_locations() const
{
  return locations;
}

inline const Graph& GraphBuilder::get_graph() const
{
  return g;
}

inline const vertex_map_t& GraphBuilder::get_vertex_map() const
{
  return vertexMap;
}
