#!/bin/bash

case "$OSTYPE" in
	darwin*)
		sudo rm -rf /Library/Frameworks/SDL2.framework/;
		sudo cp -R Library/MacOS/SDL2-2.0.3/SDL2.framework /Library/Frameworks/;
		sudo codesign -f -s - /Library/Frameworks/SDL2.framework/SDL2;
		echo /Library/Frameworks/SDL2.framework/SDL2: copied and signed;
		sudo rm -rf /Library/Frameworks/SDL2_image.framework/;
		sudo cp -R Library/MacOS/SDL2_image-2.0.0/SDL2_image.framework /Library/Frameworks/;
		#sudo codesign -f -s - /Library/Frameworks/SDL2_image.framework/SDL2_image;
		echo /Library/Frameworks/SDL2_image.framework/SDL2_image: copied;
		sudo rm -rf /Library/Frameworks/SDL2_ttf.framework/;
		sudo cp -R Library/MacOS/SDL2_ttf-2.0.12/SDL2_ttf.framework /Library/Frameworks/;
		#sudo codesign -f -s - /Library/Frameworks/SDL2_ttf.framework/SDL2_ttf;
		echo /Library/Frameworks/SDL2_ttf.framework/SDL2_ttf: copied;
		;;
	linux*) TODO;;
esac
