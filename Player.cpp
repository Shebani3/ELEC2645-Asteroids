#include "Player.h"


Player::Player() {}

void Player::initialise() {
    //printf("Ball: Init\n");
    _size = 4;
    _xc = 42;
    _yc = 24;
    _speed = 2;
   
    _x1 = 42;
_y1 = 24;
    _x2 = 42;
    _y2 = 24;
   _x0 = 42;
    _y0 = 24;
}

void Player::drawPlayer(N5110 &lcd) {
    lcd.drawCircle(_x1, _y1, 2, FILL_TRANSPARENT); 
       lcd.drawLine(_x1,_y1,_x0,_y0,1);
       lcd.drawLine(_x0,_y0,_x2,_y2,1);
       lcd.drawLine(_x1,_y1,_x2,_y2,1);
       lcd.refresh();

    
}

float Player::rad(float angle)
{
 float R;
 R = (angle*3.14f)/180;
 return R  ;
};


    void Player::pos_update(float angle,  bool thrust, Direction d){
    if((int)angle!= -1){
              
    //move_angle();
     _x0=_xc+(4*cos(rad((int)angle)));//----------
    _y0=_yc+(4*sin(rad((int)angle)));

    _x1=_xc+(4*cos(rad((int)angle+120)));
    _y1=_yc+(4*sin(rad((int)angle+120)));
   
    _x2=_xc+(4*cos(rad((int)angle+230)));
    _y2=_yc+(4*sin(rad((int)angle+230)));
    if (!thrust){
    move_angle(d);}
   }};

void Player::set_xc(int xc){
    _xc=xc;
};
void Player::set_yc(int yc){
    _yc=yc;
};

void Player::move_angle(Direction d ){
  
    if (d==SE){
 (_xc)-=_speed;
 (_yc)-=_speed;
} else   if (d==SW){
 (_xc)+=_speed;
 (_yc)-=_speed;
 } else if (d==NE){
 (_xc)-=_speed;
 (_yc)+=_speed;
  }else if (d==NW){
 (_xc)+=_speed;
 (_yc)+=_speed;
 }else if(d==N){
 (_yc)+=_speed;
 }else if(d==S){
 (_yc)-=_speed;   
 }else if(d==E){
 (_xc)-=_speed;
 }else if(d==W){
 (_xc)+=_speed;
 }
  };

int Player::get_x1(){
return _x1;
}
int Player::get_y1(){
return _y1;
}

void Player::wrapped_coord(){
    if (_xc >84){
        _xc = 0;
    }if (_yc < 0){
        _yc = 48;
    }if (_xc<0){
        _xc = 84;
    }if (_yc>48){
        _yc = 0;
    }

}