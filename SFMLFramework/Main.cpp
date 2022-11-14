// If in debug mode, include Visual Leak Detector
#ifdef _DEBUG
	#include "vld.h"
#endif // _DEBUG

#include "Game.h"

int main()
{
	Game game;
	game.run();

	return 0;
}

