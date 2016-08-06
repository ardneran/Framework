#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake5/premake5 --verbose --file=premake5.lua --os=macosx xcode4;xcodebuild -alltargets -configuration debug;xcodebuild -alltargets -configuration release;;
	linux*) ./Tools/Linux/premake5/premake5 --verbose --file=premake5.lua --os=linux gmake;make -j24;;
esac
