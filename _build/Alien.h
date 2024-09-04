#ifndef _ALIEN
#define _ALIEN
#include "Entity.h"
#include "Bullet.h"
class Alien :public Entity
{
public:
	Alien(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, float speed, float offset, float initialDelay, float delay, raylib::Texture* textureforbullets,int level);
	~Alien();
	void draw();
	void Update();
	void Alien::getCollisions(Entity* e);
	void static setSpeed(float v);
	int static getcount();
	void static resetcount();
	int Recieve(int);
private:
	static float speed_increment;
	float speed;
	Bullet* bullet;

	float shootingTimer;

	float initial;
	float offset;

	float moveTimer;
	float moveDelay;

	float towardsBottom;
	static int count;



};
#endif

