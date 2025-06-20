require "export-compile-commands"

workspace "2d_gravity_sim"
   configurations { "Debug", "Release" }

project "2d_gravity_sim"
   kind "WindowedApp"
   ignoredefaultlibraries { "MSVCRT", "MSVCRTD"}
   language "C++"
   cppdialect "C++23"
   -- staticruntime "Off"
   targetdir "bin/%{cfg.buildcfg}"
   toolset "clang"

   files { "**.h", "src/**.cpp", "src/**.c" }
   includedirs { "vendor/raylib/build/raylib/include", "src/include", "vendor/json/include" }
   libdirs { "vendor/raylib/build/raylib"}

   links { "raylib" }

   -- VERY IMPORTANT WITHOUT THIS YOU WILL NEVER COMPILE AND GET 5 MILLION LINKER ERRORS
   linkoptions { "-Xlinker /NODEFAULTLIB:libcmt" }
   -- defines { "" }

   filter "system:windows"
      links { "winmm", "shell32", "user32", "gdi32"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"
      buildoptions {
        "-g",
        "-fstandalone-debug",
        "-O0",
        "-fno-omit-frame-pointer",
      }
      -- runtime "Debug"     -- Use debug runtime (msvcrtd.lib or equivalent)

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      -- runtime "Release"   -- Use release runtime (msvcrt.lib or equivalent)

