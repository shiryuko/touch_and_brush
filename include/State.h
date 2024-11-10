//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#ifndef STATE_H
#define STATE_H

class State{

	public:

		enum StateType{
			MENU_STATE,
			LEVEL_STATE,
			WIN_STATE
		};

		virtual void handleInput()=0;
		virtual void update()=0;

	protected:

	private:

};

#endif // STATE_H

