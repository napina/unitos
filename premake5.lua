solution "unitos"
	location( "build/" .. _ACTION )
	targetdir "lib"
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }

    include "unitos.lua"