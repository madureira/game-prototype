#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SDL2/SDL.h>
#undef main
#include "src/game/game.h"

int main()
{
	using namespace game;

	Game game;

	return 0;
}