#!/bin/bash

case "$OSTYPE" in
        darwin*) xcodebuild -alltargets -configuration debug;xcodebuild -alltargets -configuration release;;
        linux*) make -j24;;
esac
