#include "pch.h"
#include "DX11.h"

#include "MyMenu.h"

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;
bool get_present_pointer()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = GetForegroundWindow();
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGISwapChain* swap_chain;
    ID3D11Device* device;

    const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels, 2, D3D11_SDK_VERSION, &sd, &swap_chain, &device, nullptr, nullptr) == S_OK)
    {
        void** p_vtable = *reinterpret_cast<void***>(swap_chain);
        swap_chain->Release();
        device->Release();
        //context->Release();
        p_present_target = (present)p_vtable[8];
        return true;
    }
    return false;
}

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HWND window = NULL;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;
static long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {
    if (!init) {
        if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device)))
        {
            p_device->GetImmediateContext(&p_context);
            DXGI_SWAP_CHAIN_DESC sd;
            p_swap_chain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            // ImGui
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
            io.IniFilename = nullptr;
            io.LogFilename = nullptr;
            io.WantSaveIniSettings = false;
            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 15.0f);

            // custom style
            Menu->SetStyle();

            ImGui_ImplWin32_Init(window);
            ImGui_ImplDX11_Init(p_device, p_context);
            init = true;
        }
        else
            return p_present(p_swap_chain, sync_interval, flags);
    }
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    
    {
        Menu->Draw();
    }
    
    ImGui::EndFrame();
    
    ImGui::Render();
    p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return p_present(p_swap_chain, sync_interval, flags);
}

bool d3d11Menu::InitMenu() {
    if (!get_present_pointer()) return false;

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) return false;

    if (MH_CreateHook(reinterpret_cast<void**>(p_present_target), &detour_present, reinterpret_cast<void**>(&p_present)) != MH_OK) {
        return false;
    }

    if (MH_EnableHook(p_present_target) != MH_OK) {
        return false;
    }

    return true;
}

bool d3d11Menu::StopMenu() {
    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) return false;

    if (MH_Uninitialize() != MH_OK) return false;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
    if (p_context) { p_context->Release(); p_context = NULL; }
    if (p_device) { p_device->Release(); p_device = NULL; }
    SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));

    return true;
}
