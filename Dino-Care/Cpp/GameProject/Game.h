#pragma once
#include <Engine.h>
using ALL_FM3D_NAMESPACES;

namespace Dino_Care {

	class Game {
	private:
		Window* m_win;

	public:
		void Initialize(HINSTANCE hInstance);
		void Start();
		void Loop();
		void Update(double time, double timeDelta);
	};
}