#include <iostream>
#include <osmium/io/any_input.hpp>
#include <osmium/index/map/vector.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>
#include "NodeCounter.h"
#include "NearestNode.h"
#include "GraphBuilder.h"
#include "RoutePlanner.h"

typedef osmium::index::map::VectorBasedSparseMap<osmium::unsigned_object_id_type,
        osmium::Location, std::vector> index_type;
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
  osmium::apply(buffer, graph_builder);

  osmium::Location start(21.654696, 47.506214);
  osmium::Location dest(21.641735, 47.542583);

  RoutePlanner route_planner(graph_builder, start, dest);

  for (const auto& l : route_planner.get_route())
  {
    std::cout << l.lat() << " " << l.lon() << std::endl;
  }

  double sum_distance = 0.0f;

  for (const auto& d : route_planner.get_distances())
    sum_distance += d;

  std::cout << "total distance: " << sum_distance / 1000 << " km" << std::endl;
}
