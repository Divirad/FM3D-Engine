#include "Game.h"

using namespace Dino_Care;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Game game;
	if (!game.Initialize(hInstance)) return 0;
	game.Start();
	game.Loop();

}