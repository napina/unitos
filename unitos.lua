project "unitos"
	uuid "1F4C0F6C-EF92-DF47-AE6C-04F9BD24AC5E"
	kind "StaticLib"
	language "C++"
	files { 
		"include/**.h",
		"include/**.inl",
		"src/**.cpp",
	}
	includedirs { "include" }
	objdir( "build/" .. _ACTION )
	location( "build/" .. _ACTION )
	targetdir "lib"
	
	flags { "FatalWarnings", "NoBufferSecurityCheck", "NoEditAndContinue", "NoIncrementalLink", "NoPCH", "NoRTTI" }
	warnings "Extra"

	configuration "Debug"
		defines { "DEBUG", "_ITERATOR_DEBUG_LEVEL=0" }
		flags { "Symbols" }
		targetsuffix "_d"

	configuration "Release"
		defines { "NDEBUG" }
		flags { "NoRuntimeChecks" }
		targetsuffix "_r"
		optimize "Speed"
