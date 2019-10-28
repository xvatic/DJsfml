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
    
    Texture t1,t2,t3;
    t1.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/platform1.png");
    t2.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/bg.jpg");
    t3.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/doodle2.png");
    
    Sprite sBackground(t2), sPlat(t1), sPers(t3);
    
    point plat[20];
//    generate plates
    
    for (int i=0;i<10;i++)
    {
        plat[i].x=rand()%SCREEN_WIDTH;
        plat[i].y=rand()%SCREEN_HEIGHT;
    
    }
    
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
        
        sPers.setPosition(x, y);
        
        game.draw(sBackground);
        game.draw(sPers);
         for (int i=0;i<10;i++)
         {
             sPlat.setPosition(plat[i].x, plat[i].y);
             game.draw(sPlat);
         }
        game.display();
    }
    return 0;
    
    
}
