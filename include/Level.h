//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <nds.h>

#include "common_def.h"
#include "State.h"
#include "Enemy.h"
#include "PatternManager.h"

#define SPAWN_ENEMY 200

//LEVEL DATA
#define TOTAL_LEVELS 4
#define E(a,b) new Enemy((a),(b))
static Enemy* level_1[ENEMY_MAX_COUNT] {E(0,0),E(0,1),E(1,0),E(1,1),E(0,1),E(1,0)};
static Enemy* level_2[ENEMY_MAX_COUNT] {E(0,0),E(1,1),E(2,0),E(0,1),E(2,0),E(1,1)};
static Enemy* level_3[ENEMY_MAX_COUNT] {E(0,1),E(2,1),E(3,2),E(1,0),E(0,0),E(2,2)};
static Enemy* level_4[ENEMY_MAX_COUNT] {E(1,1),E(0,2),E(2,0),E(0,2),E(1,1),E(3,2)};

class Level : public State{

	public:

		static Level* Instance();

		void handleInput();
		void update();

		void initLevel(int);
		void activeEnemy();
		void killEnemies(int);
		void toMenu();
		void toWin();

		//DEPRECATED
		//void loadLevelTwo();
		//void checkPattern(int, int); 

	protected:

		Level();
		Level(const Level&);
		virtual ~Level();

	private:

		void initLevel(Enemy*[],int,int);

		//Level data
		int act_level;
		int enemies_to_kill;
		int cont;

		//Enemies data and spawn
		Enemy* enemies[ENEMY_MAX_COUNT];
		int spawn_time;
		int timer;
		int last_activated;

		//Touch data and pattern recognition
		PatternManager* pm;
		int x_in, y_in;

		//DEPRECATED
		//bool already_touched;
};