-- A solution contains projects, and defines the available configurations
solution "Framework"
	configurations { "debug", "release" }

	-- Additional defines here
	-- defines {}

	-- Additional includedirs here
	-- includedirs { "../External/SDL/include" }

	-- Additional excludes here
	excludes { "**/SDL/**" }

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
			buildoptions { "-fgnu89-inline" } -- hack for DevIL
			linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			linkoptions { "-lGL", "-lGLU", "-lGLEW", "-lX11", "-L/usr/lib/nvidia-331/" } -- hack for ubuntu 14.04 with nvidia-331
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
