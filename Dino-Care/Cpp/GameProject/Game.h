#pragma once
#include <Engine.h>
using ALL_FM3D_NAMESPACES;
#include "Resources.h"
#include "CustomResources.h"

namespace Dino_Care {

	class Game {
	private:
		Window* m_win;

		RenderSystem* m_renderSystem;
		Renderer3D* m_renderer3D;
		Renderer2D* m_renderer2D;
		RenderTarget2D* m_target2D;
		RenderTarget2D* m_target3D;

		EntityCollection m_scene;
		Camera m_camera;
		EntityLogic* m_renderLogic;
		Resources m_res;
		CustomResources m_cres;
	public:
		~Game();

		bool Initialize(HINSTANCE hInstance);
		void Start();
		void Loop();
		void Update(double time, double timeDelta);
	};
}