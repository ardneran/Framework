-- A solution contains projects, and defines the available configurations
solution "Framework"
	configurations { "debug", "release" }

	-- Additional defines here
	-- defines {}

	-- Additional excludes here
	excludes { "Library/**" }

	-- Additional includedirs here
	includedirs { "Include", "External/**/Include" }

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
			frameworkdirs { "Library/MacOS/SDL2-2.0.3", "Library/MacOS/SDL2_image-2.0.0", "Library/MacOS/SDL2_ttf-2.0.12" }
			linkoptions { "-framework SDL2", "-framework SDL2_image", "-framework SDL2_ttf", "-framework OpenGL" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			buildoptions { "-I/usr/include/SDL2" }
			linkoptions { "-lGL", "-lGLU", "-lSDL2", "-lSDL2_image", "-lSDL2_ttf", "-L/usr/lib/nvidia-352/" } -- hack for nvidia driver with which graphics debugger works
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
