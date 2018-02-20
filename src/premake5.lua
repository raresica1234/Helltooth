function setProjectOutputDirectories() 
	objdir "$(SolutionDir)\\Intermediates\\"
	targetdir "$(SolutionDir)\\bin\\$(Platform)\\$(Configuration)\\$(ProjectName)\\"
end

function setConfigurationFilters() 
	filter {"configurations:OpenGL-Debug"}
		defines {
			"HT_OPENGL",
			"HT_DEBUG"
		}
	filter {"configurations:OpenGL-Release"}
		defines {
			"HT_OPENGL",
			"HT_RELEASE"
		}
		optimize "Full"
    	symbols "Off"
	filter {"configurations:DirectX-Debug"}
		defines {
			"HT_DIRECTX",
			"HT_DEBUG"
		}
	filter {"configurations:DirectX-Release"}
		defines {
			"HT_DIRECTX",
			"HT_RELEASE"
		}
		optimize "Full"
    	symbols "Off"
	filter {"platforms:x86"}
		defines {
			"HT_WINDOWS"
		}
	filter {"platforms:x64"}
		defines {
			"HT_WINDOWS"
		}
	filter {}
end


workspace ("Helltooth")
    configurations {
        "OpenGL-Debug",
        "OpenGL-Release",
        "DirectX-Debug",
        "DirectX-Release",
    }

    platforms {
        "x86",
        "x64",
    }

    location "../Solution/"
    startproject "Sandbox"

project ("Helltooth")
    kind ("StaticLib")
    files {
        "engine/**.hpp",
        "engine/**.cpp",
    }
    location "../Solution/Helltooth/"
    includedirs {
		"$(SolutionDir)../src/engine/"
	}

    setProjectOutputDirectories() 
    setConfigurationFilters()

project ("Sandbox")
    kind ("ConsoleApp")
    files {
        "demo/**.h",
        "demo/**.hpp",
        "demo/**.cpp",
        "../Solution/Sandbox/res/*/*.*"
    }
    location "../Solution/Sandbox/"
    dependson "Helltooth"
    links {
		"Helltooth.lib",
	}
	filter {"configurations:OpenGL-Debug"}
		links {
			"opengl32"
		}
	filter {"configurations:OpenGL-Release"}
		links {
			"opengl32"
		}
	filter {"configurations:DirectX-Debug"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {"configurations:DirectX-Release"}
		links {
			"D3D11",
			"d3dcompiler"
		}
	filter {}
	
	sysincludedirs {
		"$(SolutionDir)../src/engine/"
	}

	syslibdirs {
		"$(SolutionDir)bin\\$(Platform)\\$(Configuration)\\Helltooth\\"
	}

    setProjectOutputDirectories() 
    setConfigurationFilters()