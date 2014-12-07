#pragma once

#include <set>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>

/*
 * Collects unique way nodes in an osm file.
 * nodeSet.size() will give you the number of nodes.
 */
struct NodeCounter : public osmium::handler::Handler
{
  std::set<osmium::object_id_type> nodeSet;

  void way(const osmium::Way&);
};
