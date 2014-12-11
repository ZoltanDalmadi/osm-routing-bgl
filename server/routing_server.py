#!/usr/bin/env python
# encoding: utf-8

from flask import Flask, json
import subprocess


# Change to actual file locations
ROUTING_APP = "~/work/osm/osm-routing-bgl/dist/osm-routing-bgl"
OSMFILE = "~/Desktop/debrecen.osm"

app = Flask(__name__)


@app.route('/<startlat>-<startlon>-<endlat>-<endlon>')
def coords(startlat, startlon, endlat, endlon):

    sb = []
    sb.append(ROUTING_APP)
    sb.append(OSMFILE)
    sb.append(startlat)
    sb.append(startlon)
    sb.append(endlat)
    sb.append(endlon)

    command = " ".join(sb)

    output = subprocess.getoutput(command)

    dic = {}

    for index, line in enumerate(output.splitlines(), 1):
        c = line.split()
        dic[index] = c

    return json.jsonify(dic)


if __name__ == "__main__":
    app.run(host='0.0.0.0')
