#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#define DEBUG
#define BACKGROUND_SPRITE "./sprites/rippofbreakout.png"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "exceptions.h"
#include "sprite.h"
#include "game_elements.h"

using namespace std;
using namespace game_exceptions;
using namespace game_sprites;
using namespace game_elements;

namespace gamewindow
{
    typedef Sprite* sprite_ptr;

    class Gamewindow
    {
    public:
        Gamewindow(int sizeX,int sizeY,float fps_arr); //set's up screen size
        Gamewindow(int sizeX,int sizeY,int mapX,int mapY,float fps_arr); //set's up screen size and map size
        Gamewindow(); //sets up screen size with defult values
        ~Gamewindow(); //clearns every thing up with allegro after we're done
        void inut_allegro(); //starts up allegro game elements
        void inut_game_elems();
        void game_loop(); //runs the game loop
        void cleanUp(); //cleans up the bitmaps used for the game
    private:
        void reDraw();
        void clearBackGround();
        void generateBlocks(int blockMassLengh,int blockMassWidth);
        vector<Sprite*> gameSprites;
        Sprite *backgroundImage;
        Ball *gameBall;
        Bat *gameBat;
        bool gameRunning;
        bool redraw;
        int screenSizeX;
        int screenSizeY;
        int mapSizeX;
        int mapSizeY;
        float FPS;
        int numBlocks;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_TIMER *timer;
    };
}

#endif
