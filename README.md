#Framework

**Mac OS**

1. Download Development Libraries for Mac OS X from https://www.libsdl.org/download-2.0.php
2. Copy SDL2.framework to /Library/Frameworks
3. Terminal codesign -f -s - /Library/Frameworks/SDL2.framework/SDL2
4. Current version SDL2-2.0.3.dmg

**Windows**

1. Download Development Libraries for Windows from https://www.libsdl.org/download-2.0.php
2. Run deploylibraries.bat as administrator to copy dll files into appropriate directories
