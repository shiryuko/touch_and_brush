//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "State.h"
#include "DrawableEntity.h"

#define FADE 3
#define EYES_ANIM 90

class Menu : public State{

	public:

		//SIngleton
		static Menu* Instance();

		void handleInput();
		void update();

		void initMenu();

	protected:

		Menu();
		Menu(const Menu&);
		virtual ~Menu();

	private:

		//Touch the screen text face clock
		int fade_clock;

		//Attributes for the Eyes sprite of the characters
		int anim_clock;
		DrawableEntity* eyes;

};