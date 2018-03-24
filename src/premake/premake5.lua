require "projectTemplate"

workspace ("Helltooth")
    configurations {
        "Debug-GL",
        "Release-GL",
        "Debug-DX",
        "Release-DX",
    }

    platforms {
        "x86",
        "x64",
    }

    location "../../Solution/"
    startproject "Sandbox"

makeProject("Helltooth-ShadingLanguage")
	kind ("StaticLib")
	files {
		"../Helltooth-ShadingLanguage/src/htsl/**.hpp",
		"../Helltooth-ShadingLanguage/src/htsl/**.cpp",
	}
	includedirs {
		"../Helltooth-ShadingLanguage/src/htsl/"
	}

makeProject ("Helltooth")
    kind ("StaticLib")
    files {
        "../engine/**.hpp",
        "../engine/**.cpp",
    }
	dependson "Helltooth-ShadingLanguage"
    includedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
	}

makeProject ("Sandbox")
    kind ("ConsoleApp")
    files {
        "../demo/**.h",
        "../demo/**.hpp",
        "../demo/**.cpp",
        "../../Solution/Sandbox/res/*/*.*"
    }
	dependson {
		"Helltooth",
		"Helltooth-ShadingLanguage",
	}
	
    links {
		"Helltooth.lib",
		"Helltooth-ShadingLanguage.lib",
	}
	filter {"configurations:Debug-GL"}
		links {
			"opengl32"
		}
	filter {"configurations:Release-GL"}
		links {
			"opengl32"
		}
	filter {"configurations:Debug-DX"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {"configurations:Release-DX"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {}
	
	sysincludedirs {
		"../engine/",
		"../Helltooth-ShadingLanguage/src/htsl/",
	}

	syslibdirs {
		"../../bin/Helltooth/",
		"../../bin/Helltooth-ShadingLanguage/",
	}