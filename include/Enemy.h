//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#pragma once
#include "common_def.h"
#include "DrawableEntity.h"

#define ATTACK_TIMER 100
#define E_SPR_WIDTH 38
#define E_SPR_HEIGHT 38

class Enemy : public DrawableEntity{

	public:


		Enemy(int, int);
		Enemy(const Enemy&);
		virtual ~Enemy();

		//Logic update
		void update();
		bool checkCollision();
		void attack();

		//Init
		void reset();
		void init(int, int);

		//Setters
		void setActive(bool);
		void setPatternSpriteId(int);

		//Getters
		int getX();
		int getY();
		int getGfxIndex();
		int getType();
		int getPosIni();
		bool getActive();
		int getPatternSpriteId();

	private:

		float x,y; 			 //initial position position
		float inc_x, inc_y;  //movement
		bool active; 
		bool can_attack;
		int pos; // 0 -> top left corner
				 // 1 -> top right corner
				 // 2 -> bottom left corner
				 // 3 -> bottom right corner

		DrawableEntity pattern; //sprite for the pattern
		int type; //type of pattern 0 -> vertical
								//	1 -> horizontal
								//	2 -> triangle

		//timers
		int animation_clock; //for the sprite
		int timer_a;		 //attacking timer
};