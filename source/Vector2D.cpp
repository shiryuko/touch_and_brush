//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Vector2D.h"

Vector2D::Vector2D(int x_, int y_){
	x = x_;
	y = y_;
}

Vector2D::~Vector2D(){

}

int Vector2D::getX() const{
	return x;
}

int Vector2D::getY() const{
	return y;
}

void Vector2D::setX(int x_){
	x=x_;
}

void Vector2D::setY(int y_){
	y=y_;
}