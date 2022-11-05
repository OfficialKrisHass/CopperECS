workspace "ECS"
    architecture "x64"
    configurations { "Debug", "Release" }

outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "ECS"
    location ""
    kind "ConsoleApp"
    language "C++"  
    cppdialect "C++17"

    targetdir("Build/" .. outputDir)
    objdir("BuildInt/" .. outputDir)

    files {

        "include/CopperECS/**.h",

        "src/**.h",
        "src/**.cpp"

    }

    includedirs {

        "src",
        "include/CopperECS"

    }