#ifndef GAME_ELEMS_H_
#define GAME_ELEMS_H_
#define DEBUG
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "exceptions.h"
#include "sprite.h"

using namespace std;
using namespace game_sprites;
using namespace game_exceptions;

namespace game_elements
{
    class Ball : public Sprite
    {
    public:
        //adding {} to the header file might be kinda weird
        Ball(string fileName,float posX,float posY,int screenSizeX,int screenSizeY,int speedX,int speedY) : Sprite(fileName,"game ball",posX,posY,16,16)
        {

            //set the speed of the bouning ball...
            vectorX=speedX;
            vectorY=speedY;

            #ifdef DEBUG
            cout << "called constructor for ball object" << endl;
            cout << "starting value for vectorX: " << vectorX << endl;
            cout << "starting value for vectorY: " << vectorY << endl;
            #endif

            this->screenSizeX=screenSizeX;
            this->screenSizeY=screenSizeY;
        }

        void bounceX(); //sends the ball backwards on the X vector if it hits a wall
        void bounceY(); //sends the ball backwars on the y vector if it hits a wall
        void nextPos(); //advances the ball to the next position
        bool hitWall(); //returns true if the ball hit a wall, also reverses the ball's x&y vectors
        bool hitFloor(); //returns true if the ball is currntly less then the floor limit of the map
        void changeSpeed(float speedX,float speedY); //set a new speedX and speedY
        void deflectOffBat(); //makes the vall mounce off of something
        void ballHitBlock(vector<Sprite*> sprites); //when a collision happens between a ball and something else
        void ballDeflectOffBlock(); //called when a ball deflects off of a block

    private:
        int screenSizeX;
        int screenSizeY;
        float vectorX;
        float vectorY;
    };

    class Bat : public Sprite
    {
    public:
        Bat(string fileName,float startX,float startY,int screenSizeX,int screenSizeY) : Sprite(fileName,"game bat",startX,startY,64,16)
        {
            #ifdef DEBUG
            cout << "constructor for game bat called " << endl;
            #endif

        }

        void setBatX(float nextX); //set the new x cord for the bat

    private:
        //there are not private memebers
    };

    class Block : public Sprite
    {
    public:
        Block(string fileName,float posX,float posY,int id) : Sprite(fileName,"block",posX,posY,48,16)
        {
            #ifdef DEBUG
                cout << "constructor for block called " << endl;
            #endif

            block_id=id;
            //block_count++;
        }

        //void destoryBlock();
        ~Block();

    private:
        //static int block_count;
        int block_id;
    };
}

#endif
