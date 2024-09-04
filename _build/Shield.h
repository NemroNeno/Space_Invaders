#ifndef _SHIELD
#define _SHIELD
#include "Entity.h"
class Shield :public Entity
{


public:
	Shield(raylib::Texture2D* texture, raylib::Rectangle outRect, raylib::Rectangle inRect,int level);

	void Event();
	void Update();
	void draw();
	int Recieve(int i);
	
private:
	int hp;


};
#endif
