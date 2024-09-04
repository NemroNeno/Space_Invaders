#ifndef _ENTITY
#define _ENTITY
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>
class Entity
{

	
protected:
	const int screenwidth;
	const int screenhieght;
	raylib::Texture *texture;
	raylib::Rectangle inclip;
	raylib::Rectangle outclip;
	int damagepoint;

public:
	enum State {
		Damage


	};

	virtual void Event();
	virtual void Update();
	virtual void draw();
	Entity(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip,int w,int h,int level);
	bool iscolliding(Entity* e);
	virtual int Recieve(int );
	bool enabled;
	void changetext(int num);
};
#endif


