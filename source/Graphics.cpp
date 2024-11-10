//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#define TITLE_TEXT_COLOR ((u16*)0x050005CA)

#include "common_def.h"
#include "Graphics.h"
#include <stdio.h>

//Grit images
#include "GritHeaders.h"

int Graphics::next_avail_id = 0;
int Graphics::next_avail_GFX = 0;

Graphics::Graphics(){
    //create our OAM copy
	oam = new OAMTable();
    //init sprites index, now avail_id = 0 and next_avail_id = 1,
    //ready to be called and create the first sprite
    //updateAvailId();
    r = 31;
    g = 0;
    b = 0;
}

Graphics::Graphics(const Graphics& c){

}

Graphics::~Graphics(){
	delete oam;
}

Graphics* Graphics::Instance(){
	static Graphics pinstance;
	return &pinstance;
}

int Graphics::get_GFX_mem_pos(int spr_size){

    int mem_pos = next_avail_GFX;

    //update the next available tile
    next_avail_GFX = next_avail_GFX + spr_size/2;

    return mem_pos;

}

void Graphics::updateAvailId(){
    avail_id = next_avail_id;
    next_avail_id++;
}

void Graphics::initConsole(){

    //turn on the two graphics engines
	powerOn(POWER_ALL_2D);

    //map video memory
	setBanks();

    //init background registers
	initBackgrounds();

    //init OAM (sprites)
    initOAM();

    //load the menu backgrounds and sprite tiles in memory
    loadMenu();
}

void Graphics::loadMenu(){

    next_avail_GFX = 0;

    //BACKGROUNDS
	//draw bg 3 main screen
	memcpy((uint16 *)BG_BMP_RAM(4),skyBitmap,skyBitmapLen);
    memcpy(BG_PALETTE,skyPal,skyPalLen);

    //draw bg 3 sub screen
    memcpy((uint16 *)BG_BMP_RAM_SUB(0),title_2Bitmap,title_2BitmapLen);
    memcpy(BG_PALETTE_SUB,title_2Pal,title_2PalLen);
    memcpy((uint16 *)BG_BMP_RAM_SUB(4),title_2Bitmap,title_2BitmapLen);

    //sprites
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(eyes_1TilesLen)], eyes_1Tiles, eyes_1TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(eyes_2TilesLen)], eyes_2Tiles, eyes_2TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(eyes_3TilesLen)], eyes_3Tiles, eyes_3TilesLen);
    memcpy(&SPRITE_PALETTE[0], eyes_1Pal, eyes_1PalLen);

}

void Graphics::loadWin(){

    next_avail_GFX = 0;

    memcpy((uint16 *)BG_BMP_RAM(4),win_mainBitmap,win_mainBitmapLen);
    memcpy(BG_PALETTE,win_mainPal,win_mainPalLen);

    //draw bg 3 sub screen
    memcpy((uint16 *)BG_BMP_RAM_SUB(0),win_subBitmap,win_subBitmapLen);
    memcpy(BG_PALETTE_SUB,win_subPal,win_subPalLen);
    memcpy((uint16 *)BG_BMP_RAM_SUB(4),win_subBitmap,win_subBitmapLen);
}

void Graphics::loadLevel(){

    next_avail_GFX = 0;

	//draw bg 3 main screen
	memcpy((uint16 *)BG_BMP_RAM(4),groundBitmap,groundBitmapLen);
    memcpy(BG_PALETTE,groundPal,groundPalLen);

    //canvas bg
    clearCanvasBg();
    memcpy((uint16 *)BG_BMP_RAM_SUB(0),canvasBitmap,canvasBitmapLen);
    memcpy(BG_PALETTE_SUB,canvasPal,canvasPalLen); //copy the palette, but since it's the same for the two bgs we only need to copy it once

    //rainbow bg
    memcpy((uint16 *)BG_BMP_RAM_SUB(4),rainbowBitmap,rainbowBitmapLen);


	//load sprites in memory
    //enemies
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(enemyTilesLen)], enemyTiles, enemyTilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(enemy_2TilesLen)], enemy_2Tiles, enemy_2TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(enemy_3TilesLen)], enemy_3Tiles, enemy_3TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(enemy_4TilesLen)], enemy_4Tiles, enemy_4TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(enemy_5TilesLen)], enemy_5Tiles, enemy_5TilesLen);

    memcpy(&SPRITE_PALETTE[0], enemyPal, enemyPalLen); //all the frames use the same palette

    //player
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_1TilesLen)], player_1Tiles, player_1TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_2TilesLen)], player_2Tiles, player_2TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_3TilesLen)], player_3Tiles, player_3TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_4TilesLen)], player_4Tiles, player_4TilesLen);
    //memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_5TilesLen)], player_5Tiles, player_5TilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_attackTilesLen)], player_attackTiles, player_attackTilesLen);
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(player_hurtTilesLen)], player_hurtTiles, player_hurtTilesLen);

    memcpy(&SPRITE_PALETTE[16], player_1Pal, player_1PalLen); //all the frames use the same palette

    //lifes
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(heartTilesLen)], heartTiles, heartTilesLen);
    memcpy(&SPRITE_PALETTE[32], heartPal, heartPalLen);

    //patterns
    memcpy(&SPRITE_GFX[get_GFX_mem_pos(vlineTilesLen)], vlineTiles, vlineTilesLen);
    memcpy(&SPRITE_PALETTE[48], vlinePal, 32);

    memcpy(&SPRITE_GFX[get_GFX_mem_pos(hlineTilesLen)], hlineTiles, hlineTilesLen);
    memcpy(&SPRITE_PALETTE[64], hlinePal, 32);

    memcpy(&SPRITE_GFX[get_GFX_mem_pos(tlineTilesLen)], tlineTiles, tlineTilesLen);
    memcpy(&SPRITE_PALETTE[80], tlinePal, 32);

}

void Graphics::initOAM(){

    next_avail_id = 0;

   	SpriteEntry* se;
	SpriteRotation* sr;

	for(int i = 0; i < SPRITE_COUNT; i++){
		se = &oam->oamBuffer[i];
		se->attribute[0] = ATTR0_DISABLED;
		se->attribute[1] = 0;
		se->attribute[2] = 0;
		
	}

	for(int j = 0; j < MATRIX_COUNT; j++){
		sr = &oam->matrixBuffer[j];
		sr->hdx = 1 << 8;
		sr->hdy = 0;
		sr->vdx = 0;
		sr->vdy = 1 << 8;
	}

	updateOAM();
}

void Graphics::updateOAM(){
	memcpy(OAM,oam->oamBuffer,SPRITE_COUNT * sizeof (SpriteEntry));
}

void Graphics::setBanks(){

    //main screen (1 extended color palette bg)
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

    //sub screen
    //shared vram for 2 bgs (256 colors, same palette)
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    
    //sprites
	vramSetBankE(VRAM_E_MAIN_SPRITE);

    //video modes
	videoSetMode(MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG3_ACTIVE |  DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D);
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG2_ACTIVE);

}

void Graphics::initBackgrounds(){

    //set control registrers for background  on the main screen (title and level bg)
	REG_BG3CNT = BG_BMP8_256x256 | BG_BMP_BASE(4) | BG_PRIORITY(3);

	REG_BG3PA = 1 << 8;		REG_BG3PB = 0;				
	REG_BG3PC = 0;			REG_BG3PD = 1 << 8;

    REG_BG3X = 0;
    REG_BG3Y = 0;

    //set control registrers for canvas background on the sub screen
    REG_BG3CNT_SUB = BG_BMP8_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(2); //higher priority (the minor is the number, it will appear on top)

    REG_BG3PA_SUB = 1 << 8;  REG_BG3PC_SUB = 0;
    REG_BG3PB_SUB = 0;       REG_BG3PD_SUB = 1 << 8;

    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;

    //set control registrers for the rainbow background on the sub screen
    REG_BG2CNT_SUB = BG_BMP8_256x256 | BG_BMP_BASE(4) | BG_PRIORITY(3);

    REG_BG2PA_SUB = 1 << 8;  REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;       REG_BG2PD_SUB = 1 << 8;

    REG_BG2X_SUB = 0;
    REG_BG2Y_SUB = 0;

    consoleInit(0, 0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true); 

}

void Graphics::updateSpritePosition(int index, int x, int y){

    if(index>=0 && index < next_avail_id){
    	SpriteEntry* sprite = &oam->oamBuffer[index];
    	if(sprite){
    		sprite->x = x;
    		sprite->y = y;
    	}
    }

}

int Graphics::createSprite(int x, int y, SpriteType type){

    //update index
    updateAvailId();

    //create the sprite
    SpriteEntry* sprite = &oam->oamBuffer[avail_id];

    sprite->y = y;
    sprite->x = x;

    switch(type){

        case S_PLAYER:  //player sprite

            sprite->gfxIndex = 320;
            sprite->palette = 1;
            sprite->size = OBJSIZE_64;
            sprite->priority = OBJPRIORITY_2;
            break;

        case S_ENEMY:   //enemy sprite

            sprite->gfxIndex = 0;
            sprite->palette = 0;
            sprite->size = OBJSIZE_64;
            sprite->priority = OBJPRIORITY_3; //default, later may be changed
            break;

        case S_HEART:   //life sprites

            sprite->gfxIndex = 704;
            sprite->palette = 2;
            sprite->size = OBJSIZE_16;
            sprite->priority = OBJPRIORITY_0;
            break;

        case S_EYES: //eyes for the title screen

            sprite->gfxIndex = 0;
            sprite->palette = 0;
            sprite->size = OBJSIZE_64;
            sprite->priority = OBJPRIORITY_0;
            break;

        default:         //any type of pattern
            sprite->gfxIndex = 708;
            sprite->palette = 3;
            sprite->size = OBJSIZE_16;
            sprite->priority = OBJPRIORITY_1; //default, later may be changed
            break;
    }

    //common values for all sprites
    sprite->shape = OBJSHAPE_SQUARE;
    sprite->isRotateScale = false;
    sprite->isSizeDouble = false;
    sprite->blendMode = OBJMODE_NORMAL;
    sprite->isMosaic = false;
    sprite->colorMode = OBJCOLOR_16;

    updateOAM();

    return avail_id;
}

int Graphics::createPlayer(int x, int y){

    SpriteType sp_type = S_PLAYER;

	return createSprite(x, y, sp_type);
}

int Graphics::createEyesSprite(int x, int y){

    SpriteType sp_type = S_EYES;

    return createSprite(x, y, sp_type);
}

int Graphics::createEnemySprite(int x, int y, int posType){

    SpriteType sp_type = S_ENEMY;

    int id = createSprite(x, y, sp_type);

	SpriteEntry* sprite = &oam->oamBuffer[id];

    if(posType >= 2){
        sprite->priority = OBJPRIORITY_0;
    }

    if(posType == 0 || posType == 2){
            sprite->hFlip = true;
    }

    updateOAM();

    return id;

}

int Graphics::createDialog(int type, int x, int y){

    SpriteType sp_type = S_PATTERN_H; //default pattern

    int id = createSprite(x, y, sp_type);

    SpriteEntry* sprite = &oam->oamBuffer[id];

    if(type == 0 ){
        sprite->gfxIndex = 708;
        sprite->palette = 3;
    }else if(type == 1){
        sprite->gfxIndex = 712;
        sprite->palette = 4;
    }else if(type == 2){
        sprite->gfxIndex = 716;
        sprite->palette = 5;
    }

    updateOAM();

    return id;
}

void Graphics::setVisible(int index, bool h){

    if(index>=0 && index < next_avail_id){
        SpriteEntry* sprite = &oam->oamBuffer[index];
        if(sprite){
            sprite->isHidden = h;
        }
    }
}

int Graphics::createLifeSprites(int x, int y){

    SpriteType sp_type = S_HEART; //default pattern

    int id = createSprite(x, y, sp_type);

    return id;
}

void Graphics::drawCircleSub(int x, int y){

    int add = x + SCREEN_WIDTH * y;
    add = add/2;

    dmaCopy(&color, SCREEN_START + add , 2);

    //same line
    dmaCopy(&color, SCREEN_START + add -1 , 2);
    dmaCopy(&color, SCREEN_START + add +1 , 2);
    dmaCopy(&color, SCREEN_START + add -2 , 2);
    dmaCopy(&color, SCREEN_START + add +2 , 2);


    //bottom
    dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH/2 , 2); //1st line on top
        dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH/2 +1, 2);
        dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH/2 +2, 2);

        dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH/2 -1, 2);
        dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH/2 -2, 2);

    dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH , 2); //2nd line on top
            dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH +1, 2);
            dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH +2, 2);
            dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH -1, 2);
            dmaCopy(&color, SCREEN_START + add +SCREEN_WIDTH -2, 2);

    dmaCopy(&color, SCREEN_START + add +3*SCREEN_WIDTH/2 , 2); //3rd
        dmaCopy(&color, SCREEN_START + add +3*SCREEN_WIDTH/2 +1 , 2);
        dmaCopy(&color, SCREEN_START + add +3*SCREEN_WIDTH/2 -1 , 2);

    dmaCopy(&color, SCREEN_START + add +2*SCREEN_WIDTH , 2); //4th
        dmaCopy(&color, SCREEN_START + add +2*SCREEN_WIDTH +1, 2);
        dmaCopy(&color, SCREEN_START + add +2*SCREEN_WIDTH -1, 2);


    //top
    dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH/2 , 2); //1st line
        dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH/2 +1, 2);
        dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH/2 +2, 2);

        dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH/2 -1, 2);
        dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH/2 -2, 2);

    dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH , 2); //2nd line
            dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH +1, 2);
            dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH +2, 2);
            dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH -1, 2);
            dmaCopy(&color, SCREEN_START + add -SCREEN_WIDTH -2, 2);

    dmaCopy(&color, SCREEN_START + add -3*SCREEN_WIDTH/2 , 2); //3rd
        dmaCopy(&color, SCREEN_START + add -3*SCREEN_WIDTH/2 +1 , 2);
        dmaCopy(&color, SCREEN_START + add -3*SCREEN_WIDTH/2 -1 , 2);

    dmaCopy(&color, SCREEN_START + add -2*SCREEN_WIDTH , 2); //4th
        dmaCopy(&color, SCREEN_START + add -2*SCREEN_WIDTH +1, 2);
        dmaCopy(&color, SCREEN_START + add -2*SCREEN_WIDTH -1, 2);

}

void Graphics::drawLineSub(int x_i, int y_i, int x_f, int y_f){

    int dx = x_f - x_i;
    int dy = y_f - y_i;

    int inc_x_i, inc_x_r, inc_y_i, inc_y_r = 0;

    //set the displacements on x axis
    if(dx >= 0){
        inc_x_i = 1;
    }else{
        dx = -dx;
        inc_x_i = -1;
    }

    //set the displacements on y axis
    if(dy >= 0){
        inc_y_i = 1;
    }else{
        dy = -dy;
        inc_y_i = -1;
    }

    //displacements for horizontal and vertical movements
    if(dx >= dy){

        inc_x_r = inc_x_i;
        inc_y_r = 0;

    }else{

        inc_x_r = 0;
        inc_y_r = inc_y_i;

        int aux = dx;
        dx = dy;
        dy = aux;
    }

    int av_r = 2 * dy;
    int av = av_r - dx;
    int av_i = av - dx;

    int x_act = x_i;
    int y_act = y_i;

    do{

        drawCircleSub(x_act, y_act);

        if(av >= 0){

            x_act = x_act + inc_x_i;
            y_act = y_act + inc_y_i;
            av = av + av_i;

        }else{

            x_act = x_act + inc_x_r;
            y_act = y_act + inc_y_r;
            av = av + av_r;

        }


    }while(x_act != x_f || y_act != y_f);
}

void Graphics::clearCanvasBg(){
    memcpy((uint16 *)BG_BMP_RAM_SUB(0),canvasBitmap,canvasBitmapLen);
}

void Graphics::animatePlayer(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    if(sprite->gfxIndex < 512){
        sprite->gfxIndex+= 64;
    }else{
        sprite->gfxIndex = 320;
    }

}

void Graphics::animateEnemyRun(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    if(sprite->gfxIndex < 256){
        sprite->gfxIndex+= 64;
    }else{
        sprite->gfxIndex = 64;
    }
}

void Graphics::resetEnemySprite(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    if(sprite->gfxIndex != 0){
        sprite->gfxIndex = 0;
    }
}

void Graphics::fadeTitleText(){

    //source of the algorythm: CodePen
    //https://codepen.io/Codepixl/pen/ogWWaK/

    if(r > 0 && b == 0){
        r--;
        g++;
    }if(g > 0 && r == 0){
        g--;
        b++;
    }if(b > 0 && g == 0){
        r++;
        b--;
    }

    unsigned short color = RGB15(r,g,b);
    memcpy(TITLE_TEXT_COLOR,&color,sizeof(color));
    memcpy(TITLE_TEXT_COLOR+1,&color,sizeof(color));
    memcpy(TITLE_TEXT_COLOR+2,&color,sizeof(color));
}

void Graphics::animateEyes(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    if(sprite->gfxIndex < 128){
        sprite->gfxIndex+= 64;
    }else{
        sprite->gfxIndex = 0;
    }
}

void Graphics::resetEyes(int id){
        
    SpriteEntry* sprite = &oam->oamBuffer[id];

    sprite->gfxIndex = 0;
}

void Graphics::setPlayerHurtSpr(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    sprite->gfxIndex = 640;
}

void Graphics::setPlayerAttackSpr(int id){
    SpriteEntry* sprite = &oam->oamBuffer[id];

    sprite->gfxIndex = 576;
}