#include"HMModRenderer.h"
#include"IWindow.h"
#include"EventManager.h"
#include"LogManager.h"

namespace HARMONY
{
	namespace CORE
	{
		RegisterModuleClass(HMModRenderer);
		HMModRenderer::HMModRenderer()
		:_renderapi(nullptr)
		,_swapchain(nullptr)
		{
		}

		HMModRenderer::~HMModRenderer() 
		{
		}

		bool HMModRenderer::AwakeInitialize()
		{
			_renderapi = ModuleManager::GetModule<IRenderingAPI>();
			if (!_renderapi)
			{
				return false;
			}
			EventManager::GetEvent<>(TSTR("OnRender")).Add(std::bind(&HMModRenderer::OnRender, this)); 
			return true;
		}

		bool HMModRenderer::Initialize()
		{
			//ウィンドウを取得
			IWindow* window= ModuleManager::GetModule<IWindow>();
			auto handle = window->GetWindowHandle(TSTR("Harmony"));
			if (!window)
			{
				return false;
			}
			uint32_t w = window->GetWindowWidth(TSTR("Harmony"));
			uint32_t h = window->GetWindowHeight(TSTR("Harmony"));

			//スワップチェインを作成
			_swapchain = reinterpret_cast<ISwapchain*>(_renderapi->CreateResource(ResourceType::SwapChain));
			if (!_swapchain->Initialize(handle, w, h))
			{
				return false;
			}
			return true;
		}

		void HMModRenderer::Terminate()
		{
			_swapchain->Terminate();
		}

		void HMModRenderer::OnRender()
		{
			_swapchain->SetRenderTarget(0.1, 0.1, 0.5);
			_swapchain->Present();
			_renderapi->WiteGPU();
		}
	}
}