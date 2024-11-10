//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#ifndef VECTOR2D
#define VECTOR2D

class Vector2D{

	public:
		Vector2D(int, int);
		virtual ~Vector2D();
		int getX() const;
		int getY() const;
		void setX(int);
		void setY(int);

	private:
		int x,y;

};

#endif