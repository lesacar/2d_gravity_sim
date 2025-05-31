require "export-compile-commands"

workspace "2d_gravity_sim"
   configurations { "Debug", "Release" }

project "2d_gravity_sim"
   kind "WindowedApp"
   language "C++"
   staticruntime "On"
   targetdir "bin/%{cfg.buildcfg}"
   toolset "clang"

   files { "**.h", "**.cpp" }
   includedirs { "vendor/raylib/build/raylib/include", "src/include", "vendor/json/include" }
   libdirs { "vendor/raylib/build/raylib" }

   links { "raylib" }
   -- defines { "" }

   filter "system:windows"
      links { "winmm", "shell32", "user32", "gdi32" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

