REM Tools\Windows\premake5\premake5 --file=premake5.lua --os=windows vs2013
Tools\Windows\premake4\premake4 --file=premake4.lua --os=windows vs2012
msbuild Framework.sln /m /p:Configuration=Debug
msbuild Framework.sln /m /p:Configuration=Release
