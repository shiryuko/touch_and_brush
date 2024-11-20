//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Player.h"
#include "Graphics.h"
#include "Level.h"

Player* Player::Instance(){
	static Player pinstance;
	return &pinstance;
}

Player::Player(){
	resetPlayer();
}


Player::Player(const Player&){

}

Player::~Player(){

}

void Player::hurt(){

	state = 2;

	if(lifes > 1){
		lifes--;

		Graphics::Instance()->setVisible(lifeSprites[lifes]->getOAMid(),true);

	}else{
		//reset
		Level::Instance()->toMenu();
	}
}

void Player::update(){

	auto* g = Graphics::Instance();

	if(animation_clock == 0){
		animation_clock = 8;

		switch(state){
			case 0:
				g->animatePlayer(getOAMid());
			break;

			case 1:
				state = 0; //return to idle
				g->setPlayerAttackSpr(getOAMid());
			break;

			case 2:
				state = 0; //return to idle
				g->setPlayerHurtSpr(getOAMid());
			break;

			default:
				g->animatePlayer(getOAMid());
			break;
		}

	}else{
		animation_clock--;
	}
}

int Player::getLifes(){
	return lifes;
}

void Player::resetPlayer(){

	//auto* g = Graphics::Instance();

	lifes = MAX_LIFES;

	//create life sprites
	for(int i=0;i<MAX_LIFES;i++){

		lifeSprites[i] = new DrawableEntity();
		//lifeSprites[i]->setOAMid(g->createEnemySprite());
	}
	
	//player sprite is centered on the screen
	x = SCREEN_WIDTH/2 - SPR_WIDTH/2;
	y = 10; //SCREEN_HEIGHT/2 - SPR_WIDTH/2;

	//animation
	animation_clock = 8;
	state = 0;
}

int Player::getX(){
	return x;
}

int Player::getY(){
	return y;
}

void Player::setHeartSpriteId(int i, int index){
	lifeSprites[i]->setOAMid(index);
}

void Player::setState(int state_){
	state = state_;
}