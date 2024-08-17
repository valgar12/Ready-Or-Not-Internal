#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

bool FirstInject = true;
bool debug = false;
FILE* Dummy{};

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	SetColorsFlags();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 18.0f);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);

	draw_list = ImGui::GetBackgroundDrawList();
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_INSERT:
			showmenu = !showmenu;
			break;
		}
	}

	if (showmenu && !FirstInject) return true;
	if (!showmenu && FirstInject) FirstInject = false;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (showmenu)
		DrawMenu();

	GameLoop();

	if (gl::Misc::ShowMouse && showmenu)
	{
		auto MousePos = ImGui::GetMousePos();
		ImGui::GetForegroundDrawList()->AddCircleFilled(MousePos, 4.f, ImColor{ 1.f, 1.f, 1.f });
	}
	if (gl::Misc::DrawCrosshair)
		ESP::DrawCrosshair(gl::Misc::CrosshairSize, gl::Misc::CrosshairThickness, gl::esp_Colors::CrosshairColor);

	if (!alive)
	{
		kiero::shutdown();
		pDevice->Release();
		pContext->Release();
		pSwapChain->Release();
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));
	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD MainThread(HMODULE hModule)
{
	if (debug)
	{
		AllocConsole();
		freopen_s(&Dummy, "CONOUT$", "w", stdout);
	}

	std::thread(PlayerCache::PlayerCache).detach();
	std::thread(ActorsCache::ActorsCache).detach();

	bool init_hook = false;
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&oPresent, hkPresent);
		init_hook = true;
	}

	while (alive)
	{
		if (GetAsyncKeyState(VK_END))
		{
			alive = false;
			Sleep(100);
			if (debug)
			{
				FreeConsole();
				if (Dummy)
					fclose(Dummy);
			}
			FreeLibraryAndExitThread(hModule, 0);
		}
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}