-- A solution contains projects, and defines the available configurations
solution "Framework"
	configurations { "debug", "release" }

	-- Additional defines here
	-- defines {}

	-- Additional excludes here
	excludes { "Library/**" }

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
			platforms { "x64" }
			buildoptions { "/ILibrary/Windows/SDL2-2.0.3/include" }
			-- following single line can be used instead of the libdirs and links combination
			-- linkoptions { "/LIBPATH:Library/Windows/SDL2-2.0.3/lib/x64", "SDL2.lib", "SDL2main.lib" }
			libdirs { "Library/Windows/SDL2-2.0.3/lib/x64" }
			links { "SDL2", "SDL2main" }
			files { }
			excludes { "**/MacOS/**", "**/Linux/**" }

		configuration "macosx"
			buildoptions { "-I/Library/Frameworks/SDL2.framework/Headers", "-I/Library/Frameworks/SDL2_image.framework/Headers", "-I/Library/Frameworks/SDL2_ttf.framework/Headers" }
			linkoptions { "-framework CoreFoundation", "-framework OpenGL", "-framework SDL2", "-framework SDL2_image", "-framework SDL2_ttf", "-F/Library/Frameworks" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			linkoptions { "-lGL", "-lGLU", "-lGLEW", "-lX11", "-L/usr/lib/nvidia-331/" } -- hack for ubuntu 14.04 with nvidia-331
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
