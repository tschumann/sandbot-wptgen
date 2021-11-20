#!/bin/bash

set -e

cd $(dirname "${BASH_SOURCE[0]}")

./sandbot-wptgen bsp/bounce.bsp
bounce_checksum=$(md5sum bounce.wpt)
