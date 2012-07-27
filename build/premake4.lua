-- A solution contains projects, and defines the available configurations
solution "kinect"
    configurations "Release"
	links = iif (os.is("windows"), { "pthread", "ws2_32" }, "pthread")

	-- A project defines one build target
	project "kinect"
		kind "StaticLib"
		--kind "SharedLib"
		language "C++"
		files { "../src/**.h", "../src/**.cpp" }
		excludes "../src/main.cpp" 
