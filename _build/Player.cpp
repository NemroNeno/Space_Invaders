#include "Player.h"
Player::Player(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip,int w,int h,int level, float spe, raylib::Texture* textureforbullet)
:Entity(texture,inclip,outclip,w,h,level), speed(spe)
{
    maxbullet = 8;
    bullets = new Bullet[8]{
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
    Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10),
   Bullet(textureforbullet,raylib::Rectangle(8,8,8,8),outclip,w,h,level,10)
    };
    lives = 3;
    textureForThrottle = NULL;
    throttleinclip = raylib::Rectangle(0, 0, 0, 0);
}

Player::~Player() {
    delete[] bullets;
}

void Player::Event() {
    if (!enabled)
        return;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        outclip.x -= speed;
        if (outclip.x < 0)
        {
          // throttleinclip = 40;
            outclip.x = 0;
        }
        inclip.x = 0;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        outclip.x += speed;
        if (outclip.x > (screenwidth - 40))
        {
            outclip.x = screenwidth - 40;
           // throttleinclip = 56;
        }
        inclip.x = 16;
    }
    else
        inclip.x = 8;
   // throttleinclip = 48;
    if (IsKeyPressed(KEY_SPACE))
    {
        for (int i = 0; i < maxbullet; i++)
        {
            if (bullets[i].Ishit())
            {
                bullets[i].reset(outclip);
                break;
            }
        }
    
    }
}

void Player::Update() {
    if (!enabled)
        return;
    for (int i = 0; i < maxbullet; i++) {
    
        if (!bullets[i].Ishit())
        {
            bullets[i].update();
        }
    }
    throttleinclip.x = 40 + (((((int)GetTime()*20)) % 4) * 3);

    
}
void Player::draw() {
    if (!enabled)
        return;

    for (int i = 0; i < maxbullet; i++) {

        if (!bullets[i].Ishit())
        {
    
            bullets[i].draw();
        }
    }
    texture->Draw(inclip, outclip);
    outclip.y += 28;
    textureForThrottle->Draw(throttleinclip, outclip);
    outclip.y -= 28;

    for (int i = 0; i < lives; i++)
        texture->Draw(inclip, raylib::Rectangle(8 + (i * (24 + 8)), GetScreenHeight() - 24 - 8, 24, 24));
}

int Player::getCollisions(Entity* e) {
    int totalscore = 0;
    for (int i = 0; i < maxbullet; i++) {

        if (!bullets[i].Ishit()&&bullets[i].iscolliding(e))
        {
            bullets[i].CollisionHit();
         totalscore+=e->Recieve(Damage);
        }
    }

    return totalscore;

}


int Player::Recieve(int i) {

    switch (i) {

    case Damage:

        lives--;
        if (lives <= 0)
            enabled = false;
        break;

    }
    return 0;

}

void Player::SetThrottle(raylib::Texture2D* texture, raylib::Rectangle inclip) {

    textureForThrottle = texture;
    throttleinclip = inclip;

}