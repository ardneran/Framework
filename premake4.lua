-- A solution contains projects, and defines the available configurations
solution "Framework"
	configurations { "debug", "release" }

	-- Additional defines here
	-- defines {}

	-- Additional excludes here
	excludes { "External/SDL/**", "Library/SDL2/SDL2.framework/**" }

	-- Additional includedirs here
	includedirs { "include" }

	-- A project defines one build target
	project "Framework"
		kind "WindowedApp"
		language "C++"
		files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp" }
		files { "**.vert", "**.frag" }

		configuration "debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			targetdir ( "bin/debug" )
			objdir ( "obj/debug" )
			-- targetname ( "Framework" )

		configuration "release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			targetdir ( "bin/release" )
			objdir ( "obj/release" )
			-- targetname ( "Framework" )

		configuration "windows"
			linkoptions { }
			files { }
			excludes { "**/MacOS/**", "**/Linux/**" }

		configuration "macosx"
			linkoptions { "-framework CoreFoundation", "-framework OpenGL" }
			libdirs { "$HOME/Documents/Projects/GitHub/Framework/Library/SDL2/" }
			links { "SDL2" }
			files { "Library/SDL2/libSDL2.dylib" }


			includedirs { "$HOME/Documents/Projects/GitHub/Framework/Library/SDL2/SDL2.framework/Headers" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			linkoptions { "-lGL", "-lGLU", "-lGLEW", "-lX11", "-L/usr/lib/nvidia-331/" } -- hack for ubuntu 14.04 with nvidia-331
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
