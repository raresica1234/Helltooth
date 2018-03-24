#pragma once
#if defined(HT_DIRECTX)
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>
#elif defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#endif

#include <Windows.h>

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	class Context {
	private:
		HDC m_DeviceContext;
#ifdef HT_OPENGL
		HGLRC m_Context;
		HWND m_Hwnd;
#elif defined(HT_DIRECTX)
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTarget;
		ID3D11DepthStencilView* m_DepthStencilView;
		ID3D11Texture2D* m_DepthStencilBuffer;
#endif

	public:
		Context(HWND& hwnd);
		~Context();

#ifdef HT_DIRECTX
		inline ID3D11Device* GetDevice() { return m_Device; }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context; }
#endif

		void Update();
		void Clear();
	};

} }
