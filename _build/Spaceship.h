#ifndef _SPACESHIP
#define _SPACESHIP
#include "Entity.h"
class Spaceship :public Entity
{

public:
	Spaceship(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, float speed, int level);
	void Update();

private:
	float moveTimer; //This will decide when will the spaceship moves from left to right on screen
	float speed;





};
#endif
