#include <HAPI_lib.h>
#include "World.h"

using namespace HAPISPACE;

//sets timeout
int timeDelayMS = 10;
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;


void HAPI_Main()
{
	World Game;
	Game.Initialise(752, 800);
	Game.LoadLevel();
	while (HAPI.Update())
	{
		Game.Update();
	};
}


