solution "libkinect"
    configurations "Release"
	links = iif (os.is("windows"), { "pthread", "ws2_32" }, "pthread")
	language "C++"
	files { "../src/**.h", "../src/**.cpp" }
	excludes "../src/main.cpp" 

	project "kinect_static"
		kind "StaticLib"
		targetname "kinect"

	project "kinect_shared"
		kind "SharedLib"
		targetname "kinect"
