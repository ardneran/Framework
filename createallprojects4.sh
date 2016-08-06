#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake4/premake4 --verbose --file=premake4.lua --os=macosx xcode4;xcodebuild -alltargets -configuration debug;xcodebuild -alltargets -configuration release;;
	linux*) ./Tools/Linux/premake4/premake4 --file=premake4.lua --os=linux gmake;make -j24;;
esac
