#!/bin/bash

set -eu

cd $(dirname "${BASH_SOURCE[0]}")

failed=0

# TODO: is this right? might be better to check for Linux as Git Bash on Windows gives MINGW64_NT-10.0-19043
if [[ $(uname) == *"NT-"* ]]; then
	echo "Compiling on Windows"
	# hack - call out to Powershell because devenv.exe doesn't parse arguments correctly when called from git bash
	powershell ./build.ps1

	echo "Running on Windows"
	bin_path="../Debug/sandbot-wptgen"
elif [[ $(uname) == "Linux" ]]; then
	echo "Compiling on Linux"
	make -c ../sandbot-wptgen clean
	make -c ../sandbot-wptgen

	echo "Running on Linux"
	bin_path="../sandbot-wptgen/sandbot-wptgen"
fi

echo "Generating waypoint for bsp/bounce.bsp"
$bin_path -w128 bsp/bounce.bsp > /dev/null
checksum=$(md5sum bounce.wpt | awk '{ print $1 }')

if [ $checksum != "925ab0267d50dbc2aa7e04c2819999f6" ]; then
	echo "Got checksum $checksum for bounce.wpt"
	failed=1
fi

echo "Generating waypoint for bsp/frenzy.bsp"
$bin_path -w128 bsp/frenzy.bsp > /dev/null
checksum=$(md5sum frenzy.wpt | awk '{ print $1 }')

if [ $checksum != "624ef56371c50b5740e567882d865c37" ]; then
	echo "Got checksum $checksum for frenzy.wpt"
	failed=1
fi

echo "Generating waypoint for bsp/op4_bootcamp.bsp"
$bin_path -w128 bsp/op4_bootcamp.bsp > /dev/null
checksum=$(md5sum op4_bootcamp.wpt | awk '{ print $1 }')

if [ $checksum != "856e39c4819fc52db43feb8ee8f435ae" ]; then
	echo "Got checksum $checksum for op4_bootcamp.wpt"
	failed=1
fi

echo Removing .wpt files
rm *.wpt

echo "Exit code $failed"
exit $failed
