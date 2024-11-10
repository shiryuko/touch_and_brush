//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <cfloat>
#include <cstdio>
#include "PatternManager.h"

PatternManager::PatternManager(){
	x_cm = 0;
	y_cm = 0;
	x_cm_s = 0;
	y_cm_s = 0;
	
}

PatternManager::PatternManager(const PatternManager&){

}

PatternManager::~PatternManager(){
	clearPattern();

}

int PatternManager::checkPattern(){

	int type = -1;

	//First calculate center of mass of the stroke
	calculateCenterOfMass();

	//and check all the different patterns
	x_cm_s = cm_shapes[0].getX();
	y_cm_s = cm_shapes[0].getY();
	float o_tot_v = checkPattern(v_line);

	x_cm_s = cm_shapes[1].getX();
	y_cm_s = cm_shapes[1].getY();
	float o_tot_h = checkPattern(h_line);

	x_cm_s = cm_shapes[2].getX();
	y_cm_s = cm_shapes[2].getY();
	float o_tot_t = checkPattern(triangle);


	if(o_tot_v < o_tot_h && o_tot_v < o_tot_t){
		type = 0;
	}else if(o_tot_h < o_tot_v && o_tot_h < o_tot_t){
		type = 1;
	}else{
		type = 2;
	}

	clearPattern();

	return type;
}

float PatternManager::checkPattern(const Vector2D shape[]){

	//calcule displacement in both axis
	//of the user pattern from the ideal pattern
	int dx,dy;

	//Vector2D s = shape[0];
	Vector2D* u = user_pattern[0];

	//dx = s.getX() - u->getX();
	//dy = s.getY() - u->getY();

	dx = x_cm_s - x_cm;
	dy = y_cm_s - y_cm;


	//user pattern iterator
	float inc = (user_pattern.size()-1)/(ANCHOR_POINTS-1);
	float j = 0.0;


	//total deviation 
	float o_tot = 0.0;

	for(int i=0;i<ANCHOR_POINTS;i++){

		u = user_pattern[j];

		//displace point
		int x_ = u->getX() + dx;
		int y_ = u->getY() + dy;

		//Vector2D s = shape[i];
		Vector2D s = shape[findNearest(x_,y_,shape)];


		//Calculate RMS and deviation for x and y
		float rms_x, rms_y, aux;
		aux = 0.0;

		//x coordinate
		aux = pow(s.getX(),2) + pow(x_,2); // x1² + x2²
		aux = aux/2.0;						// ---------
									     	//     2
		rms_x = sqrt(aux);

		o_tot = o_tot + abs(s.getX() - rms_x);


		//y coordinate
		aux = pow(s.getY(),2) + pow(y_,2); // y1² + y2²
		aux = aux/2.0;						// ---------
									     	//     2
		rms_y = sqrt(aux);

		o_tot = o_tot + abs(s.getY() - rms_y);


		if(i == ANCHOR_POINTS-1){
			j = user_pattern.size()-1;
		}else{
			j = j + inc;
		}

	}

	return o_tot;
}

void PatternManager::insertPoint(int x, int y){

	//insert the coordinate only if it's not the same as 
	//the last one

	if(user_pattern.size()>1){

		auto* v = user_pattern[user_pattern.size()-1];

		if(v->getX() != x || v->getY() != y){
			Vector2D* pos = new Vector2D(x, y);
			user_pattern.push_back(pos);
			pos = nullptr;
		}

		v = nullptr;

	}else{
		Vector2D* pos = new Vector2D(x, y);
		user_pattern.push_back(pos);
		pos = nullptr;
	}

}

void PatternManager::clearPattern(){

	for(unsigned int i=0;i < user_pattern.size();i++){
		if(user_pattern[i]){

			delete user_pattern[i];
			user_pattern[i] = nullptr;
		}

	}
	user_pattern.clear();
	user_pattern.resize(0);

}

void PatternManager::calculateCenterOfMass(){

	int sum_x = 0;
	int sum_y = 0;

	x_cm = 0;
	y_cm = 0;

	//iterator throught the selected points
	float inc = (user_pattern.size()-1)/(ANCHOR_POINTS-1);
	float j = 0.0;

	for(int i=0;i<ANCHOR_POINTS;i++){
		if(user_pattern[i]){

			Vector2D* pos = user_pattern[j];

			sum_x = pos->getX() + sum_x;
			sum_y = pos->getY() + sum_y;

		}

		if(i == ANCHOR_POINTS-1){
			j = user_pattern.size()-1;
		}else{
			j = j + inc;
		}
	}

	x_cm = sum_x/ANCHOR_POINTS;
	y_cm = sum_y/ANCHOR_POINTS;

}

int PatternManager::findNearest(int x, int y, const Vector2D shape[]){

	float dist = FLT_MAX;
	int nearest = -1;

	for(int i = 0; i<ANCHOR_POINTS; i++){

		Vector2D pos = shape[i];

		float dist_act = sqrt(pow((pos.getX()-x),2)+pow(pos.getY()-y,2));

		if(dist_act < dist){
			nearest = i;
			dist = dist_act;
		}
	}

	return nearest;

}