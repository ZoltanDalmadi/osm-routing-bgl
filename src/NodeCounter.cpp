#include "NodeCounter.h"

void NodeCounter::way(const osmium::Way& way)
{
  for (const auto& node : way.nodes())
    nodeSet.emplace(node.positive_ref());
}
