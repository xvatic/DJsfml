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
#define OUTGEN 1100
#define GAMEOVER_SCREEN 500
#define DOODLE_WIDTH 90
#define DOODLE_HEIGHT 88
#define MONSTER_WIDTH 96
#define MONSTER_HEIGHT 110
#define PLATE_WIDTH 128
#define PLATE_HEIGHT 46
#define YRANGE_GEN 900
#define FAKE_WIDTH 122
#define FAKE_HEIGHT 56
#define JETPACK_WIDTH 61
#define JETPACK_HEIGHT 87
#define BORDER1 256
#define BORDER2 512
#define BORDER3 768

using namespace sf;

class point
{
public:
    int x,y;
};

RenderWindow game(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Doodle jump");


bool isMonsterDrawn = false;
bool isFlight = false;
int scoreplus;
int i;
Texture t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11;


Sprite sBackground, sPlat, sPers, sMonster,sGO, sBullet, sFakePanel,sBrokenPlat,sJetpack;

SoundBuffer deathSoundBuffer;
SoundBuffer jumpSoundBuffer;
SoundBuffer monsterSoundBuffer;
SoundBuffer jetSoundBuffer;


Sound death;
Sound jump;
Sound monsterhit;
Sound jet;

point plat[100];
point monster[1];
point FakePlat[12];
point JetPack[1];
point BrokenPlat[12];
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
    t9.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/fakepanel-b.png");
    t10.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/jetpack.png");
    t11.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/textures/jet.png");
    
    deathSoundBuffer.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/sounds/fall.ogg");
    jumpSoundBuffer.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/sounds/jump.ogg");
    monsterSoundBuffer.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/sounds/monster.ogg");
    jetSoundBuffer.loadFromFile("/Users/zhenya_rs6/Desktop/SFML/DJsfml/sounds/jet.wav");
   

    
}


void clearScreen()
{
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
    sBrokenPlat = Sprite(t9);
    sJetpack = Sprite(t10);
    
    
    sFakePanel.scale(0.25f, 0.5f);
    sBrokenPlat.scale(0.25f,0.5f);
    sJetpack.scale(0.17f,0.17f);
    
    death.setBuffer(deathSoundBuffer);
    jump.setBuffer(jumpSoundBuffer);
    monsterhit.setBuffer(monsterSoundBuffer);
    jet.setBuffer(jetSoundBuffer);
  
    
    
    for (int i=0;i<=3;i++)
    {
        plat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
        plat[i].y=BORDER3 +(rand()%BORDER1);
        if (i==3)
        {
            FakePlat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
            FakePlat[i].y=BORDER3 +(rand()%BORDER1);
        }
        
    }
    
    for (int i=4;i<=6;i++)
    {
        plat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
        plat[i].y=BORDER2+(rand()%BORDER1);
        if (i==6)
        {
            FakePlat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
            FakePlat[i].y=BORDER3 +(rand()%BORDER1);
        }
    }
    
    for (int i=7;i<=9;i++)
    {
        plat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
        plat[i].y=BORDER1+(rand()%BORDER1);
        if (i==9)
        {
            FakePlat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
            FakePlat[i].y=BORDER3 +(rand()%BORDER1);
        }
        
    }
    
    for (int i=10;i<=12;i++)
    {
        plat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
        plat[i].y=rand()%BORDER1;
        if (i==12)
        {
            FakePlat[i].x=rand()%(SCREEN_WIDTH-PLATE_WIDTH);
            FakePlat[i].y=BORDER3 +(rand()%BORDER1);
        }
    }
    
    JetPack[1].x=0;
    JetPack[1].y=0;
    
   
    
    
    
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
    for(i=0; i<size;i++)
    {
       
        s=s+a[i];
    }
    return s;
    
}

void gameover(int counter){
    
    RenderWindow result(sf::VideoMode(GAMEOVER_SCREEN,GAMEOVER_SCREEN),"RESULT");
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
    std::string best = convertToString(str, 5);
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
        score.setString(" NEW BEST:"+s);
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
        
       
        result.draw(score);
        result.display();
        }
    
   
    
}


void drawing()
{
    sPers.setPosition(x, y);
    
    game.draw(sBackground);
    game.draw(sPers);
    i=1;
    if (counter>100)
    {
        sMonster.setPosition(monster[i].x, monster[i].y);
        game.draw(sMonster);
        isMonsterDrawn = true;
    }
    
    for (int i=0;i<12;i++)
    {
        sPlat.setPosition(plat[i].x, plat[i].y);
        game.draw(sPlat);
        
    }
    for (int i=0;i<=12;i++)
    {
        if (i==3 || i==6 || i==9 )
        {
            if (FakePlat[i].x!=BrokenPlat[3].x && FakePlat[i].x!=BrokenPlat[6].x && FakePlat[i].x!=BrokenPlat[9].x && FakePlat[i].x!=BrokenPlat[12].x)
            {
                sFakePanel.setPosition(FakePlat[i].x, FakePlat[i].y);
                game.draw(sFakePanel);
            }
        }
    }
    
    for (int i=0;i<=12;i++)
    {
        if (i==3 || i==6 || i==9 )
        {
            if (BrokenPlat[i].x!=0 && BrokenPlat[i].y!=0)
            {
                sBrokenPlat.setPosition(BrokenPlat[i].x, BrokenPlat[i].y);
                game.draw(sBrokenPlat);
            }
            
            
        }
    }
    
    if (JetPack[1].x!=0 && JetPack[1].y!=0 && counter>=120)
    {
        sJetpack.setPosition(JetPack[1].x,JetPack[1].y);
        game.draw(sJetpack);
        
    }
}


void reRender()
{
    counter+=5;
    for (int i=0;i<=12;i++)
    {
        y=h;
        plat[i].y=plat[i].y-dy;
        FakePlat[i].y=FakePlat[i].y-dy;
        BrokenPlat[i].y=BrokenPlat[i].y-dy+50;
        
        
        if (plat[i].y>YRANGE_GEN)
        {plat[i].y=0; plat[i].x= rand()%SCREEN_WIDTH;
            if (FakePlat[i].y>YRANGE_GEN)
            {
                FakePlat[i].y=0; FakePlat[i].x= rand()%SCREEN_WIDTH;
            }
        }
        
    }
    monster[1].y-=dy;
    int i=1;
    
    if (monster[1].y>OUTGEN)
    {
        int isMonsterSpawn = rand()%15;
        if ((isMonsterSpawn==1 || isMonsterSpawn==2 || isMonsterSpawn==3) && counter>100){
            
            monster[i].x=40+rand()%400;
            monster[i].y=0;
            isMonsterDrawn=true;
        }
        else
        {
            isMonsterDrawn=false;
        }
        
    }
    
    JetPack[1].y-=dy;
    if (JetPack[1].y>OUTGEN)
    {
        i=rand()%15;
        if (i==1 || i==2 || i==3 || i==4 || i == 5 || i==6) {
            
            JetPack[1].y=0;
            JetPack[1].x=40+rand()%400;
            
        }
        else
        {
            JetPack[1].x=0;
            JetPack[1].y=0;
        }
    }
}

void checktouch()
{
    
    for (int i=0;i<12;i++)
    {
        if ((x+60>plat[i].x) && (x+30<plat[i].x+PLATE_WIDTH) && (y+78>plat[i].y) && (y+78<plat[i].y+PLATE_HEIGHT) && (dy>0))
        {
            jump.play();
            dy=-10;
           
            
        }
    }
    
    if ((x>JetPack[1].x-DOODLE_WIDTH) && (x<JetPack[1].x+JETPACK_WIDTH) && (y>JetPack[1].y-DOODLE_HEIGHT) && (y<JetPack[1].y+JETPACK_HEIGHT) && JetPack[1].x!=0 && JetPack[1].y!=0)
    {
        isFlight=true;
        jet.play();
        sPers.setTexture(t11);
        dy =-30;
        scoreplus = counter;
    }
    
    if ((counter-scoreplus)>650 && isFlight==true)
    {
        isFlight=false;
        sPers.setTexture(t3);
        
    }
    for (int i=0;i<12;i++)
    {
        if ((x+60>FakePlat[i].x) && (x+30<FakePlat[i].x+FAKE_WIDTH) && (y+78>FakePlat[i].y) && (y+78<FakePlat[i].y+FAKE_HEIGHT) && (dy>0))
        {
            
            BrokenPlat[i].x=FakePlat[i].x;
            BrokenPlat[i].y=FakePlat[i].y;
        }
    }
    // doodle 90x88   plate 128x46 monster
    int  i=1;
    
    if ((x>monster[i].x-DOODLE_WIDTH) && (x<monster[i].x+MONSTER_WIDTH) && (y>monster[i].y-DOODLE_HEIGHT) && (y<monster[i].y+MONSTER_HEIGHT) && isMonsterDrawn == true && isFlight==false)
    {
        monsterhit.play();
        game.close();
        
        gameover(counter);
        
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
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        x+=4;
        if (isFlight==false)
        {
        sPers.setTexture(t6);
        }
        
    }
    if (Keyboard::isKeyPressed(Keyboard::Space))
    {
        isShoot=true;
        
    }
    
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        x-=4;
        if (isFlight==false)
        {
        sPers.setTexture(t3);
        }
    }
    
    dy+=0.2;
   
        y+=dy;
    
   
    if (y>YRANGE_GEN) dy=-10;
    
    if (y<h)
    {
        reRender();
    }
    
    checktouch();
   
    if (y>YRANGE_GEN && counter>45)
    {
        death.play();
        game.close();
        gameover(counter);
    }
    
    
   
    drawing();
  
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
