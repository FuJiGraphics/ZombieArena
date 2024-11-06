workspace "Solution"
	startproject "Zombie"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
	}

	flags
	{
		"MultiProcessorCompile"
	}

project "Zombie"
	location "Zombie"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

pchheader "stdafx.h"
pchsource "%{wks.location}/%{prj.name}/src/Framework/stdafx.cpp"

targetdir("%{wks.location}/bin/%{cfg.buildcfg}/")
objdir("%{wks.location}/bin-int/%{cfg.buildcfg}/")
debugdir("%{wks.location}/bin/%{cfg.buildcfg}/")

files
{
	"**.cpp",
	"**.h",
}

includedirs
{
	"%{wks.location}/%{prj.name}/src",
	"%{wks.location}/%{prj.name}/src/Framework/",
	"%{wks.location}/vendor/SFML-2.6.1/include/",
}

libdirs
{
	"%{wks.location}/vendor/SFML-2.6.1/lib/%{cfg.buildcfg}/",
}

links
{
	"sfml-audio.lib",
	"sfml-graphics.lib",
	"sfml-main.lib",
	"sfml-network.lib",
	"sfml-system.lib",
	"sfml-window.lib",
}

filter "system:Windows"

defines
{
	"PPC_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
	defines "PPC_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "PPC_RELEASE"
	runtime "Release"
	optimize "On"
