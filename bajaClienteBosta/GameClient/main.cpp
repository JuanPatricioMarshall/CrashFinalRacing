/*
 * main.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: gonzalo
 */

#include "Game.h"
#include "Utils/Random.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
    int frameStartTime, frameEndTime;

	std::cout << "Abriendo juego...\n";

	Random::initialize();

	if (Game::Instance()->init("1942 Ultraa Diesel", 400, 150, 800, 600, SDL_WINDOWPOS_CENTERED)) //flag por ejemplo: SDL_WINDOW_FULLSCREEN_DESKTOP

	{
		std::cout << "game init success!\n";

		Game::Instance()->conectToKorea();
		std::cout << "Game Online!\n";

		//Bucle del juego
		while (Game::Instance()->isRunning()) {

			frameStartTime = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->render();

			frameEndTime = SDL_GetTicks() - frameStartTime;

			//tiempo a esperar = tiempo que demoro en finalizar el  frame = tiempo en que finalizó - tiempo en que inició
			if (frameEndTime < DELAY_TIME) {
				SDL_Delay((int) ((DELAY_TIME - frameEndTime)));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    Game::Instance()->clean();

    return 0;
}
