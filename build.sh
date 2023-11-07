#!/bin/bash


# Default compile threads
num_jobs=1
target=template_debug


# Check if 2 arguments are present
if [ "$#" -ge 2 ]; then
  num_jobs="$1"
  target_value="$2"
else
  echo "Usage: $0 <num_jobs> <target>"
  exit 1
fi


scons -Q -j$num_jobs target="$target"
