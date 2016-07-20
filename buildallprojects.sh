#!/bin/bash

case "$OSTYPE" in
        darwin*) xcodebuild -workspace Framework.xcworkspace -scheme Framework;;
        linux*) make -j24;;
esac
