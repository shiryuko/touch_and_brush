//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <nds.h>

#include "Win.h"
#include "Level.h"
#include "Graphics.h"
#include "Game.h"

Win::Win(){
	next_level = -1;

}

Win::Win(const Win& c){

}

Win::~Win(){


}

Win* Win::Instance(){
	static Win pinstance;
	return &pinstance;
}


void Win::handleInput(){
	//Update the keypad state	
	scanKeys();

	//After updating the inputs we need to call the "keys functions"
	//(keysHeld, keysDown, keysUp...), they represent an event and if
	//that event is triggered by any button of the console, the function
	//will change the button value in the enumerator

	if (keysUp() & KEY_TOUCH){
		Game::Instance()->setState(State::StateType::LEVEL_STATE);
		Graphics::Instance()->loadLevel();
		Level::Instance()->initLevel(next_level);
	}

}


void Win::update(){

}

void Win::setNextLevel(int level){
	next_level = level;
}