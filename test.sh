#!/bin/bash

set -e

./sandbot-wptgen bsp/bounce.bsp
bounce_checksum=$(md5sum bounce.wpt)
