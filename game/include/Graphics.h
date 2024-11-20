//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <nds.h>

#define SCREEN_START ((u16*)0x06200000)	 //Pointer to sub bg memory where the canvas bg is located
const unsigned int color = RGB15(0,0,0); //Transparent pixel color (black) for the canvas bg

//Types of sprites in the game
enum SpriteType{
	S_PLAYER,
	S_ENEMY,
	S_HEART,
	S_PATTERN_H,
	S_PATTERN_V,
	S_EYES
};


class Graphics{

	public:

		//Singleton
		static Graphics* Instance();

		//Inits
		void loadMenu();
		void loadLevel();
		void loadWin();
		void initConsole();

		//Common sprites
		void updateSpritePosition(int, int, int);
		void setVisible(int, bool);

		//CreateSprites
		int createSprite(int, int, SpriteType);
		int createEnemySprite(int, int, int);
		int createLifeSprites(int, int);
		int createPlayer(int, int);
		int createDialog(int, int, int);
		int createEyesSprite(int, int);

		//Animations
		void animatePlayer(int);
		void animateEnemyRun(int);
		void resetEnemySprite(int);
		void animateEyes(int);
		void resetEyes(int);
		void setPlayerHurtSpr(int);
		void setPlayerAttackSpr(int);

		//Others
		void drawCircleSub(int, int);
		void drawLineSub(int, int, int, int);
		void clearCanvasBg();
		void fadeTitleText();

		//OAM
		void updateOAM();
		void initOAM();

		//BACKGROUNDS
		void initBackgrounds();

		//VRAM
		void setBanks();

		//DEPRECATED
		//void updateDialog(int, int, int);

	protected:

		Graphics();
		Graphics(const Graphics&);
		virtual ~Graphics();

	private:

		OAMTable* oam; //Our OAM copy

		//sprite object index count
		static int next_avail_id;
		int avail_id;
		void updateAvailId();

		//sprite memory allocation
		static int next_avail_GFX;
		int get_GFX_mem_pos(int);

		//rgb components for rainbow fade
		int r,g,b;

};