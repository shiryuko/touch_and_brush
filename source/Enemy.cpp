//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Enemy.h"
#include "Player.h"
#include "Level.h"
#include "Graphics.h"

Enemy::Enemy(int pos, int pattern_){
	init(pos, pattern_);
	pattern.setOAMid(-1);

}

Enemy::Enemy(const Enemy& c){

}

Enemy::~Enemy(){


}

void Enemy::update(){

	if(!checkCollision()){

		x = x + inc_x;
		y = y + inc_y;

		//update run animation
		if(animation_clock == 0){
			animation_clock = 8;
			Graphics::Instance()->animateEnemyRun(getOAMid());
		}else{
			animation_clock--;
		}

	}else{
		attack();
		//reset the amimation if needed
		Graphics::Instance()->resetEnemySprite(getOAMid());
	}

}

void Enemy::attack(){

	auto* p = Player::Instance();

	//Update the attack timer
	if(can_attack == false){
		if(timer_a == 0){
			can_attack = true;
			timer_a = ATTACK_TIMER;
		}else{
			timer_a--;
		}
	}

	//Attacks the player
	if(can_attack == true){
		
		p->hurt();
		can_attack = false;
	}

}

bool Enemy::checkCollision(){

	auto* p = Player::Instance();
	bool collision = false;

	if(x + E_SPR_WIDTH >= p->getX() && x <= p->getX() + E_SPR_WIDTH && y + E_SPR_HEIGHT >= p->getY() && y <= p->getY() + E_SPR_HEIGHT){

		collision = true;
	}

	return collision;

}

bool Enemy::getActive(){
	return active;
}

void Enemy::setActive(bool a){
	active = a;
}

void Enemy::init(int pos_, int pattern_){

	animation_clock = 8;
	active = false;
	can_attack = true;
	timer_a = ATTACK_TIMER;

	pos = pos_;
	//pos = rand() % 6 + 0; //pos inic del enemigo

	switch(pos){
		case 0:		//top left
			x = -60;
			y = 25;

			inc_x = 0.5; //1.0
			inc_y = 0.0;
			
			break;

		case 1:		//top right
			x = SCREEN_WIDTH;
			y = 25;

			inc_x = -0.5; //-1.0
			inc_y = 0.0;

			break;

		case 2:		//bottom left
			x = -60;
			y = 180;

			inc_x = 1.0;
			inc_y = -1.0;
			
			break;
 
		case 3:		//bottom right
			x = 247;
			y = 180;

			inc_x = -1.0;
			inc_y = -1.0;

			break;

		default:
			x = -60;
			y = 25;

			inc_x = 0.5;
			inc_y = 0.0;
			
			break;
	}

	type = pattern_;

	if(pattern_ < 0 || pattern_ > 3){
		type = 0;
	}


}

void Enemy::reset(){

	active = false;
	can_attack = true;
	timer_a = ATTACK_TIMER;

	switch(pos){
		case 0:		//top left
			x = -60;
			y = 25;

			break;

		case 1:		//top right
			x = SCREEN_WIDTH;
			y = 25;


			break;

		case 2:		//bottom left
			x = -60;
			y = 180;
			
			break;
 
		case 3:		//bottom right
			x = 247;
			y = 180;

			break;

		default:
			x = -60;
			y = 25;
			
			break;
	}


}

//Getters

int Enemy::getX(){
	return (int)x;
}

int Enemy::getY(){
	return (int)y;
}

int Enemy::getType(){
	return type;
}

int Enemy::getPosIni(){
	return pos;
}

int Enemy::getPatternSpriteId(){
	return pattern.getOAMid();
}

void Enemy::setPatternSpriteId(int id){
	pattern.setOAMid(id);
}