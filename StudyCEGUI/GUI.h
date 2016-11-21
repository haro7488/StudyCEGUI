#pragma once

#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Direct3D9\Renderer.h>


struct D3DXVECTOR4;

using std::string;

namespace HaroEngine {
	class GUI
	{
	public:
		void Init(LPDIRECT3DDEVICE9 device, const string& resourceDirectory);
		void Destory();

		void Draw();

		void SetMouseCursor(const string& imageFile);
		void ShowMouseCursor();
		void HideMouseCursor();

		void LoadScheme(const string& schemeFile);
		void SetFont(const string& fontFile);
		CEGUI::Window* CreateWidget(const string& type, D3DXVECTOR4& destRectPerc, D3DXVECTOR4& destRectPix, const string& name = "");
		static void SetWidgetDestRect(CEGUI::Window* widget, D3DXVECTOR4& destRectPerc, D3DXVECTOR4& destRectPix);


		//Getters
		CEGUI::Direct3D9Renderer* GetRenderer() { return m_renderer; }
		CEGUI::GUIContext* GetContext() { return m_context; }

		GUI();
		~GUI();

	private:
		LPDIRECT3DDEVICE9 m_device;
		static CEGUI::Direct3D9Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_root = nullptr;
	};
}


