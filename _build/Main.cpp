#include <raylib-cpp.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "Background.h"
#include "Shield.h"
#include "Spaceship.h"
#include "Alien.h"
#include <string.h>
#include <fstream>
#include "buttons.h"
#include "AudioStream.hpp"
#include "AudioDevice.hpp"
#include <stdlib.h>




const int screenWidth = 800;
const int screenHeight = 800;

const int ALIENS_PER_ROW = 11;
const int ALIENS_PER_COL = 5;
const int TOTAL_ALIENS = ALIENS_PER_COL * ALIENS_PER_ROW;
const int TOTAL_SHIELDS = 4;
const int TOTAL_ENTITIES = 2 + TOTAL_ALIENS + TOTAL_SHIELDS;
int totalscore = 0;
int levels = 1;




enum States {
    PlayState,
    GameOver,
    PauseState,
    WinState,
    levelup




};
  int  state = PlayState;
enum EntityIDs {
    PLAYER,
    SHIELD_1,
    SHIELD_2,
    SHIELD_3,
    SHIELD_4,
    SPACESHIP
};
enum TextureIds {

    SHIPS_TEX,
    PROJECTILE_TEX,
    MISC_TEX
};
void ChangeEntityTexture(int enttype, int num, Entity** ent)
{
    if (enttype == 1)
    {
        ent[PLAYER]->changetext(num);
    }

}
int loadHighscore() {

    int highscore = 0;
    std::ifstream scoreReader;
    scoreReader.open("hsc.txt");
    if (!scoreReader.fail() && scoreReader.good())
        scoreReader >> highscore;
    return highscore;


}
int Highscore = loadHighscore();
void CreateEntites(Entity** ents, raylib::Texture2D* textures) {
    raylib::Rectangle inclip(8, 0, 8, 8);
    raylib::Rectangle outclip(400, 800 - 64, 32, 32);
    int ship_speed = 10;
    float size_of_ship = 40;


    ents[PLAYER] = new Player(&textures[SHIPS_TEX], raylib::Rectangle(8, 0, 8, 8), raylib::Rectangle(screenWidth / 2, screenHeight - 64, size_of_ship, size_of_ship), screenWidth, screenHeight, levels,ship_speed, &textures[PROJECTILE_TEX]);
    ((Player*)ents[PLAYER])->SetThrottle(&textures[MISC_TEX], raylib::Rectangle(48, 8, 8, 8));
    for (int i = 0; i < ALIENS_PER_ROW; i++)
    {
        for (int j = 0; j < ALIENS_PER_COL; j++)
        {
           
            ents[SPACESHIP + 1 + i + (j * ALIENS_PER_ROW)] = new Alien(&textures[SHIPS_TEX],
                raylib::Rectangle(32 + (j * 8), 16, 8, 8),
                raylib::Rectangle(i * (GetScreenWidth() / ALIENS_PER_ROW), (j * (GetScreenHeight() / 3 / ALIENS_PER_COL)) + 50, 32, 32),
                /*speed*/12.0f,
                /*offset*/50.0f,
                /*initial delay*/0.05f * (i + (j * ALIENS_PER_ROW)),
                /*delay*/0.5f,
                &textures[PROJECTILE_TEX],levels);

        }
    }

    Shield* shields[TOTAL_SHIELDS];
    int shieldspacing = (GetScreenWidth() / (TOTAL_SHIELDS + 1));
    for (int i = 0; i <= SHIELD_4 - SHIELD_1; i++)
    {
        ents[i + SHIELD_1] = new Shield(&textures[MISC_TEX], raylib::Rectangle(88, 32, 16, 16), raylib::Rectangle(shieldspacing + (i * shieldspacing) - 32, GetScreenHeight() - 160, 64, 64),levels);
    }

    ents[SPACESHIP] = new Spaceship(&textures[SHIPS_TEX], raylib::Rectangle(48, 64, 16, 16), raylib::Rectangle(-64, 16, 64, 64), 300.0f,levels);


}

int getCollisions(Entity** e, int i) {
    int score = 0;
    if (i != PLAYER&&!(i >= SHIELD_1 && i <= SHIELD_4) )
        score += ((Player*)e[PLAYER])->getCollisions(e[i]);

    if (i == PLAYER || (i >= SHIELD_1 && i <= SHIELD_4))
        for (int a = SPACESHIP + 1; a < (TOTAL_ENTITIES); a++)
            ((Alien*)e[a])->getCollisions(e[i]);
    return score;
}


void SaveHighscore(int& score, int& highscore) {
    if (score > highscore)
    {

        highscore = score;
        std::ofstream scorewriter;
        scorewriter.open("hsc.txt");
        scorewriter << highscore;
        scorewriter.close();

    }


}

 int stateOfGame(int stat,raylib::Window& window,Entity** ents,raylib::Texture* textures, Background &gamebackground,int &totalscore,int &higscore) {
    switch (state) {


    case PlayState:
    {
       
        if (Alien::getcount() <= 0 && (levels == 2))
        {
            state = WinState;
        }

        if (IsKeyPressed(KEY_P))
            state = PauseState;
        BeginDrawing();
        ClearBackground(BLACK);
        gamebackground.drawbackground();
        gamebackground.updatebackground(0);
        if (Alien::getcount() <= 0) {
      
            Alien::resetcount();
            SaveHighscore(totalscore, higscore);
            totalscore = 0;
            if (levels == 1)
                state = levelup;
            else
                state = WinState;
        
        }
        if (!ents[PLAYER]->enabled) {
        
            state = GameOver;
        }

        ents[PLAYER]->Event();
        for (int i = 0; i < TOTAL_ENTITIES; i++)
        {
            ents[i]->Update();
            totalscore += getCollisions(ents, i) / 10;
        }

        SaveHighscore(totalscore, Highscore);

        for (int i = 0; i < TOTAL_ENTITIES; i++)
        {
            if (i == SPACESHIP)
                continue;
            ents[i]->draw();

        }
        std::string scorest = std::to_string(totalscore);
        DrawText(scorest, 8, 8, 28, raylib::WHITE);
        std::string highstr = std::to_string(Highscore);
        DrawText(highstr, GetScreenWidth() - 100, 8, 28, raylib::WHITE);
        EndDrawing();


        break;
    }
    case GameOver:
    {
        if (IsKeyPressed(KEY_N)) {           // This applies when the user chooses restart the game.
            levels = 1;
        
            for (int i = 0; i < TOTAL_ENTITIES; i++) {
                 
                delete ents[i];
            }
            levels = 1;
            CreateEntites(ents, textures);
            state = PlayState;
        
        }
        if (IsKeyPressed(KEY_P)) {
        
            return 0;
        
        }
        BeginDrawing();
        ClearBackground(BLACK);
        gamebackground.drawbackground();
        gamebackground.updatebackground(0);

        DrawText("The Game is over\nYou have lost the battle\nPress N to to Restart the Game or P\n for leaving .", GetScreenWidth() - 800, 50, 28, raylib::WHITE);
        EndDrawing();
        break;
    }
    case PauseState:
    {
        if (IsKeyPressed(KEY_P))
            state = PlayState;
            BeginDrawing();
        ClearBackground(BLACK);
        gamebackground.drawbackground();
        SaveHighscore(totalscore, Highscore);
        for (int i = 0; i < TOTAL_ENTITIES; i++)
            ents[i]->draw();
        std::string scorest = std::to_string(totalscore);
        DrawText(scorest, 8, 8, 28, raylib::WHITE);
        DrawText("The Game is Paused Press P to continue the game", GetScreenWidth() - 800, 50, 28, raylib::WHITE);
        EndDrawing();
        break;
    }
    case WinState:
    {
        
        if (IsKeyPressed(KEY_N)) {           // This applies when the user chooses restart the game.

            for (int i = 0; i < TOTAL_ENTITIES; i++) {

                delete ents[i];
            }
            levels = 1;
            CreateEntites(ents, textures);
            state = PlayState;

        }
        if (IsKeyPressed(KEY_P)) {

            return 0;
        }
        

        BeginDrawing();
        ClearBackground(BLACK);
        
        gamebackground.drawbackground();
        gamebackground.updatebackground(0);
        DrawText("You WOn!\nPress N for Restarting the\n Game and press p for\n ending the game\n", GetScreenWidth() - 800, 200, 50, raylib::WHITE);
        EndDrawing();
        break;
    }

    case levelup:
    {
        levels++;
       BeginDrawing();
        ClearBackground(BLACK);

        gamebackground.drawbackground();
        gamebackground.updatebackground(0);
        DrawText("Level-2", GetScreenWidth()/2, 200, 50, raylib::WHITE);
        EndDrawing();
         WaitTime(2.50);

            for (int i = 0; i < TOTAL_ENTITIES; i++) {

                delete ents[i];
            }
            CreateEntites(ents, textures);
            state = PlayState;

        }


    }






   
 }

 void button_coordinates_setter(buttons& b1, buttons& b2, buttons& b3, buttons& b4, buttons& b5, buttons& b6, buttons& b7)
 {
     b1.button_coordinates_setter(275, 340);
     b2.button_coordinates_setter(275, 460);
     b3.button_coordinates_setter(275, 580);
     b4.button_coordinates_setter(275, 700);
     b5.button_coordinates_setter(275, 240);
     b6.button_coordinates_setter(275, 360);
     b7.button_coordinates_setter(275, 480);
 }





 

int main() {

    //buttons continue;
    buttons new_game;
    buttons leaderboard;
    buttons accessories;
    buttons exit;
    buttons ship1;
    buttons ship2;
    buttons ship3;


    button_coordinates_setter(new_game, leaderboard, accessories, exit, ship1, ship2, ship3);

    std::string high = std::to_string(Highscore);

    char highscore[5];
    for (int i = 0; i < high.length(); i++)
        highscore[i] = high[i];

    Vector2 mouse = GetMousePosition();

    InitWindow(screenWidth, screenHeight, "Adaptive Space Background");
    SetTargetFPS(60);
    raylib::Window window(screenWidth, screenHeight, "Adaptive Space Background");

    Background gamebackground(screenWidth, screenHeight, 1000);
    Background gb(screenWidth, screenHeight, 1000);

    raylib::Texture2D texture[] = { ("spaceship.png"),("bullet.png"),("shield.png") };
    Entity* ents[TOTAL_ENTITIES];
    CreateEntites(ents, texture);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        gamebackground.drawbackground();
        gamebackground.updatebackground(1);

        DrawText("Guardians of the \n\t\t\t  Space", 50, 50, 80, WHITE);

        new_game.updateButtonState(mouse);
        leaderboard.updateButtonState(mouse);
        accessories.updateButtonState(mouse);
        exit.updateButtonState(mouse);

        if (new_game.Update())
        {
            {
                while (!WindowShouldClose()) {
                    int x = stateOfGame(state, window, ents, texture, gamebackground, totalscore, Highscore);/// Game is running here;
                    if (x == 0)
                        break;
                }
            }
        }

        if (exit.Update())
        {
            return 0;
        }

        if (leaderboard.Update())
        {
            while (!WindowShouldClose() && !IsKeyPressed(KEY_SPACE)) {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Highscore", 160, 240, 110, WHITE);
                DrawText(high.c_str(), 270, 470, 100, WHITE);
                EndDrawing();
            }
        }

        if (accessories.Update())
        {
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);
                gamebackground.drawbackground();
                gamebackground.updatebackground(1);
                ship1.updateButtonState(mouse);
                ship1.Draw(6);
                ship2.updateButtonState(mouse);
                ship2.Draw(7);
                ship3.updateButtonState(mouse);
                ship3.Draw(8);


                if (ship1.Update())
                {
                    ChangeEntityTexture(1, 1, ents);
                }
                else if (ship2.Update())
                {
                    ChangeEntityTexture(1, 2, ents);
                }
                else if (ship3.Update())
                {
                    ChangeEntityTexture(1, 3, ents);
                }
                EndDrawing();
            }
        }

        new_game.Draw(0);
        leaderboard.Draw(1);
        accessories.Draw(2);
        exit.Draw(3);

        EndDrawing();
    }
}

    

