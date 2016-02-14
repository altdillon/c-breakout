#include "sprite.h"

using namespace game_sprites;
using namespace game_exceptions;

Sprite::Sprite(string fileName,string name)
{
    this->fileName=fileName;
    spriteName=name;
    sprite_bitmap=NULL;
    loadSprite(fileName);
}

Sprite::Sprite(string fileName,string name,float spX,float spY)
{
    this->fileName=fileName;
    spriteName=name;
    sp_pos.x=spX;
    sp_pos.y=spY;
    sprite_bitmap=NULL;
    loadSprite(fileName);
}

Sprite::Sprite(string fileName,string name,float spX,float spY,int imageX,int imageY)
{
    this->sprite_sizeX=imageX;
    this->sprite_sizeY=imageY;
    this->fileName=fileName;
    spriteName=name;
    sp_pos.x=spX;
    sp_pos.y=spY;
    sprite_bitmap=NULL;
    loadSprite(fileName);
}

Sprite::Sprite(string fileName,float spX,float spY)
{
    this->fileName=fileName;
    sp_pos.x=spX;
    sp_pos.y=spY;
}

//NOTE: getReaX & getRealY may cause run time issues
float Sprite::getRealX()
{
    return sp_pos.x/2;
}

float Sprite::getRealY()
{
    return sp_pos.y/2;
}

float Sprite::getX()
{
    return sp_pos.x;
}

float Sprite::getY()
{
    return sp_pos.y;
}

string Sprite::getName()
{
    return spriteName;
}

void Sprite::loadSprite(string fileName)
{
    sprite_bitmap=al_load_bitmap(fileName.c_str());

    if(!sprite_bitmap)
    {
        throw new SpriteException("bitmap for sprite: "+spriteName+" failed to load");
    }
}

ALLEGRO_BITMAP* Sprite::getBitmap()
{
    return sprite_bitmap;
}

int Sprite::get_sizeX()
{
    return sprite_sizeX;
}

int Sprite::get_sizeY()
{
    return sprite_sizeY;
}


bool Sprite::hitSprite(vector<Sprite*> sprites)
{
    bool detected=false;

    for(vector<Sprite*>::iterator sp=sprites.begin(); sp != sprites.end(); sp++)
    {

        if(!((*sp)->getName() == this->getName()))
        {
            //rect1 = this
            //rect2 = sp

            //bookmark: to compare between sprites
            if(this->getX() < (*sp)->getX() + (*sp)->get_sizeX() && this->getX() + this->get_sizeX() > (*sp)->getX() && this->getY() < (*sp)->getY() + (*sp)->get_sizeY() && this->get_sizeX() + this->getY() > (*sp)->getY())
            {
                #ifdef DEBUG
                cout << "collision detected!" << endl;
                cout << "sprite that was colided with: " << (*sp)->getName() << endl;
                #endif

                name_oflastOtherSpriteTouched=(*sp)->getName();
                detected=true;
            }
        }

    }

    return detected;
}

string Sprite::getNameOfLastHitSprite()
{
    return name_oflastOtherSpriteTouched;
}

Sprite::~Sprite()
{
    al_destroy_bitmap(sprite_bitmap);
}
