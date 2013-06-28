#ifndef _SARK_ENGINE_H
#define _SARK_ENGINE_H

#include <d3d9.h>
#include <string>
using std::wstring;

namespace sark{

#define SARKENGINE_CLASSNAME L"SarkEngine-Host"
#define DEFAULT_WNDSZ_W 600
#define DEFAULT_WNDSZ_H 480

	class SarkEngine{
	public:
		SarkEngine(HINSTANCE hInstance, const wstring& strCaption);
		~SarkEngine();

	private:
		bool initApp(const wstring& strCaption);
		bool initDevice();

	public:
		LRESULT msgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

		IDirect3DDevice9* const getDevice();
		bool run();
	
		
	private:
		IDirect3D9* mpd3d9;
		IDirect3DDevice9* mpDevice;
		HINSTANCE mhInst;
		HWND mhWnd;

	};

	extern SarkEngine* gpEngine;
	extern void CreateEngine(HINSTANCE hInstance, const wstring& strCaption);
}
#endif