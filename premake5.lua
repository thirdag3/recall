-- ~/premake5.lua

workspace "Recall"
    configurations { "Debug", "Release" }
    startproject "Recall"
    architecture "x86_64"

include "external/glad.lua"
include "external/glfw.lua"
include "external/imgui.lua"
include "external/assimp.lua"

include "src/"
