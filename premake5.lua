require "vendor/premake/export-compile-commands"
-- require "export-compile-commands"

workspace "2d_gravity_sim"
   configurations { "Debug", "Release" }

project "2d_gravity_sim"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++23"
   -- staticruntime "Off"
   targetdir "bin/%{cfg.buildcfg}"
   toolset "clang"

   files { "**.h", "src/**.cpp", "src/**.c" }
   includedirs { "vendor/raylib/build/raylib/include", "src/include", "vendor/json/include" }

   links { "raylib" }

   -- defines { "" }

   filter "system:windows"
      ignoredefaultlibraries { "MSVCRT", "MSVCRTD"}
      -- VERY IMPORTANT WITHOUT THIS YOU WILL NEVER COMPILE AND GET 5 MILLION LINKER ERRORS
      linkoptions { "-Xlinker /NODEFAULTLIB:libcmt" }
      links { "winmm", "shell32", "user32", "gdi32"}
      libdirs { "vendor/raylib/build/raylib"}

   filter "system:linux"
      libdirs { "vendor/raylib/build-linux/raylib"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      -- runtime "Debug"     -- Use debug runtime (msvcrtd.lib or equivalent)

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      -- runtime "Release"   -- Use release runtime (msvcrt.lib or equivalent)

