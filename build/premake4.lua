-- A solution contains projects, and defines the available configurations
solution "kinect"
    configurations "Release"
	files { "../**.h", "../**.cpp" }
	links = iif (os.is("windows"), { "pthread", "ws2_32" }, "pthread")

	-- A project defines one build target
	project "kinect_test"
		kind "ConsoleApp"
		language "C++"

	project "kinect"
		--kind "StaticLib"
		kind "SharedLib"
		language "C++"
		--excludes { "../main.cpp", "../wave.cpp", "../wave.h" }
