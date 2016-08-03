#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake4/premake4 --file=premake4.lua --os=macosx clean;rm -rf Build;;
	linux*) ./Tools/Linux/premake4/premake4 --file=premake4.lua --os=linux clean;rm -rf Build;;
esac
