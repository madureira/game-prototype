#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#else
#define DEBUG = 1
#endif

#include <SDL2/SDL.h>
#undef main
#include "src/game/game.h"

int main(int argc, char *argv[])
{
	using namespace game;

	Game game;

	return 0;
}
