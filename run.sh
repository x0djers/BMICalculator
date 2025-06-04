#!/bin/bash

BIN_NAME="bin/server"
make

clear

if [ $? -eq 0 ]; then
    ./$BIN_NAME
else
    echo "Build error"
fi