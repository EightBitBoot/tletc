workspace "TLETC"
    configurations {"debug", "release"}

project "tletc"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}"

    files {"src/**.h", "src/**.cpp"}

    includedirs {"src/"}

    links {"m", "GL", "glfw", "GLEW"}

    filter "configurations:debug"
        defines {"TLETC_DEBUG"}
        symbols "On"

    filter "configurations:release"
        symbols "Off"
        optimize "On"

-- REMINDER: Always add new generated files to this action
--           This is the common workaround to a known
--           limitation of premake
newaction {
    trigger = "clean",
    description = "Clean all generated files",
    execute = function()
        print("Removing makefiles")
        os.remove("*.make")
        os.remove("Makefile")

        print("Removing output files")
        os.rmdir("build")
        os.rmdir("bin")
    end
}