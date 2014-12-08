#include <iostream>

#include <osmium/io/any_input.hpp>
#include "NodeCounter.h"
#include "NearestNode.h"
#include "GraphBuilder.h"
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

  GraphBuilder graph_builder(buffer, index, node_counter.nodeSet);
  auto g = graph_builder.get_graph();
  auto vertexIterators = boost::vertices(g);
  for (auto it = vertexIterators.first; it != vertexIterators.second; ++it)
  {
    std::cout << "ID: " << g[*it].id << ", location: " << g[*it].loc << std::endl;
  }

}
