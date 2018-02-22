#ifdef HT_DIRECTX
#include "graphics/Texture2D.hpp"

namespace ht { namespace graphics {

	void Texture2D::SetSamplerState() {
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		HT_DXDEVICE->CreateSamplerState(&samplerDesc, &m_SamplerState);
	}


	Texture2D::Texture2D(u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		SetSamplerState();
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Width = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = static_cast<DXGI_FORMAT>(GetBaseFormat(format));
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureDesc.Usage = D3D11_USAGE_DYNAMIC;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;

		DX(HT_DXDEVICE->CreateTexture2D(&textureDesc, NULL, &m_Texture));

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = textureDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipLevels = 1;
		viewDesc.Texture2D.MostDetailedMip = 0;

		DX(HT_DXDEVICE->CreateShaderResourceView(m_Texture, &viewDesc, &m_ResourceView));
	}

	Texture2D::Texture2D(byte* pixels, u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		SetSamplerState();
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = static_cast<DXGI_FORMAT>(GetBaseFormat(format));
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = pixels;
		data.SysMemPitch = width * TextureFormatSize(format);


		DX(HT_DXDEVICE->CreateTexture2D(&textureDesc, &data, &m_Texture));

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = textureDesc.Format;
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipLevels = 1;
		viewDesc.Texture2D.MostDetailedMip = 0;

		DX(HT_DXDEVICE->CreateShaderResourceView(m_Texture, &viewDesc, &m_ResourceView));

	}

	Texture2D::~Texture2D() {
		m_Texture->Release();
		m_SamplerState->Release();
		m_ResourceView->Release();
	}

	void Texture2D::SetPixels(byte* pixels) {
		D3D11_MAPPED_SUBRESOURCE mappedTexture = {};
		DX(HT_DXCONTEXT->Map(m_Texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedTexture));
		memcpy(mappedTexture.pData, pixels, m_Width * m_Height * TextureFormatSize(m_Format));
		HT_DXCONTEXT->Unmap(m_Texture, 0);
	}

	void Texture2D::Bind(u32 slot) {
		HT_DXCONTEXT->PSSetShaderResources(slot, 1, &m_ResourceView);
		HT_DXCONTEXT->PSSetSamplers(slot, 1, &m_SamplerState);
	}


} }


#endif