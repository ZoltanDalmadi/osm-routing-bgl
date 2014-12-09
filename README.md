# OSM Routing with Boost Graph Library

### Build

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

The executable will be in the "dist" directory.

### Run

You'll need an osm file, e. g:
    $ wget http://reccos.inf.unideb.hu/~norbi/res/debrecen.osm

From the "dist" directory:
    $ osm-routing-bgl path/to/osm/file start_lan start_lon target_lat target_lon
