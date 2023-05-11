#include "GameEngine.h"

GameEngine::GameEngine(){  }    


    //printf("Game Engine: Init\n");
   //void GameEngine::init(int a1, int b1, int c ,int d1,int d2,int n,int a2,int a2,int n){
    void GameEngine::init(int a1, int a2, int b1 ,int b2,int c,int d1,int d2,int c2, int size1,int size2){
   
    
     P1.initialise();

     Asteroid[0].init(a1,b1,c,c,size1);
     Asteroid[1].init(a2,b2,c2,c2,size2);
     //printf(" 1111111111111111111 ");
  //   Asteroid[0].init(a,b,c,c,12);
    //Asteroid[1].init(70,5,c,c,8);

    } 

    void GameEngine::draw_objs(N5110 &lcd){

        Asteroid[0].drawit(lcd);
        Asteroid[1].drawit(lcd);
        P1.drawPlayer(lcd); 
    }
    //, int a, int b,int c, int d1, int d2,int n
  void GameEngine::update(float angle, bool buttonA,  Direction d,int d1,int d2){
 P1.pos_update(angle,  buttonA,  d); // change the way the arguments are
    Asteroid[1].updateAst(d1);
    Asteroid[0].updateAst(d2);
    Asteroid[0].wrapped_coord(); 
   Asteroid[1].wrapped_coord(); 
   P1.wrapped_coord();
    }

    void GameEngine::collision_ast_player(int *l){

        for (int i =0; i<2; i++){
    int a= pow((((Asteroid[i]).get_x())-(P1._xc)),2)+pow((((Asteroid[i]).get_y())-(P1._yc)),2);
    int dist = sqrt(a);
    if ((dist)<=(Asteroid[i]).get_size()){
        printf(" COLLIDE!!! ");
         (*l)=0;
       break;
    }
    }
    }

 void GameEngine::bullet_update(){
     if (Bulletvec.size()>0){
        for(int i=0;i<Bulletvec.size();i++){
        if((Bulletvec[i]._bx<84) & (Bulletvec[i]._bx>0) & (Bulletvec[i]._by>0)& (Bulletvec[i]._by<48)){
      Bulletvec[i].pos_update();
      if(Bulletvec[i].collision(Asteroid[0])){
          Asteroid[0]._size-=2;
           Bulletvec.erase(Bulletvec.begin());
      }
       if(Bulletvec[i].collision(Asteroid[1])){
          Asteroid[1]._size-=2;
           Bulletvec.erase(Bulletvec.begin());
      }}
      else{
          Bulletvec.erase(Bulletvec.begin());}
    }}
    }

     void GameEngine::fire(Direction d){
        Bullet b1(P1.get_x1(),P1.get_y1(),7,d);
        Bulletvec.push_back(b1);
     }
