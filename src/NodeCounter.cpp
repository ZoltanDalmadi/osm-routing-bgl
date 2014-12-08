#include "NodeCounter.h"

void NodeCounter::way(const osmium::Way& way)
{
  const char *highway = way.tags()["highway"];

  if (highway)
  {
    for (const auto& node : way.nodes())
      nodeSet.emplace(node.positive_ref());
  }
}
