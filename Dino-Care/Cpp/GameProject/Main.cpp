#include "Game.h"

using namespace Dino_Care;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Game game;
	game.Initialize(hInstance);
	game.Start();
	game.Loop();

}