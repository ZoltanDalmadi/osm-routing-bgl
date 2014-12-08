#pragma once

#include "NearestNode.h"
#include "GraphBuilder.h"

/*
 * Finds shortest path between 2 coordinates using the Dijkstra algorithm.
 */
class RoutePlanner
{
private:
  const GraphBuilder& gb;
  const osmium::Location start;
  const osmium::Location destination;
  std::vector<osmium::Location> route;

public:
  RoutePlanner(const GraphBuilder& gb,
               const osmium::Location& start, const osmium::Location& dest);
  const std::vector<osmium::Location>& get_route() const;
};

inline const std::vector<osmium::Location>& RoutePlanner::get_route() const
{
  return route;
}
