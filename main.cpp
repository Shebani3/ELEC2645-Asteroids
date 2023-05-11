
 /*  N5110_LCD_Test
*    ===============
*
*    Function:               Basic functionality test of the Nokia N5110 LCD display and N5110.h
*    Circuit Schematic No.:  9     : https://github.com/ELECXJEL2645/Circuit_Schematics
*    Required Libraries:     N5110 : https://github.com/ELECXJEL2645/N5110
*
*    Authored by:            Andrew Knowles
*    Date:                   2021
*    Collaberators:          Dr Craig Evans
*                            Dr Alexander Valavanis
*                            Dr Tim Amsdon
*    Version:                2.0
*    Revision Date:          06/2022 
*    MBED Studio Version:    1.4.1
*    MBED OS Version:        6.14.0
*    Board:	                 NUCLEO L476RG  */

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h" 
#include "Player.h" //utils header file is the issue 
#include <cstdio>
#include <vector>
//#include <cstdio>
//#include <cmath>
#include "Bullet.h"
#include <stdlib.h> 
#include <ctime> 
#include "SpaceObject.h"
#include "GameEngine.h"
#include <ctime>

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_3, PC_2);
InterruptIn joystick_button(PC_10);
DigitalIn buttonA(PC_8);
DigitalIn buttonB(BUTTON1); 
void contrastTest();
void brightnessTest();
void collision(vector<SpaceObject>& Asteroid,Player P,int *a);
void game_over();
void joystick_button_isr();
void fire();
void welcome();
bool Win_case(SpaceObject s1);
int win=0;
int status=0;
 volatile int g_buttonA_flag = 0;

char buffer[14] = {0};
int fps = 100;

GameEngine game;


int main(){
  
    int lives = 1; 
    joystick.init();       //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    Vector2D coord = joystick.get_mapped_coord();
    joystick_button.fall(&joystick_button_isr);
    joystick_button.mode(PullUp);
    welcome();
           // Get the current clock time before the code block starts
    clock_t start_clock = clock();
     GameEngine game;
	Direction d;
  
  srand(time(0));
    int x1 = rand()%10+2;
    int x2 = rand()%10+2;
    int y1 = rand()%80+1;
    int y2 = rand()%80+1;
    int speed1 = rand()%3+1;// 0-3(inc)
    int d1 = rand()%8; //random number between 0 and 7
    int d2 = rand()%8; //random number between 0 and 7
    int size1 = rand()%8+4; 
    int size2 = rand()%8+4; 
    int speed2 = rand()%4+1;// 0-3(inc)

   SpaceObject A1;
   
    for (int i = 0; i < 2; i++) {
       game.Asteroid.push_back(A1);   //chagne pack to sateroid
    }
    //Player P1;
    // P1.initialise();
     game.init(x1,x2,y1,y2,speed1,d1,d2,speed2,size1,size2);
  //  lcd.clear();
    //printTest();

  //  lcd.refresh();
       
//game.Asteroid[0].init(a,b,c,c,12);
//game.Asteroid[1].init(70,5,c,c,8);

   while(lives>0&win==0){
    

    lcd.clear();  
    d= joystick.get_direction();
    game.draw_objs(lcd);
    lcd.refresh();

    if(g_buttonA_flag){
    g_buttonA_flag=0;
    game.fire(d);
    }

   //printf(" items %i ",game.Bulletvec.size());
   game.update(joystick.get_angle(),  buttonA.read(),  d,d1,d2);
   game.bullet_update();
    
 for(int i=0;i<game.Bulletvec.size();i++){
    game.Bulletvec[i].drawit(lcd);}
    thread_sleep_for(100);
    game.collision_ast_player(&lives);

    if(Win_case(game.Asteroid[0])&&Win_case(game.Asteroid[1])){
      win=1;
     }
    }
    
   clock_t end_clock = clock();

    // Calculate the time difference
    double duration = (double)(end_clock - start_clock) / CLOCKS_PER_SEC * 1000000;

    printf("Time taken: %f microseconds\n", duration);
   if (win==1){
       printf("won");
   }else{
    game_over();}
}

 void game_over() { // splash screen 
    //while (1) {
        lcd.clear();
        lcd.printString("  Game Over ",0,2);  
        lcd.refresh();
        ThisThread::sleep_for(250ms);
        lcd.clear();
        lcd.refresh();
        ThisThread::sleep_for(250ms);
    //}
}
void joystick_button_isr(){
  g_buttonA_flag = 1;  
}

void welcome() { // splash screen
    lcd.printString("   Asteroids",0,1);  
    lcd.printString(" Nucleo-button",0,3);
    lcd.printString("!! BE QUICK !!",0,4);
    lcd.refresh();

        while (buttonB.read() == 1){

         ThisThread::sleep_for(100ms);
      
        }
}
bool Win_case(SpaceObject s1) {
if(s1.get_size()<=2){return true;}else{return false;}
}