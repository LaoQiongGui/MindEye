#pragma once
#include "Common.h"

namespace NewFunctions
{
	// EndScene函数
	typedef HRESULT(STDMETHODCALLTYPE *D3DENDSCENE)(LPDIRECT3DDEVICE9 p_pDevice);
	extern D3DENDSCENE fpD3dEndScene;
	HRESULT STDMETHODCALLTYPE D3dEndScene(LPDIRECT3DDEVICE9 p_pDevice);

	// DrawIndexedPrimitive函数
	typedef HRESULT(STDMETHODCALLTYPE *D3DDRAWINDEXEDPRIMITIVE)(
		LPDIRECT3DDEVICE9 p_pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex,
		UINT NumVertices, UINT startIndex, UINT primCount);
	extern D3DDRAWINDEXEDPRIMITIVE fpD3dDrawIndexedPrimitive;
	HRESULT STDMETHODCALLTYPE D3dDrawIndexedPrimitive(
		LPDIRECT3DDEVICE9 p_pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex,
		UINT NumVertices, UINT startIndex, UINT primCount);
}
