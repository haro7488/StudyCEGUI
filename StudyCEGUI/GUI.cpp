#include "GUI.h"
#include <d3dx9.h>

namespace HaroEngine
{
	CEGUI::Direct3D9Renderer* GUI::m_renderer = nullptr;

	void GUI::Init(LPDIRECT3DDEVICE9 device, const std::string& resourceDirectory)
	{
		m_device = device;
		if (m_renderer == nullptr)
		{
			m_renderer = &CEGUI::Direct3D9Renderer::bootstrapSystem(device);

			CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
			rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
			rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
			rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
			rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
			rp->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
			rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
		}

		m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
		m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
		m_context->setRootWindow(m_root);
	}

	void GUI::Destory()
	{
		CEGUI::System::getSingleton().destroyGUIContext(*m_context);
	}

	void GUI::Draw()
	{
		m_renderer->beginRendering();
		m_context->draw();
		m_renderer->endRendering();
		//m_device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SCISSORTESTENABLE, false);
	}

	void GUI::SetMouseCursor(const string & imageFile)
	{
		m_context->getMouseCursor().setDefaultImage(imageFile);
	}

	void GUI::ShowMouseCursor()
	{
		m_context->getMouseCursor().show();
	}

	void GUI::HideMouseCursor()
	{
		m_context->getMouseCursor().hide();
	}

	void GUI::LoadScheme(const std::string & schemeFile)
	{
		CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
	}

	void GUI::SetFont(const std::string & fontFile)
	{
		CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
		m_context->setDefaultFont(fontFile);
	}

	CEGUI::Window * GUI::CreateWidget(const string & type, D3DXVECTOR4& destRectPerc, D3DXVECTOR4& destRectPix, const string & name)
	{
		CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
		m_root->addChild(newWindow);
		SetWidgetDestRect(newWindow, destRectPerc, destRectPix);
		return newWindow;
	}

	void GUI::SetWidgetDestRect(CEGUI::Window * widget, D3DXVECTOR4 & destRectPerc, D3DXVECTOR4 & destRectPix)
	{
		widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
		widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
	}

	GUI::GUI()
	{
	}


	GUI::~GUI()
	{
	}
}
