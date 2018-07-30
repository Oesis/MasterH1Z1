#include "stdafx.h"
#include "D3D11Hooks.h"

#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_dx11.h"

#include "Visuals.h"
//#include <d3dcompiler.h>

//#pragma comment( lib, "d3d9.lib" )
//#pragma comment( lib, "d3dx9.lib" )
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dcompiler.lib")
//#pragma comment(lib, "d3dx11.lib")

bool doInit = true;

namespace D3D11
{
	ID3D11Device * pDevice = nullptr;
	ID3D11DeviceContext * pContext = nullptr;
	IDXGISwapChain * pSwapChain = nullptr;
	ID3D11RenderTargetView * pRenderTargetView = nullptr;

	//original Function
	tD3D11Present oPresent = NULL;

	void Initialize()
	{
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		HWND hWindow = FindWindowA("H1Z1 PlayClient (Live)", NULL); // TODO: Modify this.
		std::cout << "[D3D11] hWindows = " << hWindow << std::endl;
#pragma region Initialise DXGI_SWAP_CHAIN_DESC
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(scd));

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // sets color formatting, we are using RGBA
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // says what we are doing with the buffer
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // msdn explains better than i can: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173076(v=vs.85).aspx
		scd.OutputWindow = hWindow; // our gamewindow, obviously
		scd.SampleDesc.Count = 1; // Set to 1 to disable multisampling
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // D3D related stuff, cant really describe what it does
		scd.Windowed = ((GetWindowLongPtr(hWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true; // check if our game is windowed
		scd.BufferDesc.Width = 1920; // temporary width
		scd.BufferDesc.Height = 1080; // temporary height
		scd.BufferDesc.RefreshRate.Numerator = 60; // refreshrate in Hz
		scd.BufferDesc.RefreshRate.Denominator = 1; // no clue, lol
#pragma endregion

		if (FAILED(D3D11CreateDeviceAndSwapChain(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
			NULL, &featureLevel, 1, D3D11_SDK_VERSION,
			&scd, &D3D11::pSwapChain,
			&D3D11::pDevice, NULL, &D3D11::pContext
		)))
		{// failed to create D3D11 device
			return;
			std::cout << "[D3D11] failed to create D3D11 device\n";
		}

		std::cout << "[D3D11] created D3D11Device\n";


		//Get VTable Pointers
		DWORD_PTR* pSwapChainVT = reinterpret_cast<DWORD_PTR*>(D3D11::pSwapChain);
		DWORD_PTR* pDeviceVT = reinterpret_cast<DWORD_PTR*>(D3D11::pDevice); // Device not needed, but prolly need it to draw stuff in Present, so it is included
		DWORD_PTR* pContextVT = reinterpret_cast<DWORD_PTR*>(D3D11::pContext);

		//Pointer->Table
		pSwapChainVT = reinterpret_cast<DWORD_PTR*>(pSwapChainVT[0]);
		pDeviceVT = reinterpret_cast<DWORD_PTR*>(pDeviceVT[0]);
		pContextVT = reinterpret_cast<DWORD_PTR*>(pContextVT[0]);

		D3D11::oPresent = reinterpret_cast<tD3D11Present>(pSwapChainVT[8]); // Present Function
		std::cout << "[D3D11] pSwapChainVT = " << pSwapChainVT[8] << std::endl;

																		   //Hook using Detour
		D3D11::HookFunction(reinterpret_cast<PVOID*>(&D3D11::oPresent), D3D11::D3D11Present);
		std::cout << "[D3D11] oPresent = " << oPresent << std::endl;

	}

	HRESULT __stdcall D3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		//this is called every frame.
		if (doInit)
		{
			doInit = false;
			std::cout << "Calling D3D11 Present hook !" << std::endl;

			HWND hWindow = FindWindow("H1Z1 PlayClient (Live)", NULL);
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice)))
			{
				pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
				pDevice->GetImmediateContext(&pContext);
			}

			ID3D11Texture2D* renderTargetTexture = nullptr;
			if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
			{
				pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &pRenderTargetView);
				renderTargetTexture->Release();
			}

			ImGui_ImplDX11_Init(hWindow, pDevice, pContext);
			ImGui_ImplDX11_CreateDeviceObjects();
		}

		pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

		ImGui_ImplDX11_NewFrame();
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin("D3D11_Buffer", reinterpret_cast<bool*>(true), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar);

		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiSetCond_Always);

		Visuals::Run();

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::Render();
		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	//Detour
	void HookFunction(PVOID *oFunction, PVOID pDetour)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(oFunction, pDetour);
		DetourTransactionCommit();
	}
	void UnhookFunction(PVOID *oFunction, PVOID pDetour)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(oFunction, pDetour);
		DetourTransactionCommit();
	}
}
