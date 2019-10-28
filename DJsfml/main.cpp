//
//  main.cpp
//  DJsfml
//
//  Created by Евгений on 10/28/19.
//  Copyright © 2019 Евгений. All rights reserved.
//
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
using namespace sf;

struct point
{
    int x,y;
    
};

int main( )
{
    
    srand(time(0));
    RenderWindow game(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Doodle jump");
    
    game.setFramerateLimit(60);
    
    Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/platform1.png");
    t2.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/bg.jpg");
    t3.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/doodle2.png");
    t4.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/monster.png");
    t5.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/go.jpg");
    Sprite sBackground(t2), sPlat(t1), sPers(t3), sMonster(t4),sGO(t5);
    
    point plat[20];
    point monster[1];
//    generate plates
    
    for (int i=0;i<10;i++)
    {
        plat[i].x=rand()%SCREEN_WIDTH;
        plat[i].y=rand()%SCREEN_HEIGHT;
       
        
    }
    int i=1;
    int m=rand()%10;
    monster[i].x=plat[m].x;
    monster[i].y=plat[m].y-250;
    
    
    int x=400,y=1020,h=100;
    float dx=0,dy=0;
    
    while (game.isOpen())
    {
        Event e;
        while (game.pollEvent(e))
        {
            if (e.type == Event::Closed)
                game.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) x+=4;
          if (Keyboard::isKeyPressed(Keyboard::Left)) x-=4;
        
        dy+=0.2;
        y+=dy;
        if (y>900) dy=-10;
        
        if (y<h)
            for (int i=0;i<10;i++)
            {
                y=h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y<1024){plat[i].y=0; plat[i].x= rand()%1024;}
            }
        
        for (int i=0;i<10;i++)
        {
            if ((x+50>plat[i].x) && (x+20<plat[i].x+50) && (y+50>plat[i].y) && (y+70>plat[i].y+14) && (dy>0))
                dy=-10;
        }
       
        i=1;
        
        if ((x==monster[i].x) && (y==monster[i].y) )
        { game.draw(sGO);}

        
        sPers.setPosition(x, y);
        
        game.draw(sBackground);
        game.draw(sPers);
        i=1;
        sMonster.setPosition(monster[i].x, monster[i].y);
        game.draw(sMonster);
         for (int i=0;i<10;i++)
         {
             sPlat.setPosition(plat[i].x, plat[i].y);
             game.draw(sPlat);
            
         }
        game.display();
    }
    return 0;
    
    
}
