//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Game.h"
#include "Graphics.h"

int main(void){

	auto* game = Game::Instance();
	auto* graphics = Graphics::Instance();

	graphics->initConsole();

	game->setState(State::StateType::MENU_STATE);

	game->runGame();
	
}