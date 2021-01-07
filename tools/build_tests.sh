# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

#!/bin/bash

# Use paths relative to this script's location
SCRIPT=$(readlink -f "$0")
SCRIPTDIR=$(dirname "$SCRIPT")
BASEDIR=$(dirname "$SCRIPTDIR")

# If you want to build into a different directory, change this variable
SOURCEDIR="$BASEDIR/tests/native"
BUILDDIR="$BASEDIR/build/"

# Generate the build system using Ninja
cmake -B"$BUILDDIR" -GNinja -S"$SOURCEDIR"

# And then do the build
cmake --build $BUILDDIR -j 4 -- -v