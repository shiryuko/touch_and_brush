//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#ifndef PLAYER_H
#define PLAYER_H

#include <nds.h>
#include "DrawableEntity.h"


#define SPR_WIDTH 64
#define SPR_HEIGHT 64
#define MAX_LIFES 6

class Player : public DrawableEntity{

	public:

		//Singleton
		static Player* Instance();

		//Update
		void update();

		//Others
		void hurt();
		void resetPlayer();

		//Getters
		int getX();
		int getY();
		int getLifes();

		//Setters
		void setState(int);
		void setHeartSpriteId(int, int);
 
	protected:

		Player();
		Player(const Player&);
		virtual ~Player();

	private:

		//Player attributes
		int lifes;
		int x, y;

		//Sprite attributes
		DrawableEntity* lifeSprites[MAX_LIFES];
		u16 animation_clock;

		int state; 	//0-> idle
					//1-> attack
					//2-> hurt
};

#endif