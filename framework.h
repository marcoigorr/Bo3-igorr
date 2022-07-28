#pragma once
#pragma warning(disable : 6387)

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <cstdint>
#include <Psapi.h>
#include <vector>

#include "MinHook/MinHook.h" // $(SolutionDir)\MinHook;
#pragma comment(lib, "MinHook/libMinHook.x64.lib")


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// mine
#include "mem.h"