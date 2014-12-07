#include <iostream>

#include <osmium/io/any_input.hpp>
#include "NodeCounter.h"
#include "NearestNode.h"
#include <osmium/index/map/vector.hpp>
typedef osmium::index::map::VectorBasedSparseMap<osmium::unsigned_object_id_type,
        osmium::Location, std::vector> index_type;

#include <osmium/handler/node_locations_for_ways.hpp>
typedef osmium::handler::NodeLocationsForWays<index_type> location_handler_type;

int main(int argc, char *argv[])
{
  // Print usage
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " OSMFILE\n";
    exit(1);
  }

  // Initialize osm file reader
  osmium::io::Reader
  reader(argv[1], osmium::osm_entity_bits::node | osmium::osm_entity_bits::way);
  auto buffer = reader.read();
  reader.close();

  index_type index;
  location_handler_type location_handler(index);

  // Count number of nodes in ways
  NodeCounter node_counter;
  osmium::apply(buffer, node_counter, location_handler);

  auto numOfNodes = node_counter.nodeSet.size();
  std::cout << "Number of nodes: " << numOfNodes << std::endl;

  // nearestnode test
  osmium::Location loc(21.42, 47.12);
  NearestNode nearest_node(loc, index);
  osmium::apply(buffer, nearest_node);
  std::cout << nearest_node.get() << std::endl;
}
