#!/bin/bash

set -eu

cd $(dirname "${BASH_SOURCE[0]}")

failed=0

configuration=Release
platform=x86
type=test

while getopts "c:p:t:" opt; do
	case "${opt}" in
		c)
			configuration=${OPTARG}
			;;
		p)
			platform=${OPTARG}
			;;
		t)
			type=${OPTARG}
			;;
	esac
done

# TODO: is this right? might be better to check for Linux as Git Bash on Windows gives MINGW64_NT-10.0-19043
if [[ $(uname) == *"NT-"* ]]; then
	echo "Compiling on Windows"
	# hack - call out to Powershell because devenv.exe doesn't parse arguments correctly when called from git bash
	powershell ./build.ps1 $configuration $platform

	echo "Running unit tests on Windows"
	powershell ./unit-test.ps1 $configuration $platform

	echo "Running functional tests on Windows"

	if [[ $platform == "x86" ]]; then
		echo "Using x86 build"
		bin_path="../$configuration/sandbot-wptgen"
	elif [[ $platform == "x64" ]]; then
		echo "Using x64 build"
		bin_path="../$platform/$configuration/sandbot-wptgen"
	fi
elif [[ $(uname) == "Linux" ]]; then
	echo "Compiling on Linux for $type"
	make -C ../sandbot-wptgen clean

	if [[ $type == "test" ]]; then
		make -C ../sandbot-wptgen
	elif [[ $type == "gprof" ]]; then
		make -C ../sandbot-wptgen test-gprof
	elif [[ $type == "ubsan" ]]; then
		make -C ../sandbot-wptgen test-ubsan
	fi

	echo "Running functional tests on Linux"
	bin_path="../sandbot-wptgen/sandbot-wptgen"
fi

echo "Generating waypoint for bsp/bounce.bsp"
LSAN_OPTIONS=detect_leaks=0 $bin_path -w128 bsp/bounce.bsp > /dev/null
checksum=$(md5sum bounce.wpt | awk '{ print $1 }')

if [ $checksum != "925ab0267d50dbc2aa7e04c2819999f6" ]; then
	echo "Got checksum $checksum for bounce.wpt"
	failed=1
fi

gprof $bin_path ./gmon.out > bounce_perf.txt

echo "Generating waypoint for bsp/frenzy.bsp"
LSAN_OPTIONS=detect_leaks=0 $bin_path -w128 bsp/frenzy.bsp > /dev/null
checksum=$(md5sum frenzy.wpt | awk '{ print $1 }')

if [ $checksum != "624ef56371c50b5740e567882d865c37" ]; then
	echo "Got checksum $checksum for frenzy.wpt"
	failed=1
fi

gprof $bin_path ./gmon.out > frenzy_perf.txt

echo "Generating waypoint for bsp/op4_bootcamp.bsp"
LSAN_OPTIONS=detect_leaks=0 $bin_path -w128 bsp/op4_bootcamp.bsp > /dev/null
checksum=$(md5sum op4_bootcamp.wpt | awk '{ print $1 }')

if [ $checksum != "856e39c4819fc52db43feb8ee8f435ae" ]; then
	echo "Got checksum $checksum for op4_bootcamp.wpt"
	failed=1
fi

gprof $bin_path ./gmon.out > op4_bootcamp_perf.txt

echo Removing .wpt files
rm *.wpt

echo "Exit code $failed"
exit $failed
