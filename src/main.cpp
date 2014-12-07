#include <iostream>

#include <osmium/io/any_input.hpp>
#include "NodeCounter.h"

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
