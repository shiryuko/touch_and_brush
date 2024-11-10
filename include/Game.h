//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "State.h"

class Game{

	public:
		static Game* Instance();
		void runGame();
		void setState(State::StateType);
		//void initConsole();

	protected:
		Game();
		Game(const Game&);
		virtual ~Game();

	private:
		State* gameState;

};