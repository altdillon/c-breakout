#include "game_elements.h"

using namespace game_elements;

void Ball::bounceX()
{
    vectorX=vectorX*-1;
}

void Ball::bounceY()
{
    vectorY=vectorY*-1;
}

void Ball::nextPos()
{
    sp_pos.x+=vectorX;
    sp_pos.y+=vectorY;
}

bool Ball::hitFloor()
{
    bool did_hit_floor=false;

    if(hitWall_Y() && sp_pos.y>0)
    {
        did_hit_floor=true;
    }

    return did_hit_floor;
}

//change this: hit wall and bounce should be in two seprate methods.
bool Ball::hitWall()
{
    bool did_hit=false;

    if(sp_pos.x < 0 || sp_pos.x > (this->screenSizeX-sprite_sizeX))
    {
        this->bounceX();
        did_hit=true;
    }

    if(sp_pos.y < 0 || sp_pos.y > (this->screenSizeY-sprite_sizeY))
    {
        this->bounceY();
        did_hit=true;
    }

    return did_hit;
}

bool Ball::hitWall_X()
{
    bool hit_wall=false;

    if(sp_pos.x < 0 || sp_pos.x > (this->screenSizeX-sprite_sizeX))
    {
        hit_wall=true;
    }

    return hit_wall;
}

bool Ball::hitWall_Y()
{
    bool hit_wall=false;

    if(sp_pos.y < 0 || sp_pos.y > (this->screenSizeY-sprite_sizeY))
    {
        hit_wall=true;
    }

    return hit_wall;
}

void Ball::changeSpeed(float speedX,float speedY)
{
    vectorX=speedX;
    vectorY=speedX;
}
void Ball::deflectOffBat()
{
    //vectorX=vectorX*-1;
    vectorY=vectorY*-1;
}

void Ball::ballDeflectOffBlock()
{
    //vectorX=vectorX*-1;
    vectorY=vectorY*-1;
}
