//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <nds.h>

#include "Game.h"
#include "Menu.h"
#include "Level.h"
#include "Win.h"
#include "Graphics.h"

Game::Game(){

}

Game::Game(const Game& c){

}

Game::~Game(){

}

Game* Game::Instance(){
	static Game pinstance;
	return &pinstance;
}

void Game::runGame(){

	while(1){
		//check user input
		gameState->handleInput();
		
		//update game
		gameState->update();

		//vblank
		swiWaitForVBlank();
		Graphics::Instance()->updateOAM();
	}
}

void Game::setState(State::StateType type){
	switch(type){

		case State::StateType::LEVEL_STATE:
			gameState = Level::Instance();
		break;

		case State::StateType::MENU_STATE:
			gameState = Menu::Instance();
		break;

		case State::StateType::WIN_STATE:
			gameState = Win::Instance();
		break;

		default:
		break;
	}

}