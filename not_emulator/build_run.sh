#!/bin/bash

# build game & run it
# all arguments are propagated to build.sh script

./build.sh "$1"

./bin/"$1"
