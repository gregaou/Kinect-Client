-- A solution contains projects, and defines the available configurations
solution "kinect"
    configurations "Release"
	files { "../**.h", "../**.cpp" }

	-- A project defines one build target
	project "kinect_test"
		language "C++"
		kind "ConsoleApp"
		links = iif (os.is("windows"), { "pthread", "ws2_32" }, "pthread")

	project "kinect"
		kind "SharedLib"
		language "C++"
		links = iif (os.is("windows"), { "pthread", "ws2_32" }, "lpthread")
		excludes { "../main.cpp", "../wave.cpp", "../wave.h" }
