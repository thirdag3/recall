-- ~/Source/Kreckanism/premake5.lua

project "Recall"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "**.h", "**.hpp", "**.cpp" }

    includedirs
    {
        "%{wks.location}/src/",
        "%{wks.location}/external/glad/include",
        "%{wks.location}/external/glfw/include",
        "%{wks.location}/external/glm",
        "%{wks.location}/external/imgui",
        "%{wks.location}/external/assimp/include",
        "%{wks.location}/external/assimp/build/include/",
        "%{wks.location}/external/stb/"
    }

    filter "system:linux"
        links { "glfw", "glad", "imgui", "GL", "rt", "m", "dl", "X11", "pthread", "assimp" }

    filter "system:windows"
        links { "glfw", "glad", "imgui", "opengl32", "assimp"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
