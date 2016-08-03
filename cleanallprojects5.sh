#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake5/premake5 --verbose --file=premake5.lua --os=macosx clean;rm -rf Build;rm -rf Framework.xc*/;;
	linux*) ./Tools/Linux/premake5/premake5 --verbose --file=premake5.lua --os=linux clean;rm -rf Build;rm Makefile Framework.make;;
esac
