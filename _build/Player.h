#ifndef _PLAYER
#define _PLAYER
#include "Entity.h"
#include "Bullet.h"
class Player :public Entity
{
public:

	Player(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, int w, int h,int level, float speed, raylib::Texture* textureforbullet);
	void Event();
	void Update();
	void draw();
	~Player();
	int getCollisions(Entity* e);
	int Recieve(int);
	void SetThrottle(raylib::Texture2D*, raylib::Rectangle);
private:

	float speed;
	Bullet* bullets;
	int maxbullet;
	int lives;
	raylib::Texture2D* textureForThrottle;
	raylib::Rectangle throttleinclip;
};
#endif
