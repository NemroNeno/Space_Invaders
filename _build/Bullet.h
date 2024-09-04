#ifndef _BULLET
#define _BULLET
#include "Entity.h"
class Bullet :public Entity
{
public:
	Bullet(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, int w, int h,int level, int spe);
	bool Ishit();
	bool hit;
	void reset(raylib::Rectangle pos);
	void update();
	void Update();
	void CollisionHit();

private:
	int speed;




};
#endif
