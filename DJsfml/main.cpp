//
//  main.cpp
//  DJsfml
//
//  Created by Евгений on 10/28/19.
//  Copyright © 2019 Евгений. All rights reserved.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>


#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 1024
using namespace sf;

class point
{
public:
    int x,y;
};

RenderWindow game(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Doodle jump");


bool isMonsterDrawn = false;
Texture t1,t2,t3,t4,t5,t6,t7,t8;


Sprite sBackground, sPlat, sPers, sMonster,sGO, sBullet, sFakePanel;

point plat[100];
point monster[1];
point FakePlat[12];
point bullet;

int x=400,y=1020,h=250;
float dx=0,dy=0;
bool isShoot = false;
int counter=0;

void setSeed() {
    srand(time(0));
}

void imports()
{
    t1.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/platform1.png");
    t2.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/bg.jpg");
    t3.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/doodle2.png");
    t4.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/monster2.png");
    t5.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/go.jpg");
    t6.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/doodle2r.png");
    t7.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/Golf_Ball.png");
    t8.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/fakepanel1.png");
}


void clearScreen() {
    printf("\e[1;1H\e[2J");
    //flush(std::cout);
}

void setUpApp()
{
    game.setFramerateLimit(60);
    
    imports();
    
    sPers = Sprite(t3);
    sPlat = Sprite(t1);
    sBackground = Sprite(t2);
    sMonster = Sprite(t4);
    sBullet = Sprite(t7);
    sFakePanel = Sprite(t8);
    
    sFakePanel.scale(0.25f, 0.5f);
    
    for (int i=0;i<=3;i++)
    {
        plat[i].x=rand()%522;
        plat[i].y=768 +(rand()%256);
        if (i==3){
            FakePlat[i].x=rand()%522;
            FakePlat[i].y=768 +(rand()%256);
        }
        
    }
    
    for (int i=4;i<=6;i++)
    {
        plat[i].x=rand()%522;
        plat[i].y=512+(rand()%256);
        if (i==6){
            FakePlat[i].x=rand()%522;
            FakePlat[i].y=768 +(rand()%256);
        }
    }
    
    for (int i=7;i<=9;i++)
    {
        plat[i].x=rand()%522;
        plat[i].y=256+(rand()%256);
        if (i==9){
            FakePlat[i].x=rand()%522;
            FakePlat[i].y=768 +(rand()%256);
        }
        
    }
    
    for (int i=10;i<=12;i++)
    {
        plat[i].x=rand()%522;
        plat[i].y=rand()%256;
        if (i==12){
            FakePlat[i].x=rand()%522;
            FakePlat[i].y=768 +(rand()%256);
        }
    }
    
   
    
   
    
    
    
}




int checkX2(int x)
{
    switch (x) {
        case 640:
            x=0;
            return x;
            break;
        case 0:
            x=640;
            return x;
            break;
       
        default:
            break;
    }
    
   
    
    return x;
}

std::string convertToString(char* a,int size)
{
    int i;
    std::string s = "";
    for(i=0; i<size;i++){
       
        s=s+a[i];
    }
    return s;
    
}

void gameover(int counter){
    
    RenderWindow result(sf::VideoMode(500,500),"RESULT");
    result.setFramerateLimit(60);
    Texture r1;
    r1.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/go.jpg");
    Sprite sRes(r1);
    sf::Text score;
    sf::Font Font;
    char str[5];
    std::ifstream fout("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/scores.txt");
    fout.getline(str, 50);
    fout.close();
    int b=0;
    std::string best = convertToString(str, 3);
    std::stringstream bestf(best);
    bestf >> b;
    
    bool isNewScore=false;
    if (counter>b)
    {
        std::ofstream fout("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/scores.txt",std::ios::trunc);
        fout.close();
        std::ofstream fscore("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/scores.txt",std::ios::out);
        std::string s = std::to_string(counter);
        fscore << s;
        fout.close();
        isNewScore = true;
        
    }
    
    
    
    
   
    
//    sf::SoundBuffer buffer;
 //   buffer.loadFromFile();// тут загружаем в буфер что то
 //   sf::Sound sound;
  //  sound.setBuffer(buffer);
  //  sound.play();
    if (!Font.loadFromFile("/Users/zhenya_rs6/Downloads/Arial/Arial.ttf"))
    {
        //handle error
    }
    
    score.setCharacterSize(50);
    std::string s = std::to_string(counter);
   
    if (isNewScore==true)
    {
        score.setString("       NEW BEST:"+s);
    }
    else
    {
     score.setString("       GAME OVER\n        SCORE: "+s);
    }
    score.setFont(Font);
    score.setFillColor(sf::Color::Cyan);
    while (result.isOpen()) {
        result.clear();
        
        Event e;
        while (result.pollEvent(e))
        {
            if (e.type == Event::Closed)
                result.close();
        }
        
       // result.draw(sRes);
        result.draw(score);
        result.display();
        }
    
   
    
}

void run()
{
    x=checkX2(x);
    
    Event e;
    while (game.pollEvent(e))
    {
        if (e.type == Event::Closed)
            game.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        x+=4;
        sPers.setTexture(t6);
        
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)){
        isShoot=true;
        
    }
    
    if (Keyboard::isKeyPressed(Keyboard::Left)){
        x-=4;
        sPers.setTexture(t3);
    }
    
    dy+=0.2;
    y+=dy;
    if (y>900) dy=-10;
    
    if (y<h){
        for (int i=0;i<=12;i++)
        {
            y=h;
            plat[i].y=plat[i].y-dy;
            FakePlat[i].y=FakePlat[i].y-dy;
           
            if (plat[i].y>900)
            {plat[i].y=0; plat[i].x= rand()%650;
                if (FakePlat[i].y>900){
                    FakePlat[i].y=0; FakePlat[i].x= rand()%650;
                }
            }
            
    }
         monster[1].y-=dy;
        int i=1;
       
        if (monster[1].y>1100)
        {
        int isMonsterSpawn = rand()%15;
        if ((isMonsterSpawn==1 || isMonsterSpawn==2 || isMonsterSpawn==3) && counter>100){
            
            monster[i].x=40+rand()%500;
            monster[i].y=0;
            isMonsterDrawn=true;
        }
        else{
            isMonsterDrawn=false;
        }
                
        }
    
    }
    
    
    for (int i=0;i<12;i++)
    {
        if ((x+60>plat[i].x) && (x+30<plat[i].x+128) && (y+78>plat[i].y) && (y+78<plat[i].y+46) && (dy>0))
        {
            dy=-10;
            counter+=15;
        }
    }
    // doodle 90x88   plate 128x46 monster 240x168
    int  i=1;
    
    if ((x>monster[i].x-90) && (x<monster[i].x+96) && (y>monster[i].y-98) && (y<monster[i].y+110) && isMonsterDrawn == true)
    {
        game.close();
        
        gameover(counter);
        
    }
    if (y>900 && counter>45)
    {
        game.close();
        gameover(counter);
    }
    
    
    // bullet.x=x;
    //  bullet.y=y;
    
    //  sBullet.setPosition(bullet.x, bullet.x);
    game.draw(sBullet);
    
    
    sPers.setPosition(x, y);
    
    game.draw(sBackground);
    game.draw(sPers);
    i=1;
    if (counter>100) {
        sMonster.setPosition(monster[i].x, monster[i].y);
        game.draw(sMonster);
        isMonsterDrawn = true;
    }
    
    for (int i=0;i<12;i++)
    {
        sPlat.setPosition(plat[i].x, plat[i].y);
        game.draw(sPlat);
        
    }
    for (int i=0;i<=12;i++){
        if (i==3 || i==6 || i==9 || i==12)
        {
            sFakePanel.setPosition(FakePlat[i].x, FakePlat[i].y);
            game.draw(sFakePanel);
            
        }
    }
    
    game.display();
}

void init()
{
    setSeed();
    
    setUpApp();
}


int main( )
{
    
    
    init();

 
    while (game.isOpen())
    {
        run();
    }
    return 0;
    
    
}
