#include <iostream>
#include "NearestNode.h"

NearestNode::NearestNode(const osmium::Location& loc, const index_type& locs)
  : loc(loc), locations(locs)
{
}

void NearestNode::way(const osmium::Way& way)
{
  for (const auto& node_ref : way.nodes())
  {
    auto current = locations.get(node_ref.positive_ref());
    double dx = loc.lon() - current.lon();
    double dy = loc.lat() - current.lat();
    double dist = dx * dx + dy * dy;

    if (dist < min)
    {
      min = dist;
      node_id = node_ref.positive_ref();
    }
  }
}
