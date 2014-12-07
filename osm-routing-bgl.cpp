#include <iostream>
#include <set>

#include <osmium/io/any_input.hpp>
#include <osmium/geom/haversine.hpp>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>

/*
 * Collects unique way nodes in an osm file.
 * nodeSet.size() will give you the number of nodes.
 */
struct NodeCounter : public osmium::handler::Handler
{
  std::set<osmium::object_id_type> nodeSet;

  void way(const osmium::Way& way)
  {
    const char *highway = way.tags()["highway"];

    if (highway)
    {
      for (const auto& node : way.nodes())
        nodeSet.emplace(node.ref());
    }
  }

};

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " OSMFILE\n";
    exit(1);
  }

  osmium::io::Reader
  reader(argv[1], osmium::osm_entity_bits::node | osmium::osm_entity_bits::way);

  NodeCounter node_counter;

  osmium::apply(reader, node_counter);

  std::cout <<
            "Number of nodes: "
            << node_counter.nodeSet.size()
            << std::endl;
}
