#include "gameboard.h"
#include "exceptions.h"

using namespace gamewindow;

Gamewindow::Gamewindow()
{
    //gameSprites=new vector<Sprite>();
    mapSizeX=850;
    mapSizeY=850;
    screenSizeX=800;
    screenSizeY=800;
    display=NULL;
    event_queue=NULL;
    timer=NULL;
    gameRunning=true;
    FPS=60;
}

Gamewindow::Gamewindow(int sizeX,int sizeY,float fps_arr)
{
    //gameSprites=new vector<Sprite>();
    mapSizeX=850;
    mapSizeY=850;
    screenSizeX=sizeX;
    screenSizeY=sizeY;
    display=NULL;
    event_queue=NULL;
    timer=NULL;
    gameRunning=true;
    redraw=true;
    FPS=fps_arr;
}

Gamewindow::Gamewindow(int sizeX,int sizeY,int mapX,int mapY,float fps_arr)
{
    //gameSprites=new vector<Sprite>();
    mapSizeX=mapX;
    mapSizeY=mapY;
    screenSizeX=sizeX;
    screenSizeY=sizeY;
    display=NULL;
    event_queue=NULL;
    timer=NULL;
    gameRunning=true;
    redraw=true;
    FPS=fps_arr;
}

void Gamewindow::inut_allegro()
{
    gameRunning=true;

    //inut allegro and the plugins we're using
    if(!al_init())
    {
        throw  InutException("allegro failed to start");
    }

    timer=al_create_timer(1.0/FPS);
    if(!timer)
    {
        throw InutException("timer failed to start");
    }

    if(!al_init_image_addon())
    {
        throw InutException("allegro image plugin failed to start");
    }

    display=al_create_display(screenSizeX,screenSizeY);
    if(!display)
    {
        throw InutException("failed to start dispaly");
    }

    if(!al_install_mouse())
    {
        throw InutException("failed to load mouse");
    }
    #ifdef DEBUG
    else
    {
        cout << "mouse is installed, so nothings broken!" << endl;
    }
    #endif

    event_queue=al_create_event_queue();
    if(!event_queue)
    {
        throw InutException("failed to start event que");
    }
    else //register our events
    {
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_mouse_event_source());
    }

    //load the sprite for the backgorund image
    backgroundImage=new Sprite(BACKGROUND_SPRITE,"backgroundsp",0,0);

    //clear the background to black and start the game logic
    //al_clear_to_color(al_map_rgb(0,0,0));
    clearBackGround();
    al_flip_display();
    al_start_timer(timer);

}

void Gamewindow::clearBackGround()
{
    #ifdef DEBUG
    cout << "back ground sprite: " << backgroundImage->getName() << endl;
    #endif

    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(backgroundImage->getBitmap(),0,0,0);

}

void Gamewindow::generateBlocks(int blockMassLengh,int blockMassWidth)
{
    int blockID=0;
    Block *spawned_block;
    int blockSizeX=48;
    int blockSizeY=16;

    for(int i=0;i<blockMassLengh;i++)
    {
        for(int j=0;j<blockMassWidth;j++)
        {
            spawned_block=new Block("./sprites/stone.png",(i*blockSizeX),(j*blockSizeY),blockID);
            gameSprites.push_back(spawned_block);
            blockID++;
        }
    }

    numBlocks=blockID;
}

void Gamewindow::inut_game_elems()
{
    //load some sprites and what not

    //...you know... those picture things

    gameBall=new Ball("./sprites/paddle.png",screenSizeX/2,screenSizeY/2,screenSizeX,screenSizeY,5,4);
    gameBat=new Bat("./sprites/bat.png",screenSizeX/2,((screenSizeY/2)+100),screenSizeX,screenSizeY);

    //generate out blocks to shoot at
    generateBlocks(17,9); //we have an x,y array of blocks to knock out

    //test code for generating blocks
    //Block *testBlock=new Block("./sprites/stone.png",0,0,0);
    //end of test code for generating blocks

    #ifdef DEBUG
    cout << "ball debug..." << endl;
    cout << "starting x cord " << gameBall->getX() << endl;
    cout << "starting y cord " << gameBall->getY() << endl;
    cout << "name as a sprite: " << gameBall->getName() << endl;
    cout << "just after this the ball object is added to the vector of stuff that's going to get drawn on the screen" << endl;
    #endif

    gameSprites.push_back(gameBall);
    gameSprites.push_back(gameBat);
    //gameSprites.push_back(testBlock);

    //I'm gonna hold back on the background for awhile
    //there's some issues with it drawing over other bitmaps
    //and I want to focus more on game elements
    //gameSprites.push_back(backgroundImage);


}

void Gamewindow::reDraw()
{
    if(redraw && al_is_event_queue_empty(event_queue))
    {
        redraw=false;

        //clear the map and redraw our vector of bitmaps
        al_clear_to_color(al_map_rgb(0,0,0));
        //draw all our sprites...

        // #ifdef DEBUG
        // cout << "some debug information on the vector holding the sprites" << endl;
        // cout << "size: " << gameSprites.size() << endl;
        // cout << "capacity: " << gameSprites.capacity() << endl;
        // #endif

        for(int i=0;i<gameSprites.size();i++)
        {
            // #ifdef DEBUG
            // cout << "drawing sprites on the screen " << endl;
            // #endif

            al_draw_bitmap(gameSprites.at(i)->getBitmap(),gameSprites.at(i)->getX(),gameSprites.at(i)->getY(),0);
        }

        al_flip_display();

    }
}

void Gamewindow::game_loop()
{
    while(gameRunning)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);

        if(ev.type==ALLEGRO_EVENT_TIMER)
        {
            //this is where we set the game to it's next state
            if(gameBall->hitFloor()) //tell if the ball hit the floor
            {
                cout << "GAME OVER!!!" << endl;
                gameRunning=false;
            }

            if(numBlocks<=0)
            {
                cout << "YOU ARE WINNER!!!!!" << endl;
                gameRunning=false;
            }

            gameBall->hitWall(); //if the ball hit a wall, then bounce

            gameBall->nextPos();
            if(gameBall->hitSprite(gameSprites))
            {
                if(gameBall->getNameOfLastHitSprite()=="game bat")
                {
                    gameBall->deflectOffBat();
                }

                if(gameBall->getNameOfLastHitSprite()=="block")
                {
                    //maybe change this to an iterator?
                    for(int i=0;i<gameSprites.size();i++)
                    {
                        if(gameSprites.at(i)->hitSprite(gameSprites) && gameSprites.at(i)->getName()=="block")
                        {
                            gameBall->ballDeflectOffBlock();
                            Sprite *removedBlock=gameSprites.at(i);

                            #ifdef DEBUG
                            cout << "block removed from game: " << removedBlock->getName() << endl;
                            #endif

                            gameSprites.erase(gameSprites.begin()+i);
                            delete removedBlock;
                            numBlocks--;
                        }
                    }
                }
            }

            //gameBat->setBatX(gameBall->getX());

            redraw=true;
        }
        else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
        {
            float newBatX=ev.mouse.x;

            gameBat->setBatX(newBatX);
        }

        this->reDraw();
    }
}

Gamewindow::~Gamewindow()
{
    cout << "cleaning up game window..." << endl;
    al_destroy_timer(timer);
    al_destroy_display(display);
    delete backgroundImage;

    //delete the onscreen game sprites
    for(int i=0;i<gameSprites.size();i++)
    {
        #ifdef DEBUG
        cout << "deleting sprite: " << gameSprites.at(i)->getName() << endl;
        #endif

        delete gameSprites.at(i);
    }

    cout << "done!" << endl;
    //clearn up the game loop...
}
