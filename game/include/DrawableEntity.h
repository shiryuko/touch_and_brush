//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

//This class is to keep track of the objects of the game that can be drawn on screen using sprites
//(i.e. enemies, player, HUD...)

#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

class DrawableEntity{

	public:

        DrawableEntity();
        virtual ~DrawableEntity();
		int getOAMid();
		void setOAMid(int);

	private:

		//identifier on the OAM
		int OAMid;

};

#endif // DRAWABLEENTITY_H