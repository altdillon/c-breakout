#ifndef _SPRITE_H_
#define _SPRITE_H_
#define DEBUG
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "exceptions.h"


using namespace std;
using namespace game_exceptions;

namespace game_sprites
{

/*
    This is ment to be used as an abstract class for sprite info
    it can, however, just be used for a sprite
*/

  typedef struct sprite_pos_st
  {
    float x;
    float y;
  } SPRITE_POS;

  class Sprite //every thing on screen inharets from this class
  {
  public:
      Sprite(string fileName,string name);
      Sprite(string fileName,string name,float spX,float spY);
      Sprite(string fileName,string name,float spX,float spY,int imageX,int imageY);
      Sprite(string fileName,float spX,float spY);
      float getRealX(); //gets the center of the sprite's X
      float getRealY(); //gets the center of the sprite's Y
      //getX & getY return only where the sprite is drawn
      float getX();
      float getY();
      //acccesors to sizex and sizey
      int get_sizeX();
      int get_sizeY();
      void drawSprite(float x,float y); //moves the sprite's x and y to a diffent part of the screen
      string getName();
      ALLEGRO_BITMAP* getBitmap();
      bool hitSprite(vector<Sprite*> sprites); //goes through all the sprites that have diffent names from the current sprite and see's
      //if any of them where hit
      string getNameOfLastHitSprite(); //returns the name of the sprite that
      bool wasHit(Sprite &one,Sprite &two); //this may not get used, but it's for telling it two sprites are in the same place

      ~Sprite(); //clearns up the bitmap of the sprite when the program ends
  private:
    //SPRITE_POS sp_pos;
    string name_oflastOtherSpriteTouched; //this is the name of the last sprite touched
    string fileName;
    string spriteName;
    ALLEGRO_BITMAP *sprite_bitmap;
    void loadSprite(string fileName); //loads the sprite from a file
    //void deleteSpriteBitmap();

  protected:
     SPRITE_POS sp_pos;
     int sprite_sizeX;
     int sprite_sizeY;
  };

}

#endif
