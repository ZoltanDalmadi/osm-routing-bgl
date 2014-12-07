#pragma once

#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>
#include <osmium/index/map/vector.hpp>
typedef osmium::index::map::VectorBasedSparseMap<osmium::unsigned_object_id_type,
        osmium::Location, std::vector> index_type;

/*
 * Finds nearest node to location passed in the constructor.
 */
class NearestNode : public osmium::handler::Handler
{
  const osmium::Location& loc;
  double min = 100000.0;
  osmium::unsigned_object_id_type node_id;
  const index_type& locations;

public:
  NearestNode(const osmium::Location&, const index_type&);
  void way(const osmium::Way&);
  osmium::unsigned_object_id_type get() const;
};

inline osmium::unsigned_object_id_type NearestNode::get() const
{
  return node_id;
}
