

#ifndef PLAYER_H
#define PLAYER_H

#include "mbed.h"
#include "N5110.h"

#include <cstdio>
#include <cmath>
#include "Joystick.h" 
class Player{
public:

Player();
void initialise();
void pos_update(float angle,  bool thrust,Direction d);
void drawPlayer(N5110 &lcd);

void set_xc(int xc);
void set_yc(int yc);

int get_x1();
int get_y1();

int _xc,_yc;
void wrapped_coord();

private:
int _x0,_y0,_x1,_y1,_x2,_y2,_speed,_size;
void move_angle(Direction d);
float rad(float angle);
};

/*{
 float R;
 R = (angle*3.14f)/180;
 return R  ;
}*/
#endif

/*class Player{
    public:
    int x0,y0,x1,y1,x2,y2,xc,yc;
   // int x0,int ,int y0,int x1,int y1, int x2, int y2, int xc, int yc)
    void pos_update(){
   
    if((int)joystick.get_angle() != -1){
              
        // fire2(this->x1,this->y1,this->xc,this->yc);}
        
    //this->xc++;}
    //move_angle( &xc,&yc);
     this->x0=this->xc+(4*cos(rad((int)joystick.get_angle())));//----------
     this->y0=this->yc+(4*sin(rad((int)joystick.get_angle())));
     //printf(" (%i) ",(int)joystick.get_angle());
     //printf(" %i ",buttonA.read());
     //printf("%i ",g_buttonA_flag);
    this->x1=this->xc+(4*cos(rad((int)joystick.get_angle()+120)));
    this->y1=this->yc+(4*sin(rad((int)joystick.get_angle()+120)));
   
    x2=xc+(4*cos(rad((int)joystick.get_angle()+230)));
    y2=yc+(4*sin(rad((int)joystick.get_angle()+230)));
    move_angle( &xc,&yc);
   }}
    
   void draw(){
     lcd.drawCircle(x1, y1, 2, FILL_TRANSPARENT); 
       lcd.drawLine(x1,y1,x0,y0,1);
       lcd.drawLine(x0,y0,x2,y2,1);
       lcd.drawLine(x1,y1,x2,y2,1);
       lcd.refresh();
    }


};*/