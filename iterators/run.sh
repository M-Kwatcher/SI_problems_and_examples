#!/usr/bin/env bash

# Check if clang++ is available, otherwise fallback to g++
if command -v clang++ &>/dev/null; then
	COMPILER="clang++"
else
	COMPILER="g++"
fi

# Compile the source files
$COMPILER -std=c++17 main.cpp -o main

# Check if compilation was successful
if [ $? == 0 ]; then
	echo "Compilation successful. Running test..."
	# Run the executable
	./main
else
	echo "Compilation failed."
fi