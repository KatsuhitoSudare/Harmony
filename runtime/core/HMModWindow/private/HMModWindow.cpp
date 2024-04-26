#include"HMModWindow.h"
#include"EventManager.h"

namespace HARMONY
{
	namespace CORE
	{ 
		RegisterModuleClass(HMModWindow)

		HMModWindow::HMModWindow()
			:_nativeWindow(nullptr)
		{
			
		}

		HMModWindow::~HMModWindow()
		{
			
		}

		bool HMModWindow::AwakeInitialize()
		{ 
			_nativeWindow = ModuleManager::GetModule<IWindow>();
			if (!_nativeWindow)
			{
				return false;
			}
			_nativeWindow->MakeWindow(L"Harmony",1280,720);
			_mainWindowHandle = _nativeWindow->GetWindowHandle(L"Harmony");
			EventManager::GetEvent<>(TSTR("OnWindowUpdate")).Add(std::bind(&HMModWindow::OnWindowUpdate,this));
			return true;
		}

		void HMModWindow::OnWindowUpdate()
		{
			_nativeWindow->ProcessMessage();
		}
	}
}