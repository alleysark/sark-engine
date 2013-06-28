#include "SarkEngine.h"

namespace sark{

	SarkEngine* gpEngine;


	LRESULT CALLBACK SarkEngineMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
		if( gpEngine!=NULL )
			return gpEngine->msgProc(hwnd, msg, wParam, lParam);
		else
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}


	void CreateEngine(HINSTANCE hInstance, const wstring& strCaption){
		if( gpEngine!=NULL )
			return;

		gpEngine = new SarkEngine(hInstance, strCaption);
	}


	SarkEngine::SarkEngine(HINSTANCE hInstance, const wstring& strCaption)
		: mpd3d9(NULL), mpDevice(NULL), mhInst(hInstance), mhWnd(NULL)
	{
		if( !initApp(strCaption) )
			PostQuitMessage(0);

		if( !initDevice() )
			PostQuitMessage(0);
	}


	SarkEngine::~SarkEngine(){
		if( mpDevice!=NULL )
			mpDevice->Release();
		if( mpd3d9!=NULL )
			mpd3d9->Release();

		UnregisterClass(SARKENGINE_CLASSNAME, mhInst);
	}


	bool SarkEngine::initApp(const wstring& strCaption){
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_CLASSDC;
		wc.lpfnWndProc = SarkEngineMsgProc;
		wc.hInstance = mhInst;
		wc.lpszClassName = SARKENGINE_CLASSNAME;
		RegisterClassEx(&wc);

		RECT wndrt = {0, 0, DEFAULT_WNDSZ_W, DEFAULT_WNDSZ_H};
		AdjustWindowRect(&wndrt, WS_OVERLAPPEDWINDOW, false);
		mhWnd = CreateWindow(SARKENGINE_CLASSNAME, strCaption.c_str(), WS_OVERLAPPEDWINDOW,
			100, 100, wndrt.right-wndrt.left, wndrt.bottom-wndrt.top, 0, 0, mhInst, NULL);

		if( mhWnd==NULL ){
			return false;
		}

		ShowWindow(mhWnd, SW_SHOWDEFAULT);
		UpdateWindow(mhWnd);

		return true;
	}


	bool SarkEngine::initDevice(){
		if( NULL == (mpd3d9 = Direct3DCreate9(D3D_SDK_VERSION)) ){
			return false;
		}

		// TODO : setup device from CreationParameter
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;



		if( FAILED( mpd3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
			mhWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mpDevice) ) ){
				return false;
		}

		return true;
	}


	LRESULT SarkEngine::msgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
		switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, msg, wp, lp);
	}


	IDirect3DDevice9* const SarkEngine::getDevice(){
		return mpDevice;
	}


	bool SarkEngine::run(){
		static MSG  msg;

		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ){
			if (msg.message == WM_QUIT)
				return false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			// engine pause check

			// device lost check
		}

		return true;
	}

}