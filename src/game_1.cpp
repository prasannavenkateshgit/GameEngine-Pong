// This is the game entities for Srivathsan Govindarajan's game
#include "game.hpp"

#define SPEED 11
#define SIZE 16
#define BALL_SPEED 15
#define PI 3.14159265358979323846

bool running;
int frameCount, timerFPS, lastFrame, fps;

SDL_Rect l_paddle, r_paddle, ball, score_board;
float velX, velY;
std::string score;
int l_s, r_s;
bool turn;
bool single=false;

std::string selfID;
ReplayEvent* replay_event;
PlaybackEvent* playback_event;
GameObjects* loadEntities(std::string clientID, Color color)
{
    global_time = new Timeline();
    physics = new Physics(0);
    selfID = clientID;
    GameObjects* game_objects = new GameObjects();
    game_objects->addEntity("0", new Rect(32, (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/8), 12, SCREEN_HEIGHT/4, true, Color{255,255,255}, false));
    game_objects->addEntity("1", new Rect(SCREEN_WIDTH-48, (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/8), 12, SCREEN_HEIGHT/4, true, Color{255,255,255}, false));
    game_objects->addEntity("ball", new Rect(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 16.0, 16.0, true, {255, 255, 255}, false));
    // if (selfID == "0"){
    //     //game_objects->addEntity(selfID, new Rect(0, SCREEN_HEIGHT * 0.7 - 50 , 20, 60, true, {255, 255, 255}, false));
    //     game_objects->addEntity(selfID, new Rect(32, (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/8), 12, SCREEN_HEIGHT/4, true, Color{255,255,255}, false));
    //     //game_objects->addEntity("ball", new Rect(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 16, 16, true, Color{255, 255, 255}, false));
    // }
    // else{
    //     game_objects->addEntity(selfID, new Rect(SCREEN_WIDTH-48, (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/8), 12, SCREEN_HEIGHT/4, true, Color{255,255,255}, false));
    // }
    input_event = new InputEvent(moveEntity, game_objects, global_time->getTime(), EventPriority::HIGH);
    input_event->setType("Input");
    event_manager.registerEvent(input_event);
    // replay_event = new ReplayEvent(std::string("game_1"), global_time->getTime(), EventPriority::LOW);
    // replay_event->setType("replay");
    // event_manager.registerEvent(replay_event);
    // playback_event = new PlaybackEvent(std::string("game_1"), global_time->getTime(), EventPriority::HIGH);
    // playback_event->setType("playback");
    // event_manager.registerEvent(playback_event);
    return game_objects;
}

void moveEntity(GameObjects* game_objects, Uint8 *keys)
{
    
    float vel_y1 = 0.0;
    float vel_y2 = 0.0;
    if (keys[SDL_SCANCODE_W])
    {
        //vel_y1 = global_time->getTic()? -200.0 / global_time->getTic() : 0;
        vel_y1 = -30;
        game_objects->getEntity("0")->setY(game_objects->getEntity("0")->getY() + vel_y1);
    }
    if (keys[SDL_SCANCODE_S])
    {
        //vel_y1 = global_time->getTic()? 200.0 / global_time->getTic() : 0;
        vel_y1 = 30;
        game_objects->getEntity("0")->setY(game_objects->getEntity("0")->getY() + vel_y1);
    }
    if (keys[SDL_SCANCODE_UP])
    {
        vel_y2 = -30;
        game_objects->getEntity("1")->setY(game_objects->getEntity("1")->getY() + vel_y2);
    }
    if (keys[SDL_SCANCODE_DOWN])
    {
        vel_y2 = 30;
        game_objects->getEntity("1")->setY(game_objects->getEntity("1")->getY() + vel_y2);
    }
    if (keys[SDL_SCANCODE_SPACE])
    {
        single = !single;
    }
    // if(selfID == "0")
    // {
    //     game_objects->setEntityVelocityY(selfID, vel_y1);
    // }
    // if(selfID != "0")
    // {
    //     game_objects->setEntityVelocityY(selfID, vel_y2);
    // }
    // if(vel_y1)
    // {
    //     //game_objects->setEntityVelocityY("0", vel_y1);
    //     game_objects->getEntity("0")->setY(game_objects->getEntity("0")->getY() + vel_y1);
    // }
    // if(vel_y2)
    // {
    //     //game_objects->setEntityVelocityY("1", vel_y2);
    //     game_objects->getEntity("1")->setY(game_objects->getEntity("1")->getY() + vel_y1);
    // }

    // if (keys[SDL_SCANCODE_T])
    // {
    //     isProportional = !isProportional;
    //     if(isProportional)
    //     {
    //         std::cout<<"Object sizes are set to proportional"<<std::endl;
    //     }
    //     else
    //     {
    //         std::cout<<"Object sizes are set to constant"<<std::endl;
    //     }
    // }
    // if (keys[SDL_SCANCODE_R])
    // {
    //     std::cout<<"RECORDING"<<std::endl;
    //     event_manager.raiseEvent(replay_event);
    //     // recording = !recording;
    // }
    // if (keys[SDL_SCANCODE_Y])
    // {
    //     std::cout<<"PLAYBACK"<<std::endl;
    //     event_manager.raiseEvent(playback_event);
    //     // playback = !playback;
    // }
    // if(keys[SDL_SCANCODE_KP_PLUS])
    // {
    //     float tic = global_time->getTic();
    //     global_time->changeTic(tic + 0.1);
    //     std::cout<<"Tic set to "<<global_time->getTic()<<std::endl;
    // }
    // else if(keys[SDL_SCANCODE_KP_MINUS])
    // {
    //     float tic = global_time->getTic();
    //     global_time->changeTic(tic - 0.1);
    //     std::cout<<"Tic set to "<<global_time->getTic()<<std::endl;
    // }
    if(keys[SDL_SCANCODE_P])
    {
        if(global_time->isPaused())
        {
            global_time->unpause();
            std::cout<<"Game Unpaused"<<std::endl;
        }
        else{
            global_time->pause();
            std::cout<<"Game Paused"<<std::endl;
        }
    }
    // float vel_x = 0.0, vel_y = 0.0;
    // if(keys[SDL_SCANCODE_RIGHT])
    // {
    //     if(keys[SDL_SCANCODE_LSHIFT])
    //     {
    //         vel_x = global_time->getTic()? 20.0 / global_time->getTic() : 0;
    //     }
    //     else
    //     {
    //         vel_x = global_time->getTic()? 10.0 / global_time->getTic() : 0;
    //     }
    // }
    // else if(keys[SDL_SCANCODE_LEFT])
    // {
    //     if(keys[SDL_SCANCODE_LSHIFT])
    //     {
    //         vel_x = global_time->getTic()? -20.0 / global_time->getTic() : 0;
    //     }
    //     else
    //     {
    //         vel_x = global_time->getTic()? -10.0 / global_time->getTic() : 0;
    //     }
    // }
    // if (keys[SDL_SCANCODE_SPACE])
    // {
    //     vel_y = global_time->getTic()? -10.0 / global_time->getTic() : 0;
    // }
    // game_objects->setEntityVelocityX(selfID, vel_x);
    // if(vel_y)
    // {
    //     game_objects->setEntityVelocityY(selfID, vel_y);
    // }
}

void serve(GameObjects& game_objects) {
 l_paddle.w=12;
 l_paddle.h=SCREEN_HEIGHT/4;
 r_paddle.w=12;
 ball.w=ball.h=SIZE;
 r_paddle.h=SCREEN_HEIGHT/4;
 l_paddle.x=32;
 l_paddle.y=(SCREEN_HEIGHT/2)-(l_paddle.h/2);
 r_paddle.y=l_paddle.y;
 r_paddle.x=SCREEN_WIDTH-r_paddle.w-32;
 if(turn) {
  ball.x=l_paddle.x+(l_paddle.w*4);
  velX=BALL_SPEED/2;
 } else {
  ball.x=r_paddle.x-(r_paddle.w*4);
  velX=-BALL_SPEED/2;
 }
 ball.y=SCREEN_HEIGHT/2;
 velY=0;
 turn=!turn;
 game_objects.getEntity("ball")->setX(ball.x);
 game_objects.getEntity("ball")->setY(ball.y);
 game_objects.getEntity("ball")->setVelocityX(velX);
 game_objects.getEntity("ball")->setVelocityY(velY);
 game_objects.getEntity("0")->setX(l_paddle.x);
 game_objects.getEntity("0")->setY(l_paddle.y);
 game_objects.getEntity("0")->setW(l_paddle.w);
 game_objects.getEntity("0")->setH(l_paddle.h);
 game_objects.getEntity("1")->setX(r_paddle.x);
 game_objects.getEntity("1")->setY(r_paddle.y);
 game_objects.getEntity("1")->setW(r_paddle.w);
 game_objects.getEntity("1")->setH(r_paddle.h);
}

void update(GameObjects& game_objects) {
    l_paddle.x = game_objects.getEntity("0")->getX();
    l_paddle.y = game_objects.getEntity("0")->getY();
    l_paddle.w = game_objects.getEntity("0")->getW();
    l_paddle.h = game_objects.getEntity("0")->getH();
    r_paddle.x = game_objects.getEntity("1")->getX();
    r_paddle.y = game_objects.getEntity("1")->getY();
    r_paddle.w = game_objects.getEntity("1")->getW();
    r_paddle.h = game_objects.getEntity("1")->getH();
    ball.x = game_objects.getEntity("ball")->getX();
    ball.y = game_objects.getEntity("ball")->getY();
    ball.w = game_objects.getEntity("ball")->getW();
    ball.h = game_objects.getEntity("ball")->getH();
    float velX = game_objects.getEntity("ball")->getVelocityX();
    float velY = game_objects.getEntity("ball")->getVelocityY();

 if(SDL_HasIntersection(&ball, &l_paddle)) {
  double in = (l_paddle.y+(l_paddle.h/2))-(ball.y+(ball.h/2));
  double nor = in/(l_paddle.h/2);
  double b = nor * (5*PI/12);
  velX=BALL_SPEED*cos(b);
  velY=BALL_SPEED*-sin(b);
  velX=velX/1.5;
  velY=velY/1.5;
 }
 if(SDL_HasIntersection(&ball, &r_paddle)) {
  double in = (r_paddle.y+(r_paddle.h/2))-(ball.y+(ball.h/2));
  double nor = in/(r_paddle.h/2);
  double b = nor * (5*PI/12);
  velX=-BALL_SPEED*cos(b);
  velY=BALL_SPEED*-sin(b);
  velX=velX/1.5;
  velY=velY/1.5;
 }
 if (single){
    if(ball.y>(r_paddle.y+(r_paddle.h/2))) r_paddle.y+=SPEED;
    if(ball.y<(r_paddle.y+(r_paddle.h/2))) r_paddle.y-=SPEED;
 }
 if(game_objects.getEntity("ball")->getX()<=0) {
    r_s++;
    //cout<<"Right scored"<<endl;
    serve(game_objects);
    velX = game_objects.getEntity("ball")->getVelocityX();
    }
 if(game_objects.getEntity("ball")->getX()+game_objects.getEntity("ball")->getW()>=SCREEN_WIDTH) {
    l_s++;
    //cout<<"Left scored"<<endl;
    serve(game_objects);
    velX = game_objects.getEntity("ball")->getVelocityX();
    }
//  if(ball.x<0) {r_s++;serve(game_objects);}
//  if(ball.x+ball.w>SCREEN_WIDTH) {l_s++;serve(game_objects);}
if(game_objects.getEntity("ball")->getY()<=0 || game_objects.getEntity("ball")->getY()+game_objects.getEntity("ball")->getH()>=SCREEN_HEIGHT){
    velY=-velY;
}
//  if(ball.y<0 || ball.y+ball.h>SCREEN_HEIGHT){
//     cout<<"Flipping Y"<<endl;
//     velY=-velY;
//  }
 ball.x+=velX;
 ball.y+=velY;
 score = std::to_string(l_s) + "   " + std::to_string(r_s);
 if(l_paddle.y<0)l_paddle.y=0;
 if(l_paddle.y+l_paddle.h>SCREEN_HEIGHT)l_paddle.y=SCREEN_HEIGHT-l_paddle.h;
 if(r_paddle.y<0)r_paddle.y=0;
 if(r_paddle.y+r_paddle.h>SCREEN_HEIGHT)r_paddle.y=SCREEN_HEIGHT-r_paddle.h;
 game_objects.getEntity("0")->setX(l_paddle.x);
 game_objects.getEntity("0")->setY(l_paddle.y);
 game_objects.getEntity("1")->setX(r_paddle.x);
 game_objects.getEntity("1")->setY(r_paddle.y);
 game_objects.getEntity("ball")->setX(ball.x);
 game_objects.getEntity("ball")->setY(ball.y);
 game_objects.getEntity("ball")->setVelocityX(velX);
 game_objects.getEntity("ball")->setVelocityY(velY);
 cout<<"Left player score: "<<l_s<<" Right player score: "<<r_s<<endl;
}

// void update(GameObjects& game_objects) {
//     l_paddle.w=12;
//     l_paddle.h=SCREEN_HEIGHT/4;
//     r_paddle.w=12;
//     ball.w=ball.h=SIZE;
//     //l_paddle.x=game_objects->getEntity(selfID)->getX();
//     //l_paddle.y=game_objects->getEntity(selfID)->getY();
//     if(detectCollision(game_objects.getEntity("ball"), game_objects.getEntity("0"))) {
//         double in = (game_objects.getEntity("0")->getY()+(game_objects.getEntity("0")->getH()/2))-(game_objects.getEntity("ball")->getY()+(game_objects.getEntity("ball")->getH()/2));
//         double nor = in/(game_objects.getEntity("0")->getH()/2);
//         double b = nor * (5*PI/12);
//         //game_objects.getEntity("ball")->setVelocityX(BALL_SPEED*cos(b));
//         velX = BALL_SPEED*cos(b);
//         velY = BALL_SPEED*-sin(b);
//         //game_objects.setEntityVelocityX("ball", (BALL_SPEED*cos(b))/2);
//         //game_objects.setEntityVelocityY("ball", (BALL_SPEED*-sin(b))/2);
//         //game_objects.getEntity("ball")->setVelocityY(BALL_SPEED*-sin(b));
//     }
//     if(detectCollision(game_objects.getEntity("ball"), game_objects.getEntity("1"))) {
//         double in = (game_objects.getEntity("1")->getY()+(game_objects.getEntity("1")->getH()/2))-(game_objects.getEntity("ball")->getY()+(game_objects.getEntity("ball")->getH()/2));
//         double nor = in/(game_objects.getEntity("1")->getH()/2);
//         double b = nor * (5*PI/12);
//         velX = -BALL_SPEED*cos(b);
//         velY = BALL_SPEED*-sin(b);
//         //game_objects.getEntity("ball")->setVelocityX(BALL_SPEED*cos(b));
//         //game_objects.setEntityVelocityX("ball", (BALL_SPEED*cos(b))/2);
//         //game_objects.setEntityVelocityY("ball", (BALL_SPEED*-sin(b))/2);
//         //game_objects.getEntity("ball")->setVelocityY(BALL_SPEED*-sin(b));

//  }
//   if(game_objects.getEntity("ball")->getY()>(game_objects.getEntity("1")->getY()+(game_objects.getEntity("1")->getH()/2))) game_objects.getEntity("1")->setY(game_objects.getEntity("1")->getY()+SPEED);
//   if(game_objects.getEntity("ball")->getY()<(game_objects.getEntity("1")->getY()+(game_objects.getEntity("1")->getH()/2))) game_objects.getEntity("1")->setY(game_objects.getEntity("1")->getY()-SPEED);
//  if(game_objects.getEntity("ball")->getX()<0) 
//  {  
//     serve(game_objects);
//  }
//  if(game_objects.getEntity("ball")->getX()+game_objects.getEntity("ball")->getW()>SCREEN_WIDTH) 
//  {
//     //cout<<"CALLING RIGHT SERVE"<<endl;
//     serve(game_objects);
//  }
//  ball.x=game_objects.getEntity("ball")->getX();
//  ball.y=game_objects.getEntity("ball")->getY();
//  velX=game_objects.getEntity("ball")->getVelocityX();
//  velY=game_objects.getEntity("ball")->getVelocityY();
//  if(game_objects.getEntity("ball")->getY()<0 || game_objects.getEntity("ball")->getY()+game_objects.getEntity("ball")->getH()>SCREEN_HEIGHT) {
//     cout<<"Flipping Y velocity"<<endl;
//     velY=-velY;
//  }
//  ball.x+=velX;
//  ball.y+=velY;
//  game_objects.getEntity("ball")->setX(ball.x);
//  game_objects.getEntity("ball")->setY(ball.y);
//  score = std::to_string(l_s) + "   " + std::to_string(r_s);
//  if (game_objects.getEntity("0")->getY() < 0){
//   game_objects.getEntity("0")->setY(0);
//  }
//   if (game_objects.getEntity("1")->getY() < 0){
//   game_objects.getEntity("1")->setY(0);
//  }
//  if (game_objects.getEntity("0")->getY() + game_objects.getEntity("0")->getH() > SCREEN_HEIGHT){
//   game_objects.getEntity("0")->setY(SCREEN_HEIGHT - game_objects.getEntity("0")->getH());
//  }
//  if (game_objects.getEntity("1")->getY() + game_objects.getEntity("1")->getH() > SCREEN_HEIGHT){
//   game_objects.getEntity("1")->setY(SCREEN_HEIGHT - game_objects.getEntity("1")->getH());
//  }
// //  if(l_paddle.y<0)l_paddle.y=0;
// //  if(l_paddle.y+l_paddle.h>SCREEN_HEIGHT)l_paddle.y=SCREEN_HEIGHT-l_paddle.h;
// //  if(r_paddle.y<0)r_paddle.y=0;
// //  if(r_paddle.y+r_paddle.h>SCREEN_HEIGHT)r_paddle.y=SCREEN_HEIGHT-r_paddle.h;
// }


void handleDzone(GameObjects* game_objs)
{
    // Coord spawn_point = {SCREEN_WIDTH * 0.1, SCREEN_HEIGHT * 0.2};
    // SDL_Rect dzone1 = { static_cast<int>(SCREEN_WIDTH * 0.25), static_cast<int>(SCREEN_HEIGHT * 0.7), static_cast<int>(SCREEN_WIDTH * 0.2), static_cast<int>(SCREEN_HEIGHT * 0.3)};
    // SDL_Rect dzone2 = { static_cast<int>(SCREEN_WIDTH * 0.55), static_cast<int>(SCREEN_HEIGHT * 0.7), static_cast<int>(SCREEN_WIDTH * 0.4), static_cast<int>(SCREEN_HEIGHT * 0.3)};
    // SDL_Rect dzone3 = { static_cast<int>(SCREEN_WIDTH * 0.95), static_cast<int>(SCREEN_HEIGHT * 0.7), static_cast<int>(SCREEN_WIDTH * 0.6), static_cast<int>(SCREEN_HEIGHT * 0.3)};
    // Rect* playerE = dynamic_cast<Rect*>(game_objs->getEntity(selfID));

    // DzoneHandler& dzHandler = DzoneHandler::getInstance();
    // dzHandler.addDeathZone(dzone1, spawn_point);
    // dzHandler.addDeathZone(dzone2, spawn_point);
    // dzHandler.addDeathZone(dzone3, spawn_point);
    // dzHandler.startCollisionChecking(playerE);
}