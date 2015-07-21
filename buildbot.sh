#!/bin/bash

# This script is not relevant to you if you are´nt the buildbot, but
# feel free to explore it!

# OUT_DIR and SOURCE_DIR are defined by a 
# loader script on the buildserver. This script
# also cleans the directorys after the build.

# Set up required directorys
rm -rf $OUT_DIR/*
mkdir $OUT_DIR/logs
mkdir $OUT_DIR/misc

# Compile sources using Makefile
cd $SOURCE_DIR
make > $OUT_DIR/logs/build.log
make mkiso > $OUT_DIR/logs/mkiso.log


# Move files to the right directory
mv $SOURCE_DIR/kernel/build/lfos.bin $OUT_DIR/lfos.bin
mv $SOURCE_DIR/kernel/build/* $OUT_DIR/misc/
mv $SOURCE_DIR/iso/lfos.iso $OUT_DIR/lfos.iso

# Leave a timestamp
echo "Build successfull. Time: " + $(date) > $OUT_DIR/timestamp
