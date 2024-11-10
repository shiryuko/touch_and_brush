//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(){
	//ctor
}

DrawableEntity::~DrawableEntity(){
	//dtor
}

void DrawableEntity::setOAMid(int id){
	OAMid = id;

}

int DrawableEntity::getOAMid(){
	return OAMid;
}