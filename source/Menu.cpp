//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Menu.h"
#include "State.h"
#include "Game.h"
#include "Graphics.h"
#include "Level.h"
#include <nds.h>

Menu::Menu(){
	fade_clock = FADE;
	anim_clock = EYES_ANIM;
	eyes = new DrawableEntity();
	initMenu();

}

Menu::Menu(const Menu& c){

}

Menu::~Menu(){
	delete eyes;

}

Menu* Menu::Instance(){
	static Menu pinstance;
	return &pinstance;
}


void Menu::handleInput(){
	//Update the keypad state	
	scanKeys();

	//After updating the inputs we need to call the "keys functions"
	//(keysHeld, keysDown, keysUp...), they represent an event and if
	//that event is triggered by any button of the console, the function
	//will change the button value in the enumerator

	if (keysUp() & KEY_TOUCH){
		Game::Instance()->setState(State::StateType::LEVEL_STATE);
		Graphics::Instance()->loadLevel();
		Level::Instance()->initLevel(1);
	}

}


void Menu::update(){

	auto* g = Graphics::Instance();

	//update the "touch the screen" text
	if(fade_clock == 0){
		g->fadeTitleText();
		fade_clock = 3;
	}else{
		fade_clock--;
	}


	//animation of the character's eyes
	anim_clock--;
	if(anim_clock < 21){
		if(anim_clock == 20 || anim_clock == 10){
			g->animateEyes(eyes->getOAMid());
		}else if(anim_clock == 0){
			g->resetEyes(eyes->getOAMid());
			anim_clock = 90;
		}
	}

}

void Menu::initMenu(){
	eyes->setOAMid(Graphics::Instance()->createEyesSprite(105, 181));
}