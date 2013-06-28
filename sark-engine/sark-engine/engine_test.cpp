#include <Windows.h>
#include "SarkEngine.h"

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int){
	sark::CreateEngine(hInstance, wstring(L"sark-engine"));

	while( sark::gpEngine->run() ){
		// scene manager -> update
		// scene manager -> render


		// test code
		IDirect3DDevice9* pDev = sark::gpEngine->getDevice();
		pDev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);

		pDev->Present(0,0,0,0);
	}
	return 0;
}