# OSM Routing with Boost Graph Library

## Prerequisites

[boost-graph](http://www.boost.org/)

[libosmium](http://osmcode.org/libosmium/)

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

#### Server wrapper

For the server wrapper script you need
[Python](https://www.python.org/) and [Flask](http://flask.pocoo.org/).

The script handles input coordinates from a single URL
(`/start_lan-start_lon-target_lan-target_lon`), and returns node coordinates
in JSON format.
