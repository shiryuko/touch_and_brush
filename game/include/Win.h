//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "State.h"

class Win : public State{

	public:

		//Singleton
		static Win* Instance();

		void handleInput();
		void update();

		void setNextLevel(int);

	protected:

		Win();
		Win(const Win&);
		virtual ~Win();

	private:

		int next_level;

};