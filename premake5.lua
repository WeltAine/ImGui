project "ImGui"
    location "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
        "imgui_internal.h",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp"
    }

    filter "configurations:Debug" --暂时没用，但先写着
        runtime "Debug" --使用调试版本的运行时库（比如msvcrtd.lib），以便在调试时能够获得更详细的错误信息和调试支持
        symbols "On" 

    filter "configurations:Release"
        runtime "Release" --使用发布版本的运行时库（比如msvcrt.lib），以获得更好的性能和较小的二进制文件
        optimize "On"