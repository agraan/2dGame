workspace "MyGame"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    startproject "MyGame"

---------------------------------------------------------------------
-- 📦 setup: clone + build all external libraries automatically
---------------------------------------------------------------------
newaction {
    trigger     = "setup",
    description = "Download and build SDL2, SDL2_image, SDL2_ttf, and GLEW",
    execute     = function()
        local deps = {
            { "SDL2",       "https://github.com/libsdl-org/SDL.git" },
            { "SDL2_image", "https://github.com/libsdl-org/SDL_image.git" },
            { "SDL2_ttf",   "https://github.com/libsdl-org/SDL_ttf.git" },
            { "glew",       "https://github.com/nigels-com/glew.git" }
        }

        os.mkdir("external")

        for _, dep in ipairs(deps) do
            local name, url = dep[1], dep[2]
            local path = "external/" .. name
            local buildPath = path .. "/build"
            if not os.isdir(path) then
                local tag = ""
                if name == "SDL2" then tag = "release-2.30.2"
                elseif name == "SDL2_image" then tag = "release-2.8.2"
                elseif name == "SDL2_ttf" then tag = "release-2.22.0"
                end
                local cloneCmd = string.format('git clone --depth=1 --branch %s %s %s', tag, url, path)
                print("📥 Cloning " .. name .. " (" .. tag .. ")")
                os.execute(cloneCmd)
            else
                print("✅ " .. name .. " already present.")
            end

			print("⚙️  Building " .. name)
			os.mkdir(buildPath)

			local generator = ""
			if os.host() == "windows" then
				generator = '-G "Visual Studio 17 2022" -A x64'
			elseif os.host() == "linux" then
				generator = '-G "Unix Makefiles"'
			elseif os.host() == "macosx" then
				generator = '-G "Xcode"'
			end

			-- extra flags
			local extraFlags = ""
			if name == "SDL2_ttf" then
				local ftDir = path .. "/external/freetype"
				local dlScript = path .. "/external/download.sh"
				if not os.isdir(ftDir) then
					print("📦 Downloading FreeType for SDL2_ttf...")
					os.execute("chmod +x " .. dlScript)
					os.execute(dlScript)
				end
				extraFlags = "-DSDL2TTF_VENDORED=ON"
			end
			os.execute(string.format(
				'cmake -S %s -B %s %s -DCMAKE_BUILD_TYPE=Release %s',
				path, buildPath, generator, extraFlags
			))
			os.execute(string.format('cmake --build %s --config Release -j', buildPath))
		end
    end
}

---------------------------------------------------------------------
-- 🎮 Game project
---------------------------------------------------------------------
project "MyGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    files { "src/**.cpp", "include/**.hpp" }

    includedirs {
        "include",
        "external/SDL2/include",
        "external/SDL2_image/include",
        "external/SDL2_ttf/include",
        "external/glew/include"
    }

    libdirs {
        "external/SDL2/build/Release",
        "external/SDL2_image/build/Release",
        "external/SDL2_ttf/build/Release",
        "external/glew/build/lib/Release",
        "external/glew/lib/Release",
        "external/glew/lib"
    }

    filter "system:windows"
        links { "SDL2", "SDL2main", "SDL2_image", "SDL2_ttf", "glew32", "opengl32" }

    filter "system:linux"
        links { "SDL2", "SDL2_image", "SDL2_ttf", "GLEW", "GL", "pthread", "dl" }

    filter "system:macosx"
        links { "SDL2", "SDL2_image", "SDL2_ttf", "GLEW" }
        links { "OpenGL.framework", "Cocoa.framework" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    postbuildcommands {
        "{COPYDIR} assets %{cfg.targetdir}/assets"
    }

