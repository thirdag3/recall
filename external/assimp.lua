-- ~/external/assimp.lua

externalproject "assimp"
    kind "StaticLib"
    language "C++"
    uuid "778694a0-4ec0-11ee-9027-0800200c9a66"

    location "assimp/build/code/"
    targetdir ("assimp/build/lib/" .. ((os.host == "windows") and "%{cfg.buildcfg}/" or ""))
    targetname ((os.host == "windows") and "assimp-vc143-mtd" or "assimp")

    os.execute "cmake -Sassimp/ -Bassimp/build/ -DBUILD_SHARED_LIBS=OFF"
    os.execute "cmake --build assimp/build/"
