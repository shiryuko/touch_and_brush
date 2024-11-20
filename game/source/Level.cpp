//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include <time.h>
#include "Level.h"
#include "Menu.h"
#include "Win.h"
#include "State.h"
#include "Game.h"
#include "Graphics.h"
#include "Player.h"

Level::Level(){

	spawn_time = SPAWN_ENEMY;
	timer = spawn_time;
	x_in = -1;
	y_in = -1;
	pm = new PatternManager();
	enemies_to_kill = 5;
	last_activated = 0;
	act_level = 1;
	cont = 0;

}

Level::Level(const Level& c){

}

Level::~Level(){
	delete pm;

}

Level* Level::Instance(){
	static Level pinstance;
	return &pinstance;
}


void Level::handleInput(){

	auto* g = Graphics::Instance();
	touchPosition stylus;

	//Update the keypad state	
	scanKeys();
	touchRead(&stylus);

	//After updating the inputs we need to call the "keys functions"
	//(keysHeld, keysDown, keysUp...), they represent an event and if
	//that event is triggered by any button of the console, the function
	//will change the button value in the enumerator

	//go back to main menu
	if (keysHeld() & KEY_A){
		toMenu();
	}

	//pattern recognition
	if(keysHeld() & KEY_TOUCH){

		//first check if the input is inside the range
		if(stylus.px > 25 && stylus.py > 25 && stylus.px < 226 && stylus.py < 167){

			//bresenham
			if(x_in == -1 && y_in == -1){

				g->drawCircleSub(stylus.px, stylus.py);

			}else{

				if(x_in != stylus.px || y_in != stylus.py){
					g->drawLineSub(x_in, y_in, stylus.px, stylus.py);
				}
			}

			x_in = stylus.px;
			y_in = stylus.py;
			pm->insertPoint(x_in, y_in);

		}else{
			g->clearCanvasBg();
			x_in = -1;
			y_in = -1;
			pm->clearPattern();
		}

	}

	if(keysUp() & KEY_TOUCH){
		if(x_in != -1 && y_in != -1){

			int pattern_to_kill = pm->checkPattern();
			if(pattern_to_kill != -1)
				killEnemies(pattern_to_kill);

			Player::Instance()->setState(1); //attack sprite
		}

		x_in = -1;
		y_in = -1;
		if(act_level <= TOTAL_LEVELS && enemies_to_kill > 0)
			g->clearCanvasBg();

	}

}



void Level::update(){

	auto* g = Graphics::Instance();

	//update timer to spawn enemies
	timer--;
	if(timer <= 0){
		timer = spawn_time;
		activeEnemy();
	}

	Player::Instance()->update();

	//update enemies
	for(int i=0; i<ENEMY_MAX_COUNT;i++){
		Enemy* enemy = enemies[i];

		if(enemy && enemy->getActive()){

			enemy->update();
			//update oam
			g->updateSpritePosition(enemy->getOAMid(),enemy->getX(),enemy->getY());
			g->updateSpritePosition(enemy->getPatternSpriteId(),enemy->getX()+23,enemy->getY()-3);
		}
	}

}

void Level::activeEnemy(){

	if(act_level == 4 && cont == 11){
		enemies[2]->setActive(true);
		enemies[3]->setActive(true);
		enemies[4]->setActive(true);
		enemies[5]->setActive(true);

	}else{

		if(last_activated >= 0 && last_activated < ENEMY_MAX_COUNT){
			if(enemies[last_activated]){
				enemies[last_activated]->setActive(true);
			}

			if(act_level == 4){
				cont++;
			}
		}

		last_activated++;
		if(last_activated >= ENEMY_MAX_COUNT)
			last_activated = 0;
	}
}


void Level::killEnemies(int type){

	for(int i=0;i<ENEMY_MAX_COUNT;i++){

		Enemy* enemy = enemies[i];

		if(enemy && enemy->getActive()==true){

			int enemy_type = enemy->getType();
			
			if(enemy_type == type){
				enemy->reset();
				Graphics::Instance()->updateSpritePosition(enemy->getOAMid(),enemy->getX(),enemy->getY());
				Graphics::Instance()->updateSpritePosition(enemy->getPatternSpriteId(),enemy->getX()+23,enemy->getY()-3);
				enemies_to_kill--;

				if(enemies_to_kill <= 0){
					//to next level
					//loadLevelTwo();
					act_level++;
					if(act_level <= TOTAL_LEVELS){
						//to Win screen
						//initLevel(act_level);
						toWin();
						//toMenu();
					}else{
						//to menu
						toMenu();
					}
				}
			}
		}
	}
}

void Level::toMenu(){
		Game::Instance()->setState(State::StateType::MENU_STATE);
		//reset the game
		Graphics::Instance()->initOAM(); //clear the oam
		Graphics::Instance()->loadMenu();
		Menu::Instance()->initMenu();
}

void Level::toWin(){
		Game::Instance()->setState(State::StateType::WIN_STATE);
		//reset the game
		Graphics::Instance()->initOAM(); //clear the oam
		Graphics::Instance()->loadWin();
		Win::Instance()->setNextLevel(act_level);
}

//public to any class
void Level::initLevel(int level){

	act_level = level;

	switch(level){
		case 1:
			initLevel(level_1, 6, 200);
			break;
		case 2:
			initLevel(level_2, 10, 150);
			break;
		case 3:
			initLevel(level_3, 14, 100);
			break;
		case 4:
			initLevel(level_4, 18, 50);
			break;
		default:
			initLevel(level_1, 6, 200);
			break;
	}

}

//only accesible by level class itself
void Level::initLevel(Enemy* level_data[], int enemies_to_kill_, int spawn_time_){

	x_in = -1;
	y_in = -1;

	//srand (time(NULL));

	auto* g = Graphics::Instance();
	auto* p = Player::Instance();

	//init (or clear) the OAM
	g->initOAM();

	spawn_time = spawn_time_;
	timer = spawn_time;

	//create (or reset) the player
	p->resetPlayer();
	p->setOAMid(g->createPlayer(p->getX(),p->getY()));

	//create the life sprites ()
	for(int i=0; i < MAX_LIFES; i++){
		p->setHeartSpriteId(i,g->createLifeSprites((i*17),0));
	}

	//enemies
	for(int i=0;i<ENEMY_MAX_COUNT;i++){

		//create the enemy
		enemies[i] = level_data[i];
		//in case the enemy isn't reseted
		enemies[i]->reset();
		//create the enemy sprite
		enemies[i]->setOAMid(g->createEnemySprite(enemies[i]->getX(), enemies[i]->getY(), enemies[i]->getPosIni()));
		//create the enemy pattern sprite
		enemies[i]->setPatternSpriteId(g->createDialog(enemies[i]->getType(), enemies[i]->getX()+23, enemies[i]->getY()-3));

	}

	enemies_to_kill = enemies_to_kill_;
	last_activated = 0;
	cont = 0;

}


//Deprecated methods

/*void Level::loadLevelTwo(){

	auto* g = Graphics::Instance();
	auto* p = Player::Instance();

	g->initOAM();

	srand (time(NULL));

	timer = 100;

	//create the player
	p->resetPlayer();
	p->setOAMid(g->createPlayer(p->getX(),p->getY()));

	//create the life sprites
	for(int i=0; i < MAX_LIFES; i++){
		p->setHeartSpriteId(i,g->createLifeSprites(0+(i*16),0));
	}

	//enemies
	for(int i=0;i<ENEMY_MAX_COUNT;i++){

		//randomize BASURA QUE HAY Q CAMBIAR
		int pos = rand() % 6 + 0; 

		//create the enemy
		enemies[i] = new Enemy(pos);
		//create the enemy sprite
		enemies[i]->setOAMid(g->createEnemySprite(enemies[i]->getX(), enemies[i]->getY(), enemies[i]->getPosIni()));
		//create the enemy pattern sprite
		enemies[i]->setPatternSpriteId(g->createDialog(enemies[i]->getType(), enemies[i]->getX()+23, enemies[i]->getY()-3));

	}

	enemies_to_kill = 20;
}

void Level::checkPattern(int x_out, int y_out){

	int a = x_out - x_in;
	int b = y_out - y_in;


	if(b>10&&a<10){ //h line 
		killEnemies(0);
	}else{ 			//v line
		killEnemies(1);
	}
}*/